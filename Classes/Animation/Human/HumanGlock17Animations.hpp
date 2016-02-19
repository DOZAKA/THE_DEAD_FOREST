//
//  HumanGlock17Animations.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 10..
//
//

#pragma once

#include "AnimationBase.hpp"
#include "Singleton.hpp"

namespace realtrick
{
    
    class AnimHumanGlock17IdleLoop : public AnimationBase, public Singleton<AnimHumanGlock17IdleLoop>
    {
        
    private:
        
        friend class Singleton<AnimHumanGlock17IdleLoop>;
        virtual ~AnimHumanGlock17IdleLoop() = default;
        
        AnimHumanGlock17IdleLoop()
        {
            _startFrame     = 0;
            _maxFrame       = 19;
            _fileName       = "HumanGlock17IdleLoop";
            _priority       = 0;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };
    
    class AnimHumanGlock17IdleToMove : public AnimationBase, public Singleton<AnimHumanGlock17IdleToMove>
    {
        
    private:
        
        friend class Singleton<AnimHumanGlock17IdleToMove>;
        virtual ~AnimHumanGlock17IdleToMove() = default;
        
        AnimHumanGlock17IdleToMove()
        {
            _startFrame     = 0;
            _maxFrame       = 4;
            _fileName       = "HumanGlock17IdleToMove";
            _priority       = 1;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };
    
    
    class AnimHumanGlock17MoveToIdle : public AnimationBase, public Singleton<AnimHumanGlock17MoveToIdle>
    {
        
    private:
        
        friend class Singleton<AnimHumanGlock17MoveToIdle>;
        virtual ~AnimHumanGlock17MoveToIdle() = default;
        
        AnimHumanGlock17MoveToIdle()
        {
            _startFrame     = 0;
            _maxFrame       = 4;
            _fileName       = "HumanGlock17MoveToIdle";
            _priority       = 1;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };
    
    class AnimHumanGlock17In : public AnimationBase, public Singleton<AnimHumanGlock17In>
    {
        
    private:
        
        friend class Singleton<AnimHumanGlock17In>;
        virtual ~AnimHumanGlock17In() = default;
        
        AnimHumanGlock17In()
        {
            _startFrame     = 0;
            _maxFrame       = 4;
            _fileName       = "HumanGlock17In";
            _priority       = 0;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };
    
    
    class AnimHumanGlock17Out : public AnimationBase, public Singleton<AnimHumanGlock17Out>
    {
        
    private:
        
        friend class Singleton<AnimHumanGlock17Out>;
        virtual ~AnimHumanGlock17Out() = default;
        
        AnimHumanGlock17Out()
        {
            _startFrame     = 0;
            _maxFrame       = 4;
            _fileName       = "HumanGlock17In";
            _priority       = 0;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = true;
        }
        
    };
    
    
    class AnimHumanGlock17MoveLoop : public AnimationBase, public Singleton<AnimHumanGlock17MoveLoop>
    {
        
    private:
        
        friend class Singleton<AnimHumanGlock17MoveLoop>;
        virtual ~AnimHumanGlock17MoveLoop() = default;
        
        AnimHumanGlock17MoveLoop()
        {
            _startFrame     = 0;
            _maxFrame       = 16;
            _fileName       = "HumanGlock17MoveLoop";
            _priority       = 3;
            _frameSwapTime  = 0.05f;
            _isReversePlay  = false;
        }
        
    };
    
    class AnimHumanGlock17Attack : public AnimationBase, public Singleton<AnimHumanGlock17Attack>
    {
        
    private:
        
        friend class Singleton<AnimHumanGlock17Attack>;
        virtual ~AnimHumanGlock17Attack() = default;
        
        AnimHumanGlock17Attack()
        {
            _startFrame     = 0;
            _maxFrame       = 5;
            _fileName       = "HumanGlock17Attack";
            _priority       = 3;
            _frameSwapTime  = 0.03f;
            _isReversePlay  = false;
        }
        
    };
    
    
    class AnimHumanGlock17Reload : public AnimationBase, public Singleton<AnimHumanGlock17Reload>
    {
        
    private:
        
        friend class Singleton<AnimHumanGlock17Reload>;
        virtual ~AnimHumanGlock17Reload() = default;
        
        AnimHumanGlock17Reload()
        {
            _startFrame     = 0;
            _maxFrame       = 17;
            _fileName       = "HumanGlock17Reload";
            _priority       = 3;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };
    
}




