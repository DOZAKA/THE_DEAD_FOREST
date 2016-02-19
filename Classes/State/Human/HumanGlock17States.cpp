//
//  HumanGlock17States.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 14..
//
//

#include "HumanGlock17States.hpp"
#include "Telegram.hpp"
#include "MessageTypes.hpp"
#include "MessageDispatcher.hpp"
#include "EntityHuman.hpp"
#include "HumanOwnedAnimations.hpp"
#include "GameManager.hpp"
#include "WeaponBase.hpp"
#include "GameWorld.hpp"

using namespace cocos2d;

namespace realtrick
{
    
    //
    // HumanGlock17IdleLoop
    //
    void HumanGlock17IdleLoop::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanGlock17IdleLoop::getInstance());
    }
    
    void HumanGlock17IdleLoop::execute(EntityHuman* human)
    {
        if(human->getBodyAnimator()->isQueueEmpty())
        {
            human->getBodyAnimator()->pushAnimationFrames(&AnimHumanGlock17IdleLoop::getInstance());
        }
        
        int inputMask = human->getInputMask();
        Vec2 moving = human->getMoving();
        
        if ( isMasked(inputMask, (int)JoystickMessageTypes::RUN) )
        {
            human->getFSM()->changeState(&HumanGlock17IdleToMove::getInstance());
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
            // attack button!
            human->getFSM()->changeState(&HumanGlock17Attack::getInstance());
        }
        
    }
    
    void HumanGlock17IdleLoop::exit(EntityHuman* human) {}
    bool HumanGlock17IdleLoop::onMessage(EntityHuman* human, const Telegram& msg)
    {
        if (msg.msg == MessageType::RELOAD_WEAPON)
        {
            int numOfLeftBullet = human->getEquipedWeapon()->getNumOfLeftRounds();
            if ( numOfLeftBullet == human->getEquipedWeapon()->getMaxRounds() )
            {
                log("<HumanGlock17IdleLoop::onMessage> Bullet is full!");
                return true;
            }
            
            return true;
        }
        return false;
    }
    
    
    //
    // HumanGlock17IdleToMove
    //
    void HumanGlock17IdleToMove::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanGlock17IdleToMove::getInstance());
    }
    
    void HumanGlock17IdleToMove::execute(EntityHuman* human)
    {
        int inputMask = human->getInputMask();
        Vec2 moving = human->getMoving();
        
        if ( isMasked(inputMask, (int)JoystickMessageTypes::RUN) )
        {
            if ( human->getBodyAnimator()->isQueueEmpty() )
            {
                 human->getFSM()->changeState(&HumanGlock17MoveLoop::getInstance());
            }
        }
        else
        {
            
        }
    }
    
    void HumanGlock17IdleToMove::exit(EntityHuman* human) {}
    bool HumanGlock17IdleToMove::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    
    //
    // HumanGlock17MoveToIdle
    //
    void HumanGlock17MoveToIdle::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanGlock17MoveToIdle::getInstance());
    }
    
    void HumanGlock17MoveToIdle::execute(EntityHuman* human)
    {
        if ( human->getBodyAnimator()->isQueueEmpty() )
        {
            human->getFSM()->changeState(&HumanGlock17IdleLoop::getInstance());
        }
    }
    
    void HumanGlock17MoveToIdle::exit(EntityHuman* human) {}
    bool HumanGlock17MoveToIdle::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
      
    
    
    
    //
    // HumanGlock17Out
    //
    void HumanGlock17Out::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanGlock17Out::getInstance());
        
        AnimationBase* currAnim = human->getBodyAnimator()->getCurrAnimation();
        float animTime = currAnim->getMaxFrame() * currAnim->getFrameSwapTime();
        float weaponRange = human->getEquipedWeapon()->getRange();
        human->enableWeaponEquipped(false);
        human->getCrossHair()->runAction(Spawn::create(FadeTo::create(animTime, 255),
                                                       EaseElasticOut::create(MoveTo::create(animTime, human->getHeading() * weaponRange)),
                                                       nullptr));
    }
    
    void HumanGlock17Out::execute(EntityHuman* human)
    {
        if(human->getBodyAnimator()->isQueueEmpty())
        {
            human->getFSM()->changeState(&HumanGlock17IdleLoop::getInstance());
        }
    }
    
    void HumanGlock17Out::exit(EntityHuman* human) { human->enableWeaponEquipped(true); }
    bool HumanGlock17Out::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    
    //
    // HumanGlock17In
    //
    void HumanGlock17In::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanGlock17In::getInstance());
        
        AnimationBase* currAnim = human->getBodyAnimator()->getCurrAnimation();
        float animTime = currAnim->getMaxFrame() * currAnim->getFrameSwapTime();
        human->enableWeaponEquipped(false);
        human->getCrossHair()->runAction(FadeTo::create(animTime, 0));
    }
    
    void HumanGlock17In::execute(EntityHuman* human)
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
    
    void HumanGlock17In::exit(EntityHuman* human) {}
    bool HumanGlock17In::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    
    //
    // HumanGlock17MoveLoop
    //
    void HumanGlock17MoveLoop::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushFramesAtoB(&AnimHumanGlock17MoveLoop::getInstance(), 0, 7);
    }
    
    void HumanGlock17MoveLoop::execute(EntityHuman* human)
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
            
            if ( currFrame == 7 )
            {
                human->getBodyAnimator()->pushFramesAtoB(&AnimHumanGlock17MoveLoop::getInstance(), 8, 15);
            }
            else if( currFrame == 15 )
            {
                human->getBodyAnimator()->pushFramesAtoB(&AnimHumanGlock17MoveLoop::getInstance(), 0, 7);
            }
        }
        else
        {
            if ( currFrame == 7 || currFrame == 15 )
            {
                human->setVelocity( Vec2::ZERO );
                human->getFSM()->changeState(&HumanGlock17IdleLoop::getInstance());
            }
        }
        
    }
    
    void HumanGlock17MoveLoop::exit(EntityHuman* human) {}
    bool HumanGlock17MoveLoop::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    //
    // HumanGlock17Attack
    //
    void HumanGlock17Attack::enter(EntityHuman* human)
    {
        if ( human->getEquipedWeapon()->getNumOfLeftRounds() > 0 )
        {
            // attack
            human->getEquipedWeapon()->attack();
            human->getBodyAnimator()->pushAnimationFrames(&AnimHumanGlock17Attack::getInstance());
        }
        else
        {
            log("<HumanGlock17Attack::enter> Number Of Left Rounds is 0.");
            human->getFSM()->changeState(&HumanGlock17IdleLoop::getInstance());
        }
    }
    
    void HumanGlock17Attack::execute(EntityHuman* human)
    {
        int inputMask = human->getInputMask();
        Vec2 moving = human->getMoving();
        
        if( isMasked(inputMask, (int)JoystickMessageTypes::MOVE) )
        {
            human->setVelocity( moving * human->getWalkSpeed() );
        }
        else
        {
            human->setVelocity( Vec2::ZERO );
        }
        
        if ( isMasked(inputMask, (int)JoystickMessageTypes::ATTACK_ENDED) )
        {
            human->removeInputMask((int)JoystickMessageTypes::ATTACK_ENDED);
        }
        
        if ( human->getBodyAnimator()->isQueueEmpty() )
        {
            human->getFSM()->changeState(&HumanGlock17IdleLoop::getInstance());
        }
        
    }
    
    void HumanGlock17Attack::exit(EntityHuman* human) {}
    bool HumanGlock17Attack::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    //
    // HumanGlock17Reload
    //
    void HumanGlock17Reload::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanGlock17Reload::getInstance());
    }
    
    void HumanGlock17Reload::execute(EntityHuman* human)
    {
        int inputMask = human->getInputMask();
        Vec2 moving = human->getMoving();
        
        if( isMasked(inputMask, (int)JoystickMessageTypes::MOVE) )
        {
            human->setVelocity( moving * human->getWalkSpeed() );
        }
        else
        {
            human->setVelocity( Vec2::ZERO );
        }
        
        if ( human->getBodyAnimator()->isQueueEmpty() )
        {
            // 필요한 총알의 수를 구한 후 그 만큼을 채워넣는다.
            human->getFSM()->changeState(&HumanGlock17IdleLoop::getInstance());
        }
        
    }
    
    void HumanGlock17Reload::exit(EntityHuman* human) {}
    bool HumanGlock17Reload::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
}









