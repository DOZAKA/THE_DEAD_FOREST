//
//  AnimationPlayer.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 14..
//  
//

#include "AnimationPlayer.hpp"
#include "AnimationBase.hpp"
#include "EntityHuman.hpp"
#include "HumanOwnedStates.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    AnimationPlayer::AnimationPlayer(EntityHuman* owner, AnimationBase* animation, int zOrder) :
        _owner(owner),
        _isReady(false),
        _accumulatedTime(0.0f)
    {
        _currAnimation = animation;
        
        _baseSprite = Sprite::create();
        _owner->addChild(_baseSprite);
        
        _shadowSprite = Sprite::create();
        _shadowSprite->setPosition(10.0f, -7.0f);
        _owner->addChild(_shadowSprite);
        
        _normalSprite = Sprite::create();
        _normalSprite->setVisible(false);
        _owner->addChild(_normalSprite);
        
        _baseSprite->setZOrder(zOrder);
        _shadowSprite->setZOrder(zOrder - 1);
        _normalSprite->setZOrder(zOrder + 1);
        
    }
    
    void AnimationPlayer::pushAnimationFrames(AnimationBase* animation)
    {
        if(_currAnimation->getPriority() <= animation->getPriority())
        {
            _frameQueue.clear();
        }
        
        int startIndex, endIndex;
        if(animation->isReversePlay() == true)
        {
            startIndex = animation->getMaxFrame() - 1;
            endIndex = animation->getStartFrame();
            for(int i = startIndex ; i >= endIndex; -- i)
            {
                std::string frameName = animation->getFileName() + _to_string(i);
                _frameQueue.push_back(std::make_pair(frameName, i));
            }
        }
        else
        {
            startIndex = animation->getStartFrame();
            endIndex = animation->getMaxFrame();
            for(int i = startIndex ; i < endIndex; ++ i)
            {
                std::string frameName = animation->getFileName() + _to_string(i);
                _frameQueue.push_back(std::make_pair(frameName, i));
            }
        }
        
        _currAnimation = animation;
    }
    
    void AnimationPlayer::pushFramesAtoB(AnimationBase* anim, int startIndex, int endIndex)
    {
        if(_currAnimation->getPriority() <= anim->getPriority())
        {
            _frameQueue.clear();
        }
        
        if( startIndex < endIndex )
        {
            if( startIndex < 0 || endIndex >= anim->getMaxFrame())
                return ;
            
            for(int i = startIndex ; i <= endIndex ; ++ i)
            {
                std::string frameName = anim->getFileName() + _to_string(i);
                _frameQueue.push_back(std::make_pair(frameName, i));
            }
        }
        else
        {
            if( endIndex < 0 || startIndex >= anim->getMaxFrame() )
                return ;
            
            for(int i = startIndex ; i >= endIndex ; -- i)
            {
                std::string frameName = anim->getFileName() + _to_string(i);
                _frameQueue.push_back(std::make_pair(frameName, i));
            }
        }
        
        _currAnimation = anim;
    }
    
    void AnimationPlayer::processAnimation(float dt)
    {
        if(_isReady == true || _frameQueue.empty() == true)
            return ;
        
        _accumulatedTime += dt;
        if(_currAnimation->getFrameSwapTime() <= _accumulatedTime)
        {
            _accumulatedTime = 0.0f;
            
            _currFrameName = _getFrameName();
            _baseSprite->setSpriteFrame(_currFrameName + ".png");
            _baseSprite->setRotation(_owner->getBodyRot());
            
            _shadowSprite->setSpriteFrame(_currFrameName + ".png");
            _shadowSprite->setColor(Color3B::BLACK);
            _shadowSprite->setRotation(_owner->getBodyRot());
            
            _normalSprite->setSpriteFrame(_currFrameName + "_n.png");
            _normalSprite->setRotation(_owner->getBodyRot());
            
            _isReady = false;
        }
    }
    
    std::string AnimationPlayer::_getFrameName()
    {
        std::string frame = _frameQueue.front().first;
        _frameQueue.pop_front();
        return frame;
    }
    
    int AnimationPlayer::getFrameIndex() const
    {
        return _frameQueue.front().second;
    }
    
    void AnimationPlayer::pushOneFrame(const std::pair<std::string, int>& pair_string_int)
    {
        _frameQueue.push_back(pair_string_int);
    }
    
    void AnimationPlayer::setVisible(bool enable)
    {
        _baseSprite->setVisible(enable);
    }
    
    void AnimationPlayer::enableShadow(bool enable)
    {
        _shadowSprite->setVisible(enable);
    }
    
    void AnimationPlayer::enableNormal(bool enable)
    {
        _normalSprite->setVisible(enable);
    }
}












