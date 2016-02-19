//
//  GameMap.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 12..
//  
//

#include <string>

#include "GameMap.hpp"
#include "GameManager.hpp"
#include "Camera2D.hpp"


namespace realtrick
{
    
    GameMap::GameMap(GameManager* gameMgr) : _gameMgr(gameMgr),
    _numOfTileX(0),
    _numOfTileY(0),
    _sizeOfTile(0),
    _worldWidth(0),
    _worldHeight(0),
    _maxEntity(0),
    _cellWidth(0),
    _cellHeight(0),
    _numOfViewableTileX(0),
    _numOfViewableTileY(0),
    _isNormal(false)
    {}
    
    
    GameMap::~GameMap()
    {}
    
    
    GameMap* GameMap::create(GameManager* gameMgr, const char* fileName)
    {
        GameMap *ret = new (std::nothrow) GameMap(gameMgr);
        if (ret && ret->initGameMap(fileName))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    
    bool GameMap::initGameMap(const char* fileName)
    {
        if ( !Node::init() )
        {
            return false;
        }
        
        _numOfViewableTileX     = Prm.getValueAsInt("numOfViewableTileX");
        _numOfViewableTileY     = Prm.getValueAsInt("numOfViewableTileY");
        _sizeOfTile             = Prm.getValueAsInt("sizeOfTile");
        _worldWidth             = Prm.getValueAsInt("worldWidth");
        _worldHeight            = Prm.getValueAsInt("worldHeight");
        _maxEntity              = Prm.getValueAsInt("maxEntity");
        _cellWidth              = Prm.getValueAsInt("cellWidth");
        _cellHeight             = Prm.getValueAsInt("cellHeight");
        
        _currTiles.resize(_numOfViewableTileY);
        _normalTiles.resize(_numOfViewableTileY);
        for (int i = 0; i < _numOfViewableTileY; ++i)
        {
            _currTiles[i].resize(_numOfViewableTileX);
            _normalTiles[i].resize(_numOfViewableTileX);
        }
        
        for (int i = 0; i < _numOfViewableTileY; ++i)
        {
            for (int j = 0; j < _numOfViewableTileX; ++j)
            {
                _currTiles[i][j] = Sprite::create();
                _normalTiles[i][j] = Sprite::create();
                 addChild(_normalTiles[i][j] , 2);          //     =="====""===="==== : 배경 노멀 텍스쳐 (2)
                addChild(_currTiles[i][j] , 1);             //     --'----''----'---- : 일반 배경 텍스쳐 (1)
            }
        }
        
        _parseFromFile(fileName);
        enableNormal(false);
        
        return true;
    }
    
    
    void GameMap::_parseFromFile(const char* fileName)
    {
        _data = FileUtils::getInstance()->getStringFromFile(fileName);
        _doc.Parse<0>(_data.c_str());
        
        _parseCollisionData();
        _parseDoodadData();
        _parseIndoorTileData();
        _parseItemData();
        _parseStartingLocationList();
        _parseTileData();
        _parseWallsData();
    }
    
    
    void GameMap::_parseCollisionData()
    {
        const rapidjson::Value& objs = _doc["Collisions"];
        for(SizeType i = 0; i < objs.Size(); ++ i)
        {
            Polygon p;
            const rapidjson::Value& vertices = objs[i];
            for(SizeType j = 0; j < vertices.Size() ; ++ j)
            {
                const rapidjson::Value& data = vertices[j];
                p.pushVertex(( Vec2(data["x"].GetDouble(), data["y"].GetDouble()) ));
            }
            _collisionData.push_back(p);
            
            // add clipped walls
            _gameMgr->getCellSpace()->addWall(p);
        }
    }
    
    
    void GameMap::_parseTileData()
    {
        const rapidjson::Value& tile = _doc["Tiles"];
        _numOfTileX = tile["width"].GetInt();
        _numOfTileY = tile["height"].GetInt();
        _tileData.resize(_numOfTileY);
        for(int i = 0 ; i < _numOfTileY; ++ i)
        {
            _tileData[i].resize(_numOfTileX);
        }
        const rapidjson::Value& tileNames = tile["type"];
        for(int i = 0; i < _numOfTileY; ++ i)
        {
            for(int j = 0; j < _numOfTileX; ++ j)
            {
                const rapidjson::Value& name = tileNames[j + i * _numOfTileX];
                _tileData[i][j] = name["name"].GetString();
            }
        }
    }
    
    
    void GameMap::_parseStartingLocationList()
    {
        const rapidjson::Value& locations = _doc["Locations"];
        for(SizeType i = 0 ; i < locations.Size() ; ++ i)
        {
            const rapidjson::Value& data = locations[i];
            _startingLocationList.push_back(Vec2(data["x"].GetInt(),data["y"].GetInt()));
        }
    }
    
    
    void GameMap::_parseItemData()
    {
        const rapidjson::Value& items = _doc["Items"];
        for(SizeType i = 0 ; i < items.Size() ; ++ i)
        {
            const rapidjson::Value& data = items[i];
            _itemData.push_back(NameCoordAmount(data["name"].GetString(),
                                                Vec2(data["x"].GetInt(), data["y"].GetInt()),
                                                data["amount"].GetInt()));
        }
    }
    
    
    void GameMap::_parseIndoorTileData()
    {
        const rapidjson::Value& indoorTiles = _doc["InDoorTiles"];
        for(SizeType i = 0 ; i < indoorTiles.Size() ; ++ i)
        {
            const rapidjson::Value& data = indoorTiles[i];
            _indoorTileData.push_back(NameCoord(data["name"].GetString(), Vec2(data["x"].GetInt(), data["y"].GetInt())));
        }
    }
    
    
    
    void GameMap::_parseWallsData()
    {
        const rapidjson::Value& walls = _doc["Walls"];
        for(SizeType i = 0 ; i < walls.Size() ; ++ i)
        {
            const rapidjson::Value& data = walls[i];
            _wallsData.push_back(NameCoord(data["name"].GetString(), Vec2(data["x"].GetInt(), data["y"].GetInt())));
        }
    }
    
    
    
    void GameMap::_parseDoodadData()
    {
        const rapidjson::Value& objects = _doc["Doodads"];
        for(SizeType i = 0 ; i < objects.Size() ; ++ i)
        {
            const rapidjson::Value& data = objects[i];
            _doodadData.push_back(NameCoord(data["name"].GetString(), Vec2(data["x"].GetInt(), data["y"].GetInt())));
        }
    }
    
    
    
    std::pair<int,int> GameMap::_getExactTileIndex(const Vec2& pos)
    {
        int centerTileIndexX = (int)((pos.x) / _sizeOfTile);        // not exact index!
        int centerTileIndexY = (int)((pos.y) / (_sizeOfTile / 2));  // not exact index!
        
        for(int i = centerTileIndexY - 2 ; i < centerTileIndexY + 2 ; ++ i)
        {
            for(int j = centerTileIndexX - 2 ; j < centerTileIndexX + 2 ; ++ j)
            {
                Vec2 pivot;
                if(i % 2 == 0)  pivot.x = (_sizeOfTile / 2) + (_sizeOfTile * j);
                else            pivot.x = _sizeOfTile * (j + 1);
                
                pivot.y = (_sizeOfTile / 2) * i;
                
                if(physics::isContainPointInDiamond(pivot, (_sizeOfTile / 2), pos))
                {
                    centerTileIndexX = j; // exact index!
                    centerTileIndexY = i; // exact index!
                    return std::make_pair(j, i);
                }
            }
        }
        return std::make_pair(0,0);
    }
    
    
    
    void GameMap::updateChunk(const Vec2& position)
    {
        log("<GameMap::updateChunk> re-load tiles at (%f, %f)", position.x, position.y);
        
        std::pair<int, int> originIndex = _getExactTileIndex(position);
        int xIdx = 0;
        int yIdx = 0;
        for(int y = originIndex.second - _numOfViewableTileY / 2; y < originIndex.second + _numOfViewableTileY / 2 ; ++ y)
        {
            for(int x = originIndex.first - _numOfViewableTileX / 2; x < originIndex.first + _numOfViewableTileX / 2 ; ++ x)
            {
                if( xIdx == _numOfViewableTileX) xIdx = 0, yIdx ++;
                
                _currTiles[yIdx][xIdx]->setSpriteFrame(_tileData[y][x] + ".png");
                _currTiles[yIdx][xIdx]->setPosition(_getTilePositionFromIndex(x, y));
                
                _normalTiles[yIdx][xIdx]->setSpriteFrame(_tileData[y][x] + "_n.png");
                _normalTiles[yIdx][xIdx]->setPosition(_getTilePositionFromIndex(x, y));
                
                xIdx++;
            }
        }
    }
    
    
    void GameMap::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
    {
        setPosition( getWorldPosition() - _gameMgr->getGameCamera()->getCameraPos() );
        Node::visit(renderer, transform, flags);
    }
    
    
    void GameMap::enableNormal(bool enable)
    {
        for(int i = 0 ; i < _normalTiles.size() ; ++ i)
        {
            for(int j = 0 ; j < _normalTiles[i].size() ; ++ j)
            {
                _normalTiles[i][j]->setVisible(enable);
            }
        }
    }
    
    
    std::vector<Segment> GameMap::getNeighborWall(const cocos2d::Vec2 position) const
    {
        std::vector<Segment> ret;
        
        return ret;
    }
    
}






