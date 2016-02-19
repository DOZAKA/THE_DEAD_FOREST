//
//  HumanDeadStates.cpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 5..
//
//

#include "HumanDeadStates.hpp"
#include "Telegram.hpp"
#include "MessageTypes.hpp"
#include "MessageDispatcher.hpp"
#include "EntityHuman.hpp"
#include "HumanOwnedAnimations.hpp"
#include "GameManager.hpp"
#include "WeaponBase.hpp"
#include "GameWorld.hpp"


namespace realtrick
{
    
    //
    // HumanBackDead
    //
    void HumanBackDead::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanBackDead::getInstance());
        human->getBodyAnimator()->enableShadow(false);
    }
    
    void HumanBackDead::execute(EntityHuman* human)
    {
        if ( human->getBodyAnimator()->isQueueEmpty() )
        {
            human->getBodyAnimator()->pushOneFrame(std::make_pair("HumanBackDead13", 13));
        }
    }
    
    void HumanBackDead::exit(EntityHuman* human) {}
    bool HumanBackDead::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
    
    
    //
    // HumanFrontDead
    //
    void HumanFrontDead::enter(EntityHuman* human)
    {
        human->getBodyAnimator()->pushAnimationFrames(&AnimHumanFrontDead::getInstance());
    }
    
    void HumanFrontDead::execute(EntityHuman* human)
    {
        if ( human->getBodyAnimator()->isQueueEmpty() )
        {
            human->getBodyAnimator()->pushOneFrame(std::make_pair("HumanBackDead30", 30));
        }
    }
    
    void HumanFrontDead::exit(EntityHuman* human) {}
    bool HumanFrontDead::onMessage(EntityHuman* human, const Telegram& msg) { return false; }
    
}









