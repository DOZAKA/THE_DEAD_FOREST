//
//  GameManager.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 27..
//
//

#pragma once

#include <string>
#include <exception>
#include <memory>

#include "cocos2d.h"
#include "CellSpacePartition.hpp"
#include "GameMap.hpp"
#include "EntityHuman.hpp"

#define Z_ORDER_GAME_MAP    0
#define Z_ORDER_SHADOW      1
#define Z_ORDER_LIGHT       2
#define Z_ORDER_ITEMS       3
#define Z_ORDER_HUMAN       4
#define Z_ORDER_SKY         5
#define Z_ORDER_UI          6

#define BF_MULTIPLY         { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA }
#define BF_ADDITIVE         { GL_ONE, GL_ONE }

namespace realtrick
{
    
    class EntityBase;
    class EntityHuman;
    class GameWorld;
    class Camera2D;
    
    class GameManager
    {
        
    public:
        
        explicit GameManager(GameWorld* world, Camera2D* camera);
        
        virtual ~GameManager();
        
        EntityHuman*                            getPlayerPtr() const                                    { return _player; }
        
        const std::map<int, EntityBase*>&       getEntities() const                                     { return _entities; }
        
        GameMap*                                getGameMap() const                                      { return _gameMap; }
        
        CellSpacePartition*                     getCellSpace() const                                    { return _cellSpace; }
        
        int                                     getNextValidID()                                        { return _nextValidID++; }
        
        GameWorld*                              getGameWorld() const                                    { return _gameWorld; }
        
        std::list<EntityBase*>                  getNeighborsOnMove(const cocos2d::Vec2& position, float speed) const;
        
        std::list<EntityBase*>                  getNeighborsOnAttack(const cocos2d::Vec2& position, const cocos2d::Vec2& dir, float range) const;
    
        std::vector<Polygon>                    getNeighborWalls(const cocos2d::Vec2& position, float speed) const;
        
        std::vector<Polygon>                    getNeighborWalls(const cocos2d::Vec2& position, const cocos2d::Size screenSize) const;
        
        void setPlayer(EntityHuman* player);
        
        void registEntity(EntityBase* entity, int ID, int zOrder);
        
        void removeEntity(int id);
        
        EntityBase* getEntityFromID(int ID);
        
        void clear();
        
        void update(float dt);
        
        void loadGameMap(const char* fileName);
        
        void loadGameMapWithNetwork(const char* fileName);
        
        std::string getFileFromNetwork();
        
        void setGameCamera(Camera2D* camera) { _gameCamera = camera; }
        
        Camera2D* getGameCamera() const { return _gameCamera; }
        
        void setDebugNode(cocos2d::DrawNode* node) { _debugNode = node; }
        
        cocos2d::DrawNode* getDebugNode() const { return _debugNode; }
        
        cocos2d::Vec2 worldToLocal(const cocos2d::Vec2& p) const ;
        
        cocos2d::Vec2 worldToLocal(const cocos2d::Vec2& p, const cocos2d::Vec2& camera) const ;

    private:
        
        GameWorld*                                  _gameWorld;
        
        cocos2d::Size                               _winSize;
        
        EntityHuman*                                _player;
        
        std::map<int, EntityBase*>                  _entities;
        
        CellSpacePartition*                         _cellSpace;
        
        GameMap*                                    _gameMap;
        
        Camera2D*                                   _gameCamera;
        
        cocos2d::DrawNode*                          _debugNode;
        
        static int                                  _nextValidID;

    private:
        
        void _setGameWorld(GameWorld* world)            { _gameWorld = world; }
        
        void _loadCellSpaceAndMap(const char* fileName);
    };
    
}











