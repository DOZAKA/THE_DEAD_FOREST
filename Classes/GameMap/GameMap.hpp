//
//  GameMap.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 12..
//  
//


#pragma once

#include <string>
#include <exception>

#include "cocos2d.h"
#include "Physics.hpp"
#include "ParamLoader.hpp"
#include "json/document.h"
#include "ParseStructures.hpp"

using namespace cocos2d;
using namespace rapidjson;
using namespace std;

namespace realtrick
{
    
    class GameManager;
    
    class GameMap : public cocos2d::Node
    {
    
    public:
        
        static GameMap* create(GameManager* gameMgr, const char* fileName);
        
        void updateChunk(const Vec2& position);
        
        int getWorldWidth() const                                                   { return _worldWidth; }
        
        int getWorldHeight() const                                                  { return _worldHeight; }
        
        int getMaxEntity() const                                                    { return _maxEntity; }
        
        int getCellWidth() const                                                    { return _cellWidth; }
        
        int getCellHeight() const                                                   { return _cellHeight; }
        
        const std::vector<Polygon>&              getCollisionData() const           { return _collisionData; }
        
        const std::vector<vector<string>>&       getTileData() const                { return _tileData; }
        
        const std::vector<Vec2>&                 getStartingLocationData() const    { return _startingLocationList; }
        
        const std::vector<NameCoordAmount>&      getItemData() const                { return _itemData; }
        
        const std::vector<NameCoord>&            getIndoorTileData() const          { return _indoorTileData; }
        
        const std::vector<NameCoord>&            getWallsData() const               { return _wallsData; }
        
        const std::vector<NameCoord>&            getDoodadData() const              { return _doodadData; }

        virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
        
        cocos2d::Vec2 getWorldPosition() const                                      { return _worldPosition; }
        
        void setWorldPosition(const cocos2d::Vec2& worldPos)                        { _worldPosition = worldPos; }
        
        void enableNormal(bool enable);
        
        inline std::pair<int, int> getModerateTileIndex(const cocos2d::Vec2& pos) const;
        
        std::vector<Segment> getNeighborWall(const cocos2d::Vec2 position) const;
        
    private:
        
        GameManager*                                    _gameMgr;
        
        std::vector<std::vector<Sprite*>>               _currTiles;
        
        std::vector<std::vector<Sprite*>>               _normalTiles;
        
        int                                             _numOfTileX;
        
        int                                             _numOfTileY;
        
        int                                             _sizeOfTile;
        
        int                                             _worldWidth;
        
        int                                             _worldHeight;
        
        int                                             _maxEntity;
        
        int                                             _cellWidth;
        
        int                                             _cellHeight;
        
        int                                             _numOfViewableTileX;
        
        int                                             _numOfViewableTileY;
        
        std::pair<int,int>                              _pivotIndex;
        
        std::string                                     _data;
        
        rapidjson::Document                             _doc;
        
        std::vector<Polygon>                            _collisionData;
        
        std::vector<vector<string>>                     _tileData;
        
        std::vector<Vec2>                               _startingLocationList;
        
        std::vector<NameCoordAmount>                    _itemData;
        
        std::vector<NameCoord>                          _indoorTileData;
        
        std::vector<NameCoord>                          _wallsData;
        
        std::vector<NameCoord>                          _doodadData;
        
        cocos2d::Vec2                                   _worldPosition;
        
        bool                                            _isNormal;
        
    private:
        
        explicit GameMap(GameManager* gameMgr);
        
        virtual ~GameMap();
        
        bool initGameMap(const char* fileName);
        
        std::pair<int, int> _getExactTileIndex(const cocos2d::Vec2& pos);
        
        void _parseCollisionData();
        
        void _parseTileData();
        
        void _parseStartingLocationList();
        
        void _parseItemData();
        
        void _parseIndoorTileData();
        
        void _parseWallsData();
        
        void _parseDoodadData();
        
        void _parseFromFile(const char* fileName);
        
        inline cocos2d::Vec2 _getTilePositionFromIndex(int x, int y);
        
    };
    
    
    inline cocos2d::Vec2 GameMap::_getTilePositionFromIndex(int x, int y)
    {
        return cocos2d::Vec2(y % 2 ? _sizeOfTile * (x + 1) : (_sizeOfTile / 2) + (_sizeOfTile * x), (_sizeOfTile / 2) * y);
    }
    
    
    inline std::pair<int, int> GameMap::getModerateTileIndex(const cocos2d::Vec2& pos) const
    {
        int x = (int)((pos.x) / _sizeOfTile);        // not exact index!
        int y = (int)((pos.y) / (_sizeOfTile / 2));  // not exact index!
        return std::make_pair(x, y);
    }
    
}





