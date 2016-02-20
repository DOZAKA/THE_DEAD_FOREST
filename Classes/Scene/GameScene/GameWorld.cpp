//
//  GameWorld.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 12..
//
//

#include "GameWorld.hpp"
#include "GameManager.hpp"
#include "GameManager.hpp"
#include "JoystickEx.hpp"
#include "CircularBezel.hpp"
#include "WeaponStatusEx.hpp"
#include "MessageDispatcher.hpp"
#include "ParamLoader.hpp"
#include "EntityHuman.hpp"
#include "Items.hpp"
#include "OcculusionBuilder.hpp"
#include "Camera2D.hpp"
#include "GameMap.hpp"
#include "ClipperWrapper.hpp"
#include "ButtonHolder.hpp"
#include "Inventory.hpp"
#include "GameFlow.hpp"
#include "SingleGameFlow.hpp"
#include "NetworkGameFlow.hpp"

#include "Network.h"
#include "PacketQueue.h"
#include "PacketClass.h"


using namespace realtrick::network;
using namespace cocos2d;

namespace realtrick
{
    
    GameWorld::~GameWorld()
    {
        CC_SAFE_DELETE(_gameMgr);
        CC_SAFE_DELETE(_gameFlow);
    }
    
    
    Scene* GameWorld::createScene()
    {
        auto scene = Scene::create();
        auto layer = GameWorld::create();
        scene->addChild(layer);
        return scene;
    }
    

    bool GameWorld::init()
    {
        if ( !Layer::init() )
        {
            return false;
        }
        
        auto touchListener = EventListenerTouchAllAtOnce::create();
        touchListener->onTouchesBegan = CC_CALLBACK_2(GameWorld::onTouchesBegan, this);
        touchListener->onTouchesMoved = CC_CALLBACK_2(GameWorld::onTouchesMoved, this);
        touchListener->onTouchesEnded = CC_CALLBACK_2(GameWorld::onTouchesEnded, this);
        touchListener->onTouchesCancelled = CC_CALLBACK_2(GameWorld::onTouchesCancelled, this);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        _winSize = Director::getInstance()->getVisibleSize();
        
        
        return true;
    }
    
    
    void GameWorld::onEnter()
    {
        //
        //                                                [Director]
        //                                                    |
        //                                                    |
        //                                               [Game World]
        //                                   /                                      \
        //                             clipRectNode                             ui layer                         (depth 1)
        //                                  |                                       |
        //                             game camera                  inventory   joystick   circular bezel        (depth 2)
        //                                  |
        //       static node   dynamic node   normal node    occulusion node                                     (depth 3)
        //
        
        prepareToStart(true);
        Layer::onEnter();
    }
    
    
    void GameWorld::prepareToStart(bool network)
    {
        _debugNode = DrawNode::create();
        _debugNode->setPosition(_winSize/2);
        addChild(_debugNode, numeric_limits<int>::max() - 1);
        
        // is use debug?
        _debugNode->setVisible(Prm.getValueAsBool("useDebug"));
        
        //
        // 화면을 클리핑하기 위한 상위 객체. (이 노드에 붙는다면 화면 바깥은 안그려지게 된다)
        //
        _clipRectNode = ClippingRectangleNode::create(cocos2d::Rect(0, 0, _winSize.width, _winSize.height));
        addChild(_clipRectNode);
        
    
        // [월드 생성 순서]
        // Camera 생성   ->   Manager 생성   ->   Game Flow 생성   ->   게임 로드
        //
        
        
        //
        // 1. Game Camera
        //
        _gameCamera = Camera2D::create(this);
        _gameCamera->setZoom(Prm.getValueAsFloat("cameraZoom"));
        _gameCamera->pauseGame();
        addChild(_gameCamera);
        
        
        //
        // 2. Game Manager
        //
        _gameMgr = new GameManager(this, _gameCamera);
        _gameMgr->setDebugNode(_debugNode);
    
        
        //
        // 3. Game Flow ( 네트워크, 싱글 플레이에 맞게 게임 로직이 다르게 흐른다. )
        //
        if ( network ) _gameFlow = new NetworkGameFlow(this);
        else _gameFlow = new SingleGameFlow(this);
        
        
        //
        // 4. Load Data ( 흐름에 맞게 데이터를 로딩 )
        //
        _gameFlow->loadGameData();
    }
    
    
    void GameWorld::displayGame()
    {
        _uiLayer = Sprite::create();
        addChild(_uiLayer, numeric_limits<int>::max());

        
        //
        // Move Joystick
        //
        _moveJoystick = JoystickEx::create("handler.png", "handler.png", cocos2d::ui::Widget::TextureResType::PLIST);
        _moveJoystick->setJoystickPad("pad.png");
        _moveJoystick->setMaxMovableRadius(50.0f);
        _moveJoystick->setPosition(Vec2(200, 200));
        _moveJoystick->setRotationType(realtrick::JoystickEx::RotationType::ROTATION_8);
        _moveJoystick->setChangedDirectionAndStatusCallback(_gameFlow->getMoveJoystickCallback());
        _uiLayer->addChild(_moveJoystick);
        
        
        //
        // Bezel
        //
        _bezel = CircularBezel::create("bezel.png", ui::Widget::TextureResType::LOCAL);
        _bezel->setPosition(Vec2(_winSize.width - 200, 200));
        _bezel->setTriggerDegree(std::make_pair(5.0f, 10.0f));
        _bezel->setTriggerRadius(std::make_pair(50.0f, 200.0f));
        _bezel->setPrecision(3);
        _bezel->addTriggerCallback(_gameFlow->getBelzelCallback());
        _uiLayer->addChild(_bezel);
        

        //
        // Attack Joystick
        //
        _attButton = JoystickEx::create("attackButton.png", "attackButton.png", ui::Widget::TextureResType::LOCAL);
        _attButton->setJoystickPad("pad.png");
        _attButton->setMaxMovableRadius(80.0f);
        _attButton->setPosition(Vec2(_winSize.width - 200, 200));
        _attButton->setClickCallback(_gameFlow->getAttackJoystickCallback());
        _uiLayer->addChild(_attButton);
        
        
        
        //
        // Current Weapon UI
        //
        _weaponStatus = WeaponStatusEx::create("reload.png", "reload.png", ui::Widget::TextureResType::LOCAL);
        _weaponStatus->setPosition(Vec2(_winSize.width - 100.0f, _winSize.height - 100.0f));
        _weaponStatus->setReloadButtonCallback([&, this](Ref* ref, ui::Widget::TouchEventType type){
            
            ui::Button* self = (ui::Button*)ref;
            
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                {
                    self->stopAllActions();
                    self->runAction(ScaleTo::create(0.1f, 0.95f));
                    break;
                }
                case ui::Widget::TouchEventType::ENDED:
                {
                    self->stopAllActions();
                    self->runAction(Spawn::create(ScaleTo::create(0.1f, 1.0f), EaseElasticOut::create(RotateBy::create(0.5f, 360.0f)), nullptr));
                    Dispatch.pushMessage(0.0f, _player, nullptr, MessageType::RELOAD_WEAPON, nullptr);
                }
                default: break;
            }
            
        });
        _uiLayer->addChild(_weaponStatus);
        
        
        //
        // Button Holder
        //
        _buttonHolder = userinterface::ButtonHolder::create(_gameMgr);
        _buttonHolder->setPosition(Vec2(_winSize.width / 2.0f, _winSize.height * 0.15f));
        _buttonHolder->setButtonSize(Size(92.0f, 92.0f));
        addChild(_buttonHolder);
        
        // inventory를 눌렀을 때,
        _buttonHolder->addInventoryButtonEvent(1, [&](Ref* ref, ui::CheckBox::EventType type){
            
            switch ( type )
            {
                case ui::CheckBox::EventType::SELECTED:
                {
                    log("inventory selected.");
                    _inventory->setVisible(true);
                    break;
                }
                case ui::CheckBox::EventType::UNSELECTED:
                {
                    log("inventory unselected.");
                    _inventory->setVisible(false);
                    break;
                }
                default: break;
            }
            
        });
        
        
        //
        // Inventory
        //
        _inventory = userinterface::Inventory::create();
        _inventory->setVisible(false);
        _inventory->setPosition(Vec2(_winSize.width / 2, _winSize.height * 0.55f));
        _uiLayer->addChild(_inventory);
        
        
        
        //
        // Hp System (Dummy)
        //
        auto hpBar = Sprite::createWithSpriteFrameName("hpBar.png");
        hpBar->setAnchorPoint(Vec2(0.0f, 0.5f));
        hpBar->setScaleX(0.3f);
        hpBar->setPosition(_winSize.width * 0.07f, _winSize.height * 0.93f);
        _uiLayer->addChild(hpBar);
        
        hpBar->runAction(RepeatForever::create(Sequence::create(FadeTo::create(0.5f, 0), FadeTo::create(0.5f, 255), nullptr)));
        
        auto hpBundle = Sprite::createWithSpriteFrameName("hpBundle.png");
        hpBundle->setAnchorPoint(Vec2(0.0f, 0.5f));
        hpBundle->setPosition(_winSize.width * 0.07f, _winSize.height * 0.93f);
        _uiLayer->addChild(hpBundle);
        
        
        
        // init game map
        _gameMgr->getGameMap()->updateChunk(_player->getWorldPosition());
        _gameCamera->setCameraPos(_player->getWorldPosition());
        _gameCamera->resumeGame();
        
        this->scheduleUpdate();
    }

    
    void GameWorld::update(float dt)
    {
        _gameFlow->packetExecute();

        _debugNode->clear();
        Vec2 oldCameraPos = _gameCamera->getCameraPos();
        pair<int, int> oldIndex = _gameMgr->getGameMap()->getModerateTileIndex(oldCameraPos);
        
        _gameMgr->update(dt);
        _gameCamera->setCameraPos(_player->getWorldPosition());
        
        if ( oldIndex != _gameMgr->getGameMap()->getModerateTileIndex(_gameCamera->getCameraPos()) )
            _gameMgr->getGameMap()->updateChunk(oldCameraPos);
        
        Dispatch.dispatchDelayedMessages();
    }
    
}










