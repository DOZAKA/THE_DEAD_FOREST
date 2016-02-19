//
//  HumanAxeAnimations.hpp
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
    
    class AnimHumanAxeIdleLoop : public AnimationBase, public Singleton<AnimHumanAxeIdleLoop>
    {
        
    private:
        
        friend class Singleton<AnimHumanAxeIdleLoop>;
        virtual ~AnimHumanAxeIdleLoop() = default;
        
        AnimHumanAxeIdleLoop()
        {
            _startFrame     = 0;
            _maxFrame       = 20;
            _fileName       = "HumanAxeIdleLoop";
            _priority       = 0;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };

    
    class AnimHumanAxeOut : public AnimationBase, public Singleton<AnimHumanAxeOut>
    {
        
    private:
        
        friend class Singleton<AnimHumanAxeOut>;
        virtual ~AnimHumanAxeOut() = default;
        
        AnimHumanAxeOut()
        {
            _startFrame     = 0;
            _maxFrame       = 4;
            _fileName       = "HumanAxeIn";
            _priority       = 4;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = true;
        }
        
    };
    
    
    class AnimHumanAxeIn : public AnimationBase, public Singleton<AnimHumanAxeIn>
    {
        
    private:
        
        friend class Singleton<AnimHumanAxeIn>;
        virtual ~AnimHumanAxeIn() = default;
        
        AnimHumanAxeIn()
        {
            _startFrame     = 0;
            _maxFrame       = 4;
            _fileName       = "HumanAxeIn";
            _priority       = 4;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };
    
    
    
    class AnimHumanAxeMoveLoop : public AnimationBase, public Singleton<AnimHumanAxeMoveLoop>
    {
        
    private:
        
        friend class Singleton<AnimHumanAxeMoveLoop>;
        virtual ~AnimHumanAxeMoveLoop() = default;
        
        AnimHumanAxeMoveLoop()
        {
            _startFrame     = 0;
            _maxFrame       = 16;
            _fileName       = "HumanAxeMoveLoop";
            _priority       = 4;
            _frameSwapTime  = 0.05f;
            _isReversePlay  = false;
        }
        
    };
    
    
    class AnimHumanAxeAttack : public AnimationBase, public Singleton<AnimHumanAxeAttack>
    {
        
    private:
        
        friend class Singleton<AnimHumanAxeAttack>;
        virtual ~AnimHumanAxeAttack() = default;
        
        AnimHumanAxeAttack()
        {
            _startFrame     = 0;
            _maxFrame       = 18;
            _fileName       = "HumanAxeAttack";
            _priority       = 3;
            _frameSwapTime  = 0.07f;
            _isReversePlay  = false;
        }
        
    };
    
}









