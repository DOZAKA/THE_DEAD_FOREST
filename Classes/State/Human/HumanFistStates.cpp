//
//  HumanFistStates.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 14..
//
//

#include "HumanFistStates.hpp"
#include "Telegram.hpp"
#include "MessageTypes.hpp"
#include "MessageDispatcher.hpp"
#include "EntityHuman.hpp"
#include "HumanOwnedAnimations.hpp"
#include "GameManager.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    //
    // HumanFistIdleLoop
    //
    void HumanFistIdleLoop::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanFistIdleLoop::getInstance());
    }
    
    void HumanFistIdleLoop::execute(EntityHuman* human)
    {
        if(human->getBodyAnimator()->isQueueEmpty())
        {
            human->getBodyAnimator()->pushAnimationFrames(&AnimHumanFistIdleLoop::getInstance());
        }
        
        int inputMask = human->getInputMask();
        Vec2 moving = human->getMoving();
        
        
        if ( isMasked(inputMask, (int)JoystickMessageTypes::RUN) )
        {
            human->getFSM()->changeState(&HumanFistMoveLoop::getInstance());
        }
        else if( isMasked(inputMask, (int)JoystickMessageTypes::MOVE) )
        {
            human->setVelocity( moving * 150.0f );
        }
        else
        {
           human->setVelocity( Vec2::ZERO );
        }
        
    }
    
    void HumanFistIdleLoop::exit(EntityHuman* human) {}
    bool HumanFistIdleLoop::onMessage(EntityHuman* human, const Telegram& msg)
    {
        if ( msg.msg  == MessageType::RUN_BACK_DEAD )
        {
            human->getFSM()->changeState(&HumanBackDead::getInstance());
            return true;
        }
        return false;
    }
    
    
    
    //
    // HumanFistOut
    //
    void HumanFistOut::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanFistOut::getInstance());
        
        AnimationBase* currAnim = human->getBodyAnimator()->getCurrAnimation();
        float animTime = currAnim->getMaxFrame() * currAnim->getFrameSwapTime();
        human->getCrossHair()->runAction(FadeTo::create(animTime, 0));
    }
    
    void HumanFistOut::execute(EntityHuman* human)
    {
        if(human->getBodyAnimator()->isQueueEmpty())
        {
            human->getFSM()->changeState(&HumanFistIdleLoop::getInstance());
        }
    }
    
    void HumanFistOut::exit(EntityHuman* human) {}
    bool HumanFistOut::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    //
    // HumanFistIn
    //
    void HumanFistIn::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanFistIn::getInstance());
        
        AnimationBase* currAnim = human->getBodyAnimator()->getCurrAnimation();
        float animTime = currAnim->getMaxFrame() * currAnim->getFrameSwapTime();
        human->getCrossHair()->runAction(FadeTo::create(animTime, 0));
    }
    
    void HumanFistIn::execute(EntityHuman* human)
    {
        if(human->getBodyAnimator()->isQueueEmpty())
        {
            human->getEquipedWeapon()->outWeapon();
        }
    }
    
    void HumanFistIn::exit(EntityHuman* human) {}
    bool HumanFistIn::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    //
    // HumanFistMoveLoop
    //
    void HumanFistMoveLoop::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushFramesAtoB(&AnimHumanFistMoveLoop::getInstance(), 0, 5);
    }
    
    void HumanFistMoveLoop::execute(EntityHuman* human)
    {
        int inputMask = human->getInputMask();
        Vec2 moving = human->getMoving();
        
        if( moving != Vec2::ZERO )
        {
            human->setTargetHeading(moving);
        }
        
        int currFrame = human->getBodyAnimator()->getFrameIndex();
        if ( isMasked(inputMask, (int)JoystickMessageTypes::RUN) )
        {
            human->setVelocity( moving * human->getRunSpeed() );
            
            if ( currFrame == 5 )
            {
                human->getBodyAnimator()->pushFramesAtoB(&AnimHumanFistMoveLoop::getInstance(), 6, 11);
            }
            else if( currFrame == 11 )
            {
                human->getBodyAnimator()->pushFramesAtoB(&AnimHumanFistMoveLoop::getInstance(), 0, 5);
            }
        }
        else
        {
            if ( currFrame == 5 || currFrame == 11 )
            {
                human->setVelocity( Vec2::ZERO );
                human->getFSM()->changeState(&HumanFistIdleLoop::getInstance());
            }
        }

    }
    
    void HumanFistMoveLoop::exit(EntityHuman* human) {}
    bool HumanFistMoveLoop::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
}









