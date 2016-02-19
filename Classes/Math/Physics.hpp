//
//  Physics.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 12..
//  
//

#pragma once

#include "Geometry.hpp"

namespace realtrick
{
    
    namespace physics
    {
        
        inline bool     intersect(const Rect& rect1, const Rect& rect2);
        inline bool     intersect(const Rect& rect, const Circle& circle);
        inline bool     intersect(const Rect& rect, const Segment& segment);
        inline bool     intersect(const Rect& rect, const Polygon& polygon);
        
        inline bool     intersect(const Circle& circle, const Rect& rect);
        inline bool     intersect(const Circle& circle1, const Circle& circle2);
        inline bool     intersect(const Circle& circle, const Segment& segment);
        inline bool     intersect(const Circle& circle, const Polygon& polygon);
        
        inline bool     intersect(const Segment& segment, const Rect& rect);
        inline bool     intersect(const Segment& segment, const Circle& circle);
        inline bool     intersect(const Segment& segment1, const Segment& segment2);
        inline bool     intersect(const Segment& segment, const Polygon& polygon);
        
        
        inline bool     intersect(const Polygon& polygon, const Rect& rect);
        inline bool     intersect(const Polygon& polygon, const Circle& circle);
        inline bool     intersect(const Polygon& polygon, const Segment& segment);
        inline bool     intersect(const Polygon& polygon1, const Polygon& polygon2);
        
        inline bool     intersectGet(const Segment& segment1, const Segment& segment2, float &dist);
        inline bool     intersectGet(const Segment& segment1, const Segment& segment2, float &dist, cocos2d::Vec2& point);
        
        inline bool     isContainPointInDiamond(const cocos2d::Vec2& diamondCenter, float halfLen, const cocos2d::Vec2& p);
        inline float    getAngleFromZero(const cocos2d::Vec2& point);
        
    };
    
    
}

#include "Physics.inl"




