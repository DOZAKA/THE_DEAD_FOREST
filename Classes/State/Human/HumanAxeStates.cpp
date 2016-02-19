//
//  HumanAxeStates.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 14..
//
//

#include "HumanAxeStates.hpp"
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
    // HumanAxeIdleLoop
    //
    void HumanAxeIdleLoop::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanAxeIdleLoop::getInstance());
    }
    
    void HumanAxeIdleLoop::execute(EntityHuman* human)
    {
        if(human->getBodyAnimator()->isQueueEmpty())
        {
            human->getBodyAnimator()->pushAnimationFrames(&AnimHumanAxeIdleLoop::getInstance());
        }
        
        int inputMask = human->getInputMask();
        Vec2 moving = human->getMoving();
        
        if ( isMasked(inputMask, (int)JoystickMessageTypes::RUN) )
        {
            human->getFSM()->changeState(&HumanAxeMoveLoop::getInstance());
        }
        else if( isMasked(inputMask, (int)JoystickMessageTypes::MOVE) )
        {
            human->setVelocity( moving * human->getWalkSpeed() );
        }
        else
        {
            human->setVelocity( Vec2::ZERO );
        }
        
        if ( isMasked(inputMask, (int)JoystickMessageTypes::ATTACK_BEGAN) )
        {
            human->getFSM()->changeState(&HumanAxeAttack::getInstance());
        }
        
    }
    
    void HumanAxeIdleLoop::exit(EntityHuman* human) {}
    bool HumanAxeIdleLoop::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    
    //
    // HumanAxeOut
    //
    void HumanAxeOut::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanAxeOut::getInstance());
        
        AnimationBase* currAnim = human->getBodyAnimator()->getCurrAnimation();
        float animTime = currAnim->getMaxFrame() * currAnim->getFrameSwapTime();
        float weaponRange = human->getEquipedWeapon()->getRange();
        human->enableWeaponEquipped(false);
        human->getCrossHair()->runAction(Spawn::create(FadeTo::create(animTime, 255),
                                                        EaseElasticOut::create(MoveTo::create(animTime, human->getHeading() * weaponRange)),
                                                       nullptr));

    }
    
    void HumanAxeOut::execute(EntityHuman* human)
    {
        if(human->getBodyAnimator()->isQueueEmpty())
        {
            human->getFSM()->changeState(&HumanAxeIdleLoop::getInstance());
        }
    }
    
    void HumanAxeOut::exit(EntityHuman* human) { human->enableWeaponEquipped(true); }
    bool HumanAxeOut::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    
    //
    // HumanAxeIn
    //
    void HumanAxeIn::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanAxeIn::getInstance());
        
        AnimationBase* currAnim = human->getBodyAnimator()->getCurrAnimation();
        float animTime = currAnim->getMaxFrame() * currAnim->getFrameSwapTime();
        human->enableWeaponEquipped(false);
        human->getCrossHair()->runAction(FadeTo::create(animTime, 0));
    }
    
    void HumanAxeIn::execute(EntityHuman* human)
    {
        if(human->getBodyAnimator()->isQueueEmpty())
        {
            if( human->getEquipedWeapon() == nullptr )
            {
                human->getFSM()->changeState(&HumanFistOut::getInstance());
                return ;
            }
            
            human->getEquipedWeapon()->outWeapon();
        }
    }
    
    void HumanAxeIn::exit(EntityHuman* human) {}
    bool HumanAxeIn::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    
    //
    // HumanAxeMoveLoop
    //
    void HumanAxeMoveLoop::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushFramesAtoB(&AnimHumanAxeMoveLoop::getInstance(), 0, 5);
    }
    
    void HumanAxeMoveLoop::execute(EntityHuman* human)
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
                human->getBodyAnimator()->pushFramesAtoB(&AnimHumanAxeMoveLoop::getInstance(), 6, 11);
            }
            else if( currFrame == 11 )
            {
                human->getBodyAnimator()->pushFramesAtoB(&AnimHumanAxeMoveLoop::getInstance(), 0, 5);
            }
        }
        else
        {
            if ( currFrame == 5 || currFrame == 11 )
            {
                human->setVelocity( Vec2::ZERO );
                human->getFSM()->changeState(&HumanAxeIdleLoop::getInstance());
            }
        }
        
    }
    
    void HumanAxeMoveLoop::exit(EntityHuman* human) {}
    bool HumanAxeMoveLoop::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    //
    // HumanAxeAttack
    //
    void HumanAxeAttack::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushFramesAtoB(&AnimHumanAxeAttack::getInstance(), 0, 10);
    }
    
    void HumanAxeAttack::execute(EntityHuman* human)
    {
        int inputMask = human->getInputMask();
        Vec2 moving = human->getMoving();
        
        int currFrame = human->getBodyAnimator()->getFrameIndex();
        
        if( isMasked(inputMask, (int)JoystickMessageTypes::MOVE) )
        {
            human->setVelocity( moving * human->getWalkSpeed() );
        }
        else
        {
            human->setVelocity( Vec2::ZERO );
        }
        
        if ( currFrame == 10)
        {
            if ( isMasked(inputMask, (int)JoystickMessageTypes::ATTACK_BEGAN) )
            {
                human->getBodyAnimator()->pushOneFrame(std::make_pair("HumanAxeAttack10.png", 10));
            }
            else if ( isMasked(inputMask, (int)JoystickMessageTypes::ATTACK_ENDED) )
            {
                human->removeInputMask((int)JoystickMessageTypes::ATTACK_ENDED);
                human->getBodyAnimator()->pushFramesAtoB(&AnimHumanAxeAttack::getInstance(), 11, 17);

                // attack.
                human->getEquipedWeapon()->attack();
            }
        }
        else if ( currFrame < 10 )
        {
            if ( isMasked(inputMask, (int)JoystickMessageTypes::ATTACK_ENDED) )
            {
                human->removeInputMask((int)JoystickMessageTypes::ATTACK_ENDED);
                human->getBodyAnimator()->pushFramesAtoB(&AnimHumanAxeAttack::getInstance(), currFrame - 1, 0);
            }
        }
        
        if ( human->getBodyAnimator()->isQueueEmpty() )
        {
            human->getFSM()->changeState(&HumanAxeIdleLoop::getInstance());
        }
        
    }
    
    void HumanAxeAttack::exit(EntityHuman* human) {}
    bool HumanAxeAttack::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
}









