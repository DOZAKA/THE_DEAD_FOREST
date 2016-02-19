//
//  HumanM16A2Animations.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 20..
//
//

#pragma once

#include "AnimationBase.hpp"
#include "Singleton.hpp"

namespace realtrick
{
    
    class AnimHumanM16A2IdleLoop : public AnimationBase, public Singleton<AnimHumanM16A2IdleLoop>
    {
        
    private:
        
        friend class Singleton<AnimHumanM16A2IdleLoop>;
        virtual ~AnimHumanM16A2IdleLoop() = default;
        
        AnimHumanM16A2IdleLoop()
        {
            _startFrame     = 0;
            _maxFrame       = 19;
            _fileName       = "HumanM16A2IdleLoop";
            _priority       = 0;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };
    
    
    class AnimHumanM16A2In : public AnimationBase, public Singleton<AnimHumanM16A2In>
    {
        
    private:
        
        friend class Singleton<AnimHumanM16A2In>;
        virtual ~AnimHumanM16A2In() = default;
        
        AnimHumanM16A2In()
        {
            _startFrame     = 0;
            _maxFrame       = 6;
            _fileName       = "HumanM16A2In";
            _priority       = 0;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };
    
    
    class AnimHumanM16A2Out : public AnimationBase, public Singleton<AnimHumanM16A2Out>
    {
        
    private:
        
        friend class Singleton<AnimHumanM16A2Out>;
        virtual ~AnimHumanM16A2Out() = default;
        
        AnimHumanM16A2Out()
        {
            _startFrame     = 0;
            _maxFrame       = 6;
            _fileName       = "HumanM16A2In";
            _priority       = 0;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = true;
        }
        
    };
    
    
    class AnimHumanM16A2MoveLoop : public AnimationBase, public Singleton<AnimHumanM16A2MoveLoop>
    {
        
    private:
        
        friend class Singleton<AnimHumanM16A2MoveLoop>;
        virtual ~AnimHumanM16A2MoveLoop() = default;
        
        AnimHumanM16A2MoveLoop()
        {
            _startFrame     = 0;
            _maxFrame       = 16;
            _fileName       = "HumanM16A2MoveLoop";
            _priority       = 3;
            _frameSwapTime  = 0.05f;
            _isReversePlay  = false;
        }
        
    };
    
    class AnimHumanM16A2Attack : public AnimationBase, public Singleton<AnimHumanM16A2Attack>
    {
        
    private:
        
        friend class Singleton<AnimHumanM16A2Attack>;
        virtual ~AnimHumanM16A2Attack() = default;
        
        AnimHumanM16A2Attack()
        {
            _startFrame     = 0;
            _maxFrame       = 6;
            _fileName       = "HumanM16A2Attack";
            _priority       = 3;
            _frameSwapTime  = 0.03f;
            _isReversePlay  = false;
        }
        
    };
    
    
    class AnimHumanM16A2Reload : public AnimationBase, public Singleton<AnimHumanM16A2Reload>
    {
        
    private:
        
        friend class Singleton<AnimHumanM16A2Reload>;
        virtual ~AnimHumanM16A2Reload() = default;
        
        AnimHumanM16A2Reload()
        {
            _startFrame     = 0;
            _maxFrame       = 27;
            _fileName       = "HumanM16A2Reload";
            _priority       = 3;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };
    
}




