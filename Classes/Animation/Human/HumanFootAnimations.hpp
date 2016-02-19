//
//  HumanFootAnimations.hpp
//  TheDeadForest
//
//  Created by mac on 2015. 12. 27..
//
//

#pragma once

namespace realtrick
{
    
    class AnimHumanFootFront : public AnimationBase, public Singleton<AnimHumanFootFront>
    {
        
    private:
        
        friend class Singleton<AnimHumanFootFront>;
        virtual ~AnimHumanFootFront() = default;
        
        AnimHumanFootFront()
        {
            _startFrame     = 0;
            _maxFrame       = 6;
            _fileName       = "HumanFoot";
            _priority       = 0;
            _frameSwapTime  = 0.07f;
            _isReversePlay  = false;
        }
        
    };
    
    class AnimHumanFootBack : public AnimationBase, public Singleton<AnimHumanFootBack>
    {
        
    private:
        
        friend class Singleton<AnimHumanFootBack>;
        virtual ~AnimHumanFootBack() = default;
        
        AnimHumanFootBack()
        {
            _startFrame     = 6;
            _maxFrame       = 12;
            _fileName       = "HumanFoot";
            _priority       = 0;
            _frameSwapTime  = 0.07f;
            _isReversePlay  = false;
        }
        
    };
    
}