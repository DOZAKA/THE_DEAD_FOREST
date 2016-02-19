//
//  HumanM16A2States.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 14..
//
//

#include "HumanM16A2States.hpp"
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
    // HumanM16A2IdleLoop
    //
    void HumanM16A2IdleLoop::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanM16A2IdleLoop::getInstance());
    }
    
    void HumanM16A2IdleLoop::execute(EntityHuman* human)
    {
        if(human->getBodyAnimator()->isQueueEmpty())
        {
            human->getBodyAnimator()->pushAnimationFrames(&AnimHumanM16A2IdleLoop::getInstance());
        }
        
        int inputMask = human->getInputMask();
        Vec2 moving = human->getMoving();
        
        if ( isMasked(inputMask, (int)JoystickMessageTypes::RUN) )
        {
            human->getFSM()->changeState(&HumanM16A2MoveLoop::getInstance());
        }
        else if( isMasked(inputMask, (int)JoystickMessageTypes::MOVE) )
        {
            human->setVelocity( moving * human->getWalkSpeed() );
    
        }
        else
        {
            
        }
        
        if ( isMasked(inputMask, (int)JoystickMessageTypes::ATTACK_BEGAN) )
        {
            // attack button!
            human->getFSM()->changeState(&HumanM16A2Attack::getInstance());
        }
        
    }
    
    void HumanM16A2IdleLoop::exit(EntityHuman* human) {}
    bool HumanM16A2IdleLoop::onMessage(EntityHuman* human, const Telegram& msg)
    {
        if (msg.msg == MessageType::RELOAD_WEAPON)
        {
            int numOfLeftBullet = human->getEquipedWeapon()->getNumOfLeftRounds();
            if ( numOfLeftBullet == human->getEquipedWeapon()->getMaxRounds() )
            {
                log("<HumanM16A2IdleLoop::onMessage> Bullet is full!");
                return true;
            }
            
            return true;
        }
        else if ( msg.msg  == MessageType::RUN_BACK_DEAD )
        {
            log("dead!!!!");
            human->getFSM()->changeState(&HumanBackDead::getInstance());
            return true;
        }
        
        return false;
    }
    
    
    
    
    //
    // HumanM16A2Out
    //
    void HumanM16A2Out::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanM16A2Out::getInstance());
        
        AnimationBase* currAnim = human->getBodyAnimator()->getCurrAnimation();
        float animTime = currAnim->getMaxFrame() * currAnim->getFrameSwapTime();
        float weaponRange = human->getEquipedWeapon()->getRange();
        human->enableWeaponEquipped(false);
        human->getCrossHair()->runAction(Spawn::create(FadeTo::create(animTime, 255),
                                                        EaseElasticOut::create(MoveTo::create(animTime, human->getHeading() * weaponRange)),
                                                        nullptr));
    }
    
    void HumanM16A2Out::execute(EntityHuman* human)
    {
        if(human->getBodyAnimator()->isQueueEmpty())
        {
            human->getFSM()->changeState(&HumanM16A2IdleLoop::getInstance());
        }
    }
    
    void HumanM16A2Out::exit(EntityHuman* human) { human->enableWeaponEquipped(true); }
    bool HumanM16A2Out::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    
    //
    // HumanM16A2In
    //
    void HumanM16A2In::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanM16A2In::getInstance());
        
        AnimationBase* currAnim = human->getBodyAnimator()->getCurrAnimation();
        float animTime = currAnim->getMaxFrame() * currAnim->getFrameSwapTime();
        human->enableWeaponEquipped(false);
        human->getCrossHair()->runAction(FadeTo::create(animTime, 0));
    }
    
    void HumanM16A2In::execute(EntityHuman* human)
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
    
    void HumanM16A2In::exit(EntityHuman* human) {}
    bool HumanM16A2In::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    
    //
    // HumanM16A2MoveLoop
    //
    void HumanM16A2MoveLoop::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushFramesAtoB(&AnimHumanM16A2MoveLoop::getInstance(), 0, 5);
    }
    
    void HumanM16A2MoveLoop::execute(EntityHuman* human)
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
                human->getBodyAnimator()->pushFramesAtoB(&AnimHumanM16A2MoveLoop::getInstance(), 6, 11);
            }
            else if( currFrame == 11 )
            {
                human->getBodyAnimator()->pushFramesAtoB(&AnimHumanM16A2MoveLoop::getInstance(), 0, 5);
            }
        }
        else
        {
            if ( currFrame == 5 || currFrame == 11 )
            {
                human->setVelocity( Vec2::ZERO );
                human->getFSM()->changeState(&HumanM16A2IdleLoop::getInstance());
            }
        }
        
    }
    
    void HumanM16A2MoveLoop::exit(EntityHuman* human) {}
    bool HumanM16A2MoveLoop::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    //
    // HumanM16A2Attack
    //
    void HumanM16A2Attack::enter(EntityHuman* human)
    {
//        if ( human->getEquipedWeapon()->getNumOfLeftRounds() > 0 )
//        {
            // attack
            human->getEquipedWeapon()->attack();
            human->getBodyAnimator()->pushFramesAtoB(&AnimHumanM16A2Attack::getInstance(), 0, 5);
//        }
//        else
//        {
//            log("<HumanM16A2Attack::enter> Number Of Left Rounds is 0.");
//            human->getFSM()->changeState(&HumanM16A2IdleLoop::getInstance());
//        }
    }
    
    void HumanM16A2Attack::execute(EntityHuman* human)
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
            human->getFSM()->changeState(&HumanM16A2IdleLoop::getInstance());
        }
        
    }
    
    void HumanM16A2Attack::exit(EntityHuman* human) {}
    bool HumanM16A2Attack::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    //
    // HumanM16A2Reload
    //
    void HumanM16A2Reload::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanM16A2Reload::getInstance());
    }
    
    void HumanM16A2Reload::execute(EntityHuman* human)
    {
        int inputMask = human->getInputMask();
        Vec2 moving = human->getMoving();
        
        if( isMasked(inputMask, (int)JoystickMessageTypes::MOVE) )
        {
         
        }
        else
        {
            human->setVelocity( Vec2::ZERO );
        }

        if ( human->getBodyAnimator()->isQueueEmpty() )
        {
            // 필요한 총알의 수를 구한 후 그 만큼을 채워넣는다.
//            int currBullets = human->getEquipedWeapon()->getNumOfLeftRounds();
//            int needBullets = human->getEquipedWeapon()->getMaxRounds() - currBullets;
//            
//            InventoryEx* inventory = human->getGameManager()->getGameWorld()->getInventory();
//            int remainBullets = inventory->getItemAmount(EntityType::BULLET_556MM);
//            if ( remainBullets  > 0 )
//            {
//                if ( remainBullets <= needBullets )
//                {
//                    inventory->substractItem(EntityType::BULLET_556MM, remainBullets);
//                    human->getEquipedWeapon()->setNumOfLeftRounds(currBullets + remainBullets);
//                    log("<HumanM16A2Reload:execute> Reload %d bullets.", remainBullets);
//                }
//                else
//                {
//                    inventory->substractItem(EntityType::BULLET_556MM, needBullets);
//                    human->getEquipedWeapon()->setNumOfLeftRounds(currBullets + needBullets);
//                    log("<HumanM16A2Reload:execute> Reload %d bullets.", needBullets);
//                }
//            }
//            else
//            {
//                log("<HumanM16A2Reload:execute> No has bullet.");
//            }
//            
            human->getFSM()->changeState(&HumanM16A2IdleLoop::getInstance());
        }
        
    }
    
    void HumanM16A2Reload::exit(EntityHuman* human) {}
    bool HumanM16A2Reload::onMessage(EntityHuman* human, const Telegram& msg) { return false; }

}









