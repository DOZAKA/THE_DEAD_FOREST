//
//  GameManager.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 27..
//
//

#include "GameManager.hpp"
#include "EntityHuman.hpp"
#include "Items.hpp"
#include "GameWorld.hpp"
#include "Camera2D.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    int GameManager::_nextValidID = 0;
    
    void GameManager::update(float dt)
    {
        for(auto &d : _entities )
        {
            d.second->update(dt);
        }
        
        if ( _debugNode->isVisible() )
        {
            // 공간분할 디버그
            const std::vector<Cell>& cells = _cellSpace->getCells();
            int idx = _cellSpace->positionToIndex(_gameCamera->getCameraPos());
            for( int i = 0 ; i < (int)cells.size() ; ++ i)
            {
                if ( idx == i )
                {
                    _debugNode->drawSolidRect(worldToLocal(cells[i].boundingBox.origin),
                                              worldToLocal(Vec2(cells[i].boundingBox.getMaxX(), cells[i].boundingBox.getMaxY())),
                                              Color4F(1.0f, 0.0f, 1.0f, 0.1f));
                }
                
                _debugNode->drawRect(worldToLocal(cells[i].boundingBox.origin),
                                     worldToLocal(Vec2(cells[i].boundingBox.getMaxX(), cells[i].boundingBox.getMaxY())),
                                     Color4F::RED);
            }
        }
    }
    
    GameManager::GameManager(GameWorld* world, Camera2D* camera) :
    _gameWorld(world),
    _winSize(Size::ZERO),
    _player(nullptr),
    _cellSpace(nullptr),
    _gameMap(nullptr),
    _gameCamera(camera),
    _debugNode(nullptr)
    {
        _winSize = cocos2d::Director::getInstance()->getVisibleSize();
    }
    
    
    GameManager::~GameManager()
    {
        this->clear();
    }
    
    void GameManager::_loadCellSpaceAndMap(const char* fileName)
    {
        _cellSpace = new CellSpacePartition(Prm.getValueAsInt("worldWidth"),
                                            Prm.getValueAsInt("worldHeight"),
                                            Prm.getValueAsInt("cellWidth"),
                                            Prm.getValueAsInt("cellHeight"),
                                            Prm.getValueAsInt("maxEntity"));
        
        _gameMap = GameMap::create(this, fileName);
        _gameMap->setTag(999);
        _gameCamera->getStaticRenderTarget()->addChild(_gameMap);
    }
    
    void GameManager::loadGameMapWithNetwork(const char* fileName)
    {
        if( _gameMap != nullptr )
        {
            throw std::runtime_error("<GameManager::loadGameMap> GameMap is already exist.");
        }
        
        _loadCellSpaceAndMap(fileName);
    }
    
    
    void GameManager::loadGameMap(const char* fileName)
    {
        if( _gameMap != nullptr )
        {
            throw std::runtime_error("<GameManager::loadGameMap> GameMap is already exist.");
        }

        _loadCellSpaceAndMap(fileName);
        
        std::vector<Vec2> startingPoints = getGameMap()->getStartingLocationData();
        log("<GameManager::loadGameMap> Created Human at (%.0f, %.0f)", startingPoints.front().x, startingPoints.front().y);
        EntityHuman* human = EntityHuman::create(this);
        human->setWorldPosition(startingPoints.front());
        human->setVisibleCrossHair(true);
        registEntity(human, getNextValidID(), Z_ORDER_HUMAN);
        setPlayer(human);
        
        
        for(int i = 1 ; i < startingPoints.size() ; ++ i)
        {
            log("<GameManager::loadGameMap> Created Human at (%.0f, %.0f)", startingPoints[i].x, startingPoints[i].y);
            EntityHuman* human = EntityHuman::create(this);
            human->setWorldPosition(startingPoints[i]);
            registEntity(human, getNextValidID(), Z_ORDER_HUMAN);
        }
        
        
//        std::vector<NameCoordAmount> items = getGameMap()->getItemData();
//        for(int i = 0 ; i < items.size() ; ++ i)
//        {
//            log("<GameManager::loadGameMap> Created Items at (%.0f, %.0f)", items[i].pos.x, items[i].pos.y);
//            
//            if ( items[i].name == "Glock22" )
//            {
//                ItemGlock17* glock17 = ItemGlock17::create(this, "Glock17.png", "Glock17.png", "Glock17.png",
//                                                           ui::Widget::TextureResType::PLIST);
//                glock17->setPosition(items[i].pos);
//                glock17->setAmount(items[i].amount);
//                registEntity(glock17, getNextValidID(), Z_ORDER_ITEMS);
//            }
//            else if (items[i].name == "M16A4" )
//            {
//                ItemM16A2* m16a2 = ItemM16A2::create(this, "M16A2.png", "M16A2.png", "M16A2.png",
//                                                     ui::Widget::TextureResType::PLIST);
//                m16a2->setPosition(items[i].pos);
//                m16a2->setAmount(items[i].amount);
//                registEntity(m16a2, getNextValidID(), Z_ORDER_ITEMS);
//            }
//            else if (items[i].name == "Axe" )
//            {
//                ItemAxe* axe = ItemAxe::create(this, "Axe.png", "Axe.png", "Axe.png",
//                                               ui::Widget::TextureResType::PLIST);
//                axe->setPosition(items[i].pos);
//                axe->setAmount(items[i].amount);
//                registEntity(axe, getNextValidID(), Z_ORDER_ITEMS);
//            }
//            else if (items[i].name == "M1897" )
//            {
//                ItemM1897* m1897 = ItemM1897::create(this, "M1897.png", "M1897.png", "M1897.png",
//                                                     ui::Widget::TextureResType::PLIST);
//                m1897->setPosition(items[i].pos);
//                m1897->setAmount(items[i].amount);
//                registEntity(m1897, getNextValidID(), Z_ORDER_ITEMS);
//            }
//            else if (items[i].name == "5_56mm")
//            {
//                Bullet556mm* bullet556mm = Bullet556mm::create(this, "5_56mm.png", "5_56mm.png", "5_56mm.png", ui::Widget::TextureResType::PLIST);
//                bullet556mm->setPosition(items[i].pos);
//                bullet556mm->setAmount(items[i].amount);
//                registEntity(bullet556mm, getNextValidID(), Z_ORDER_ITEMS);
//            }
//            else if (items[i].name == "9mm")
//            {
//                Bullet9mm* bullet9mm = Bullet9mm::create(this, "9mm.png", "9mm.png", "9mm.png", ui::Widget::TextureResType::PLIST);
//                bullet9mm->setPosition(items[i].pos);
//                bullet9mm->setAmount(items[i].amount);
//                registEntity(bullet9mm, getNextValidID(), Z_ORDER_ITEMS);
//            }
//        }
    }
    
    
    
    void GameManager::setPlayer(EntityHuman* player)
    {
        _player = player;
    }
    
    
    EntityBase* GameManager::getEntityFromID(int ID)
    {
        auto iter = _entities.find(ID);
        if(iter != _entities.end())
        {
            return iter->second;
        }
        else
        {
            return nullptr;
        }
    }
    
    
    void GameManager::registEntity(EntityBase* entity, int ID, int zOrder)
    {
        auto iter = _entities.find(ID);
        if( iter != _entities.end())
        {
            throw std::runtime_error("<GameManager::registEntity> ID is already exist.");
        }
        
        entity->setTag(ID);
        _entities.insert(std::make_pair(ID, entity));
        _cellSpace->addEntity(entity);
        
        int type = entity->getEntityType();
        if ( type == EntityType::ENTITY_HUMAN )
        {
            _gameCamera->getDynamicRenderTarget()->addChild(entity, zOrder);
        }
    }
    
    
    void GameManager::removeEntity(int id)
    {
        auto iter = _entities.find(id);
        if(iter == _entities.end())
        {
            throw std::runtime_error("<GameManager::removeEntity> ID is not exist.");
        }
        
        iter->second->removeFromParent();
        _entities.erase(iter);
        _cellSpace->removeEntityFromCell(iter->second);
        _gameWorld->removeChildByTag(id);
    }
    
    
    void GameManager::clear()
    {
        _entities.clear();
        
        CC_SAFE_DELETE(_cellSpace);
        
        _player = nullptr;

    }
    
    
    std::list<EntityBase*> GameManager::getNeighborsOnMove(const cocos2d::Vec2& position, float speed) const
    {
        std::list<EntityBase*> ret;
        std::vector<int> cellIndices = _cellSpace->getNeighborCells(position);
        for ( const int idx : cellIndices )
        {
            const Cell& currCell = _cellSpace->getCell(idx);
            if ( currCell.boundingBox.intersectsRect(cocos2d::Rect(position.x - speed / 2, position.y - speed / 2, speed, speed)) )
            {
                for ( const auto &entity : currCell.members )
                {
                    ret.push_back(entity);
                }
                
                // debug node
                if ( _debugNode->isVisible() )
                {
                    _debugNode->drawSolidRect(worldToLocal(currCell.boundingBox.origin),
                                              worldToLocal(Vec2(currCell.boundingBox.origin.x + currCell.boundingBox.size.width,
                                                                currCell.boundingBox.origin.y + currCell.boundingBox.size.height)), Color4F(1.0, 1.0, 0.0, 0.1));
                }
            }
        }
        return std::move(ret);
    }
    
    
    std::list<EntityBase*> GameManager::getNeighborsOnAttack(const cocos2d::Vec2& position, const cocos2d::Vec2& dir, float range) const
    {
        std::list<EntityBase*> ret;
        std::vector<int> cellIndices = _cellSpace->getNeighborCells(position);
        for ( const int idx : cellIndices )
        {
            const Cell& currCell = _cellSpace->getCell(idx);
            if ( physics::intersect(realtrick::Rect(currCell.boundingBox.origin.x,
                                                    currCell.boundingBox.origin.y,
                                                    currCell.boundingBox.size.width,
                                                    currCell.boundingBox.size.height), Segment(position, position + dir * range)) )
            {
                for ( const auto &entity : currCell.members )
                {
                    ret.push_back(entity);
                }
            }
        }
        return std::move(ret);
    }
    
    std::vector<Polygon> GameManager::getNeighborWalls(const cocos2d::Vec2& position, float speed) const
    {
        std::vector<Polygon> ret;
        std::vector<int> cellIndices = _cellSpace->getNeighborCells(position);
        for ( const int idx : cellIndices )
        {
            const Cell& currCell = _cellSpace->getCell(idx);
            if ( currCell.boundingBox.intersectsRect(cocos2d::Rect(position.x - speed / 2, position.y - speed / 2, speed, speed)) )
            {
                for ( const auto &wall : currCell.walls )
                {
                    ret.push_back(wall);
                }
            }
        }
        return std::move(ret);
    }
    
    std::vector<Polygon> GameManager::getNeighborWalls(const cocos2d::Vec2& position, const cocos2d::Size screenSize) const
    {
        std::vector<Polygon> ret;
        std::vector<int> cellIndices = _cellSpace->getNeighborCells(position);
        for ( const int idx : cellIndices )
        {
            const Cell& currCell = _cellSpace->getCell(idx);
            if ( currCell.boundingBox.intersectsRect(cocos2d::Rect(position - screenSize / 2, screenSize)) )
            {
                for ( const auto &wall : currCell.walls )
                {
                    ret.push_back(wall);
                }
            }
        }
        return std::move(ret);
    }
    
    cocos2d::Vec2 GameManager::worldToLocal(const cocos2d::Vec2& p) const
    {
        return p - _gameCamera->getCameraPos();
    }
    
    
    cocos2d::Vec2 GameManager::worldToLocal(const cocos2d::Vec2& p, const cocos2d::Vec2& camera) const
    {
        return p - camera;
    }
    
}












