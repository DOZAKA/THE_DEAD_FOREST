//
//  CellSpacePartition.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 15..
//
//

#pragma once

#include <vector>
#include <list>
#include <algorithm>

#include "cocos2d.h"
#include "Physics.hpp"

namespace realtrick
{

    class EntityBase;
    
    class Cell
    {
        
    public:
        
        std::list<EntityBase*>                      members;
        
        std::vector<Polygon>                        walls;
        
        cocos2d::Rect                               boundingBox;
        
        Cell(cocos2d::Rect rect): boundingBox(rect)
        {}
        
    };
    
    
    class CellSpacePartition
    {
        
    public:
        
        CellSpacePartition() = delete;
        
        explicit CellSpacePartition(float worldWidth, float worldHeight, int cellWidth, int cellHeight, int maxEntities) :
        _worldWidth(worldWidth),
        _worldHeight(worldHeight),
        _cellWidth(cellWidth),
        _cellHeight(cellHeight)
        {
            _numOfCellsX = (worldWidth  / cellWidth) + 2;
            _numOfCellsY = (worldHeight / cellHeight) + 2;
            
            for (int y = 0; y < _numOfCellsY; ++y)
            {
                for (int x = 0; x <_numOfCellsX; ++x)
                {
                    float left  = x * cellWidth;
                    float bot   = y * cellHeight;
                    _cells.push_back(Cell(cocos2d::Rect(left - _cellWidth, bot - _cellHeight, cellWidth, cellHeight)));
                }
            }
            
        }
    
        inline void                     addEntity(EntityBase* ent);
        
        inline void                     addWall(const Polygon& wall);
        
        inline bool                     updateEntity(EntityBase* ent, cocos2d::Vec2 oldPos);
        
        inline void                     calculateNeighbors(cocos2d::Vec2 targetPos, float queryRadius);
        
        inline void                     clearCells();
        
        inline void                     removeEntityFromCell(EntityBase* ent);
        
        inline int                      positionToIndex(const cocos2d::Vec2& pos) const;
        
        inline const Cell&              getCell(const cocos2d::Vec2& pos) const;
        
        inline const Cell&              getCell(int index)  { return _cells[index]; }
        
        inline float                    getWorldWidth() const { return _worldWidth; }
        
        inline float                    getWorldHeight() const { return _worldHeight; }
        
        inline int                      getNumOfCellX() const { return _numOfCellsX; }
        
        inline int                      getNumOfCellY() const { return _numOfCellsY; }
        
        inline float                    getCellWidth() const { return _cellWidth; }
        
        inline float                    getCellHeight() const { return _cellHeight; }
        
        inline std::vector<int>         getNeighborCells(const cocos2d::Vec2& pos) const;
        
        inline const std::vector<Cell>& getCells() const { return _cells; }
        
    private:
        
        std::vector<Cell>       _cells;
        
        float                   _worldWidth;
        
        float                   _worldHeight;
        
        int                     _numOfCellsX;
        
        int                     _numOfCellsY;
        
        float                   _cellWidth;
        
        float                   _cellHeight;
    
    };
    
}

#include "CellSpacePartition.inl"





