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

#include "Network.h"



using namespace realtrick::network;
using namespace cocos2d;

namespace realtrick
{
    
    GameWorld::~GameWorld()
    {
        CC_SAFE_DELETE(_gameMgr);
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
        
        prepareToStart(false);
        
        Layer::onEnter();
    }
    
    
    
    void GameWorld::prepareToStart(bool network)
    {
        _debugNode = DrawNode::create();
        _debugNode->setPosition(_winSize/2);
        
        // is use debug?
        _debugNode->setVisible(Prm.getValueAsBool("useDebug"));
        
        addChild(_debugNode, numeric_limits<int>::max());
        
        _clipRectNode = ClippingRectangleNode::create(cocos2d::Rect(0, 0, _winSize.width, _winSize.height));
        addChild(_clipRectNode);
        
        
        _gameCamera = Camera2D::create(this);
        _gameCamera->setZoom(Prm.getValueAsFloat("cameraZoom"));
        _gameCamera->pauseGame();
        addChild(_gameCamera);
        
        
        _gameMgr = new GameManager(this, _gameCamera);
        _gameMgr->setDebugNode(_debugNode);
    
        
        if ( network )
        {
            loadGameDataByNetwork();
        }
        else
        {
            loadGameDataByFile();
        }
    }
    
    
    
    void GameWorld::loadGameDataByNetwork()
    {
        _gameMgr->loadGameMapWithNetwork("jsonData.txt");
        _gameMgr->setPacketProcess(std::make_shared<PacketProcess>(_gameMgr));
        
        while(!(network::Network::getInstance().isConnection()));
        
        PK_C_REQ_REGIST reqPacket;
        reqPacket.pid = ClientGenerator::getInstance().id();
        reqPacket.roomID = 1;
        
       Network::getInstance().sendPacket(&reqPacket);
    }
    
    
    
    void GameWorld::loadGameDataByFile()
    {
        _gameMgr->loadGameMap("jsonData.txt");
        setPlayerPtr(_gameMgr->getPlayerPtr());
        // 화면 출력
        displayGame();
    }
    
    
    
    void GameWorld::displayGame()
    {
        
        _uiLayer = Sprite::create();
        this->addChild(_uiLayer, Z_ORDER_UI);
        
        _moveJoystick = JoystickEx::create("handler.png", "handler.png", cocos2d::ui::Widget::TextureResType::PLIST);
        _moveJoystick->setJoystickPad("pad.png");
        _moveJoystick->setMaxMovableRadius(50.0f);
        _moveJoystick->setPosition(Vec2(200, 200));
        _moveJoystick->setRotationType(realtrick::JoystickEx::RotationType::ROTATION_8);
        _moveJoystick->setClickCallback([&, this](Ref* ref, ui::Widget::TouchEventType type){
            
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                {
                    _player->addInputMask(JoystickMessageTypes::MOVE);
                    break;
                }
                case ui::Widget::TouchEventType::ENDED:
                {
                    _player->removeInputMask(JoystickMessageTypes::MOVE);
                    break;
                }
                case ui::Widget::TouchEventType::CANCELED:
                {
                    _player->removeInputMask(JoystickMessageTypes::MOVE);
                    break;
                }
                default: break;
            }
            
        });
        
        _moveJoystick->setDoubleClickCallback([&, this](Ref* ref, JoystickEx::ClickEventType type){
            
            switch (type)
            {
                case JoystickEx::ClickEventType::BEGAN:
                {
                    _player->addInputMask(JoystickMessageTypes::RUN);
                    break;
                }
                case JoystickEx::ClickEventType::ENDED:
                {
                    _player->removeInputMask(JoystickMessageTypes::RUN);
                    break;
                }
                default: break;
            }
            
        });
        
        _moveJoystick->setChangedDirectionCallback([&, this](Ref* ref, const Vec2& newDirection){
            
            _player->setMoving(newDirection);
            
            JoystickEx* self = (JoystickEx*)ref;
            
            if( self->isDoubleClicked() )
            {
                _bezel->setBezelDirection(newDirection, _player->getTurnSpeed());
            }
            
        });
        
        _uiLayer->addChild(_moveJoystick);
        
        
        
        _bezel = CircularBezel::create("bezel.png", ui::Widget::TextureResType::LOCAL);
        _bezel->setPosition(Vec2(_winSize.width - 200, 200));
        _bezel->setTriggerDegree(std::make_pair(5.0f, 10.0f));
        _bezel->setTriggerRadius(std::make_pair(50.0f, 200.0f));
        _bezel->setPrecision(3);
        _bezel->addTriggerCallback([&, this](Ref* ref, const Vec2& dir){
            
            _player->setTargetHeading(dir);
            
        });
        _uiLayer->addChild(_bezel);
        
        
        
        _attButton = JoystickEx::create("attackButton.png", "attackButton.png", ui::Widget::TextureResType::LOCAL);
        _attButton->setJoystickPad("pad.png");
        _attButton->setMaxMovableRadius(80.0f);
        _attButton->setPosition(Vec2(_winSize.width - 200, 200));
        _attButton->setClickCallback([&, this](Ref* ref, ui::Widget::TouchEventType type){
            
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                {
                    _player->addInputMask((int)JoystickMessageTypes::ATTACK_BEGAN);
                    break;
                }
                case ui::Widget::TouchEventType::ENDED:
                {
                    _player->removeInputMask((int)JoystickMessageTypes::ATTACK_BEGAN);
                    _player->addInputMask((int)JoystickMessageTypes::ATTACK_ENDED);
                    break;
                }
                case ui::Widget::TouchEventType::CANCELED:
                {
                    _player->removeInputMask((int)JoystickMessageTypes::ATTACK_BEGAN);
                    _player->addInputMask((int)JoystickMessageTypes::ATTACK_ENDED);
                    break;
                }
                    
                default: break;
            }
            
        });
        _uiLayer->addChild(_attButton);
        
        
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
        // button holder
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
        
        
        _inventory = userinterface::Inventory::create();
        _inventory->setVisible(false);
        _inventory->setPosition(Vec2(_winSize.width / 2, _winSize.height * 0.55f));
        _uiLayer->addChild(_inventory);
        
        
        
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










