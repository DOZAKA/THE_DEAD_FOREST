//
//  OcculusionBuilder.inl
//  TheDeadForest
//
//  Created by 남준현 on 2015. 12. 5..
//
//

#include "OcculusionBuilder.hpp"

namespace realtrick
{
    
    inline bool OcculusionBuilder::_isVisibleWall(const Segment& wall) const
    {
        cocos2d::Vec2 wallDir = wall.end - wall.start;
        cocos2d::Vec2 normal;
        if(_windingOrder == WindingOrder::CCW) normal = wallDir.getRPerp();
        else if(_windingOrder == WindingOrder::CW) normal = wallDir.getPerp();
        normal.normalize();
        cocos2d::Vec2 toWall = wall.start - _eyePos;
        return (toWall.dot(normal) <= 0);
    }
    
    
    inline int OcculusionBuilder::_hashFunc(const cocos2d::Vec2& p) const
    {
        int a = (int)p.x;
        int b = (int)p.y;
        return a + (2 * a * b) + (3 * b) + (a / 4);
    }
    
    inline bool OcculusionBuilder::_isOneHitVertex(const std::vector<Segment>& walls, const cocos2d::Vec2& vert) const
    {
        for(auto &wall : walls)
        {
            if(wall.start == vert || wall.end == vert) continue;
            if ( physics::intersect(Segment(_eyePos, vert), wall) ) return false;
        }
        return true;
    }
    
    
    inline cocos2d::Vec2 OcculusionBuilder::_getClosestIntersectPointToWall(const std::vector<Segment>& walls, const Segment& seg) const
    {
        std::pair<float, cocos2d::Vec2> closestVal { std::numeric_limits<float>::max(), cocos2d::Vec2::ZERO };
        for(const auto &wall : walls)
        {
            std::pair<float, cocos2d::Vec2> rst {};
            if( physics::intersectGet(seg, Segment(wall.start, wall.end), rst.first, rst.second) )
            {
                if( rst.first < closestVal.first ) closestVal = rst;
            }
        }
        return closestVal.second;
    }
    
    
    inline cocos2d::Vec2 OcculusionBuilder::_worldToLocal(const cocos2d::Vec2& point)
    {
        return point - _eyePos;
    }
    
}
















