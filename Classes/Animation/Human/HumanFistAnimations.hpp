//
//  HumanFistAnimations.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 14..
//
//

#pragma once

#include "AnimationBase.hpp"
#include "Singleton.hpp"

namespace realtrick
{
    
    class AnimHumanFistIdleLoop : public AnimationBase, public Singleton<AnimHumanFistIdleLoop>
    {
        
    private:
        
        friend class Singleton<AnimHumanFistIdleLoop>;
        virtual ~AnimHumanFistIdleLoop() = default;
        
        AnimHumanFistIdleLoop()
        {
            _startFrame     = 0;
            _maxFrame       = 21;
            _fileName       = "HumanFistIdleLoop";
            _priority       = 0;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };
    
    
    class AnimHumanFistOut : public AnimationBase, public Singleton<AnimHumanFistOut>
    {
        
    private:
        
        friend class Singleton<AnimHumanFistOut>;
        virtual ~AnimHumanFistOut() = default;
        
        AnimHumanFistOut()
        {
            _startFrame     = 0;
            _maxFrame       = 5;
            _fileName       = "HumanFistIn";
            _priority       = 0;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = true;
        }
        
    };
    
    
    class AnimHumanFistIn : public AnimationBase, public Singleton<AnimHumanFistIn>
    {
        
    private:
        
        friend class Singleton<AnimHumanFistIn>;
        virtual ~AnimHumanFistIn() = default;
        
        AnimHumanFistIn()
        {
            _startFrame     = 0;
            _maxFrame       = 5;
            _fileName       = "HumanFistIn";
            _priority       = 0;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };
    
    
    
    class AnimHumanFistMoveLoop : public AnimationBase, public Singleton<AnimHumanFistMoveLoop>
    {
        
    private:
        
        friend class Singleton<AnimHumanFistMoveLoop>;
        virtual ~AnimHumanFistMoveLoop() = default;
        
        AnimHumanFistMoveLoop()
        {
            _startFrame     = 0;
            _maxFrame       = 12;
            _fileName       = "HumanFistMoveLoop";
            _priority       = 4;
            _frameSwapTime  = 0.05f;
            _isReversePlay  = false;
        }
        
    };
    
    
    class AnimHumanFistAttack : public AnimationBase, public Singleton<AnimHumanFistAttack>
    {
        
    private:
        
        friend class Singleton<AnimHumanFistAttack>;
        virtual ~AnimHumanFistAttack() = default;
        
        AnimHumanFistAttack()
        {
            _startFrame     = 0;
            _maxFrame       = 10;
            _fileName       = "HumanFistAttack";
            _priority       = 3;
            _frameSwapTime  = 0.07f;
            _isReversePlay  = false;
        }
        
    };
    
}









