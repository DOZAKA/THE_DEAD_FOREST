//
//  HumanDeadAnimations.hpp
//  TheDeadForest
//
//  Created by mac on 2015. 12. 27..
//
//

#pragma once

namespace realtrick
{
    
    class AnimHumanBackDead : public AnimationBase, public Singleton<AnimHumanBackDead>
    {
        
    private:
        
        friend class Singleton<AnimHumanBackDead>;
        virtual ~AnimHumanBackDead() = default;
        
        AnimHumanBackDead()
        {
            _startFrame     = 0;
            _maxFrame       = 14;
            _fileName       = "HumanBackDead";
            _priority       = 10;
            _frameSwapTime  = 0.07f;
            _isReversePlay  = false;
        }
        
    };
    

    
    class AnimHumanFrontDead : public AnimationBase, public Singleton<AnimHumanFrontDead>
    {
        
    private:
        
        friend class Singleton<AnimHumanFrontDead>;
        virtual ~AnimHumanFrontDead() = default;
        
        AnimHumanFrontDead()
        {
            _startFrame     = 0;
            _maxFrame       = 31;
            _fileName       = "HumanFrontDead";
            _priority       = 0;
            _frameSwapTime  = 0.07f;
            _isReversePlay  = false;
        }
        
    };
    
}









