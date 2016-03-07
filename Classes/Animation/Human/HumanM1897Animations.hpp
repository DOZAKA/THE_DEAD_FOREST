//
//  HumanM1897Animations.hpp
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
    
    class AnimHumanM1897IdleLoop : public AnimationBase, public Singleton<AnimHumanM1897IdleLoop>
    {
        
    private:
        
        friend class Singleton<AnimHumanM1897IdleLoop>;
        virtual ~AnimHumanM1897IdleLoop() = default;
        
        AnimHumanM1897IdleLoop()
        {
            _startFrame     = 0;
            _maxFrame       = 20;
            _fileName       = "HumanM1897IdleLoop";
            _priority       = 0;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };
    
    
    class AnimHumanM1897In : public AnimationBase, public Singleton<AnimHumanM1897In>
    {
        
    private:
        
        friend class Singleton<AnimHumanM1897In>;
        virtual ~AnimHumanM1897In() = default;
        
        AnimHumanM1897In()
        {
            _startFrame     = 0;
            _maxFrame       = 5;
            _fileName       = "HumanM1897In";
            _priority       = 0;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = false;
        }
        
    };
    
    
    class AnimHumanM1897Out : public AnimationBase, public Singleton<AnimHumanM1897Out>
    {
        
    private:
        
        friend class Singleton<AnimHumanM1897Out>;
        virtual ~AnimHumanM1897Out() = default;
        
        AnimHumanM1897Out()
        {
            _startFrame     = 0;
            _maxFrame       = 5;
            _fileName       = "HumanM1897In";
            _priority       = 0;
            _frameSwapTime  = 0.1f;
            _isReversePlay  = true;
        }
        
    };
    
    
    class AnimHumanM1897MoveLoop : public AnimationBase, public Singleton<AnimHumanM1897MoveLoop>
    {
        
    private:
        
        friend class Singleton<AnimHumanM1897MoveLoop>;
        virtual ~AnimHumanM1897MoveLoop() = default;
        
        AnimHumanM1897MoveLoop()
        {
            _startFrame     = 0;
            _maxFrame       = 16;
            _fileName       = "HumanM1897MoveLoop";
            _priority       = 3;
            _frameSwapTime  = 0.05f;
            _isReversePlay  = false;
        }
        
    };
    
    class AnimHumanM1897Attack : public AnimationBase, public Singleton<AnimHumanM1897Attack>
    {
        
    private:
        
        friend class Singleton<AnimHumanM1897Attack>;
        virtual ~AnimHumanM1897Attack() = default;
        
        AnimHumanM1897Attack()
        {
            _startFrame     = 0;
            _maxFrame       = 17;
            _fileName       = "HumanM1897Attack";
            _priority       = 3;
            _frameSwapTime  = 0.06f;
            _isReversePlay  = false;
        }
        
    };
    
    
    class AnimHumanM1897Reload : public AnimationBase, public Singleton<AnimHumanM1897Reload>
    {
        
    private:
        
        friend class Singleton<AnimHumanM1897Reload>;
        virtual ~AnimHumanM1897Reload() = default;
        
        AnimHumanM1897Reload()
        {
            _startFrame     = 0;
            _maxFrame       = 9;
            _fileName       = "HumanM1897Reload";
            _priority       = 3;
            _frameSwapTime  = 0.14f;
            _isReversePlay  = false;
        }
        
    };
    
}




