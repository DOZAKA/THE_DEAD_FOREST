//
//  HumanDeadStates.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 2. 5..
//
//

#pragma once

#include "State.hpp"
#include "Singleton.hpp"

namespace realtrick
{
    
    class EntityHuman;
    class Telegram;
    
    //
    // HumanBackDead
    //
    class HumanBackDead : public State<EntityHuman>, public Singleton<HumanBackDead>
    {
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    private:
        
        friend Singleton<HumanBackDead>;
        HumanBackDead() = default;
        virtual ~HumanBackDead() = default;
        
    };
    
    
    //
    // HumanFrontDead
    //
    class HumanFrontDead : public State<EntityHuman>, public Singleton<HumanFrontDead>
    {
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    private:
        
        friend Singleton<HumanFrontDead>;
        HumanFrontDead() = default;
        virtual ~HumanFrontDead() = default;
        
    };

}









