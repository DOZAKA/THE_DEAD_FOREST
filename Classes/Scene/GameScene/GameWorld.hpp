//
//  GameWorld.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 12..
//  
//


#pragma once

#include "cocos2d.h"
#include "CocosGUI.h"
#include "PacketProcess.h"

namespace realtrick
{
    
    class GameManager;
    class JoystickEx;
    class CircularBezel;
    class InventoryEx;
    class EntityHuman;
    class WeaponStatusEx;
    class OcculusionBuilder;
    class Camera2D;
    class GameFlow;
    
    namespace userinterface
    {
        class ButtonHolder;
        class Inventory;
    }
    
    class GameWorld : public cocos2d::Layer
    {
        
    public:
        
        bool                                _isNetworkReady = false;
        
    public:
        
        virtual ~GameWorld();
        
        static cocos2d::Scene* createScene();
        
        virtual bool init() override;
        
        CREATE_FUNC(GameWorld);
        
        virtual void update(float dt) override;
        
        Camera2D* getGameCamera() const { return _gameCamera; }
        
        cocos2d::Size getWorldSize() const { return _winSize; }
        
        GameManager* getGameManager() const { return _gameMgr; }
        
        virtual void onEnter() override;
        
        cocos2d::DrawNode* getDebugNode() const { return _debugNode; }
        
        EntityHuman* getPlayerPtr() const { return _player; }
        
        void setPlayerPtr(EntityHuman* player) { _player = player; }
        
        void prepareToStart(bool network = false);
        
        void loadGameDataByNetwork();
        
        void loadGameDataByFile();
        
        void displayGame();
        
    private:
        
        cocos2d::Size                       _winSize;
        
        GameManager*                        _gameMgr;
        
        cocos2d::Sprite*                    _uiLayer;
        
        cocos2d::ClippingRectangleNode*     _clipRectNode;
        
        Camera2D*                           _gameCamera;
        
        JoystickEx*                         _moveJoystick;
        
        CircularBezel*                      _bezel;
        
        JoystickEx*                         _attButton;
        
        WeaponStatusEx*                     _weaponStatus;
        
        EntityHuman*                        _player;
        
        cocos2d::DrawNode*                  _debugNode;
        
        userinterface::ButtonHolder*        _buttonHolder;
        
        userinterface::Inventory*           _inventory;
        
        GameFlow*                           _gameFlow;
    
    };
    
}










