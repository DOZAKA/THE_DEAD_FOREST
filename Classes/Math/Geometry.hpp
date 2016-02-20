//
//  Geometry.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 12..
//  
//

#pragma once

#include <vector>
#include <chrono>

#include "Mat3.hpp"

namespace realtrick
{
    
    class Rect
    {
    
    public:
    
        cocos2d::Vec2           origin;
        
        float                   width;
        
        float                   height;
    
        Rect();
        
        Rect(float x, float y, float width, float height);
        
        Rect(const cocos2d::Vec2& pos, float width, float height);
        
        Rect(const Rect& copy);
        
        Rect& operator=(const Rect& rhs);
        
        void setRect(float x, float y, float width, float height);
        
        float getMinX() const;
        
        float getMidX() const;
        
        float getMaxX() const;
        
        float getMinY() const;
        
        float getMidY() const;
        
        float getMaxY() const;
        
        bool equals(const Rect& rect) const;
        
        bool containPoint(const cocos2d::Vec2& point) const;
        
        static const Rect ZERO;
    
        virtual ~Rect() {}
        
    };

    class Circle
    {
      
    public:
        
        cocos2d::Vec2           origin;
        
        float                   radius;
        
        Circle();
        
        Circle(float x, float y, float r);
        
        Circle(const cocos2d::Vec2& origin, float r);
        
        Circle(const Circle& copy);
        
        Circle& operator=(const Circle& rhs);
        
        void setCircle(float x, float y, float r);
        
        Circle getTranslatedCircle(const cocos2d::Vec2& dir, float distance);
        
        bool containPoint(const cocos2d::Vec2& point) const;
        
        static const Circle ZERO;
        
        virtual ~Circle() {}
        
    };
    
    
    
    class Segment
    {
        
    public:
        
        cocos2d::Vec2         start;
        
        cocos2d::Vec2         end;
        
        Segment();
        
        Segment(float sx, float sy, float ex, float ey);
        
        Segment(const cocos2d::Vec2& start, const cocos2d::Vec2& end);
        
        Segment(const Segment& copy);
        
        Segment& operator=(const Segment& rhs);
        
        void setSegment(float sx, float sy, float ex, float dy);
        
        cocos2d::Vec2 getDirection() const;
        
        float getDistance() const;
        
        float getDistanceSq() const;
        
        bool containPoint(const cocos2d::Vec2& point) const;
        
        virtual ~Segment() {}
    };

    class Polygon
    {
        
    public:
        
        std::vector<cocos2d::Vec2> vertices;
        
        Polygon();
        
        Polygon(const std::vector<cocos2d::Vec2>& segs);
        
        Polygon(const Polygon& copy);
        
        Polygon& operator=(const Polygon& rhs);
        
        void setPolygon(const std::vector<cocos2d::Vec2>& segs);
        
        void pushVertex(const cocos2d::Vec2 point);
        
        bool containPoint(const cocos2d::Vec2& point) const;
        
        virtual ~Polygon() { vertices.clear(); }
        
    };
    
    
    inline bool isEqual(float a, float b)
    {
        if (fabs(a-b) < 1E-12)
        {
            return true;
        }
        
        return false;
    }
    
    inline bool IsZero(float val)
    {
        return (-std::numeric_limits<float>::min() < val && val < std::numeric_limits<float>::min());
    }
    
}








