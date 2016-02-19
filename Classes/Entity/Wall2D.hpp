//
//  Wall2D.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 12. 5..
//
//

#pragma once

#include "Physics.hpp"
#include "cocos2d.h"

namespace realtrick
{
    
    class Wall2D
    {
    
    public:
        
        Wall2D() = default;
        
        Wall2D(const Segment& seg) : _seg(seg)
        {
            _calculateNormal();
        }
        
        Segment         getSegment() const              { return _seg; }
        
        cocos2d::Vec2   getNormal() const               { return _normal; }
        
        void reverseNormal()                            { _normal *= -1; }
        
        void setSegment(const Segment& seg)
        {
            _seg = seg;
            _calculateNormal();
        }
      
    private:
        
        Segment             _seg;
        
        cocos2d::Vec2       _normal;
        
    private:
        
        void _calculateNormal()
        {
            _normal = (_seg.end - _seg.start).getPerp();
        }
        
    };
    
}







