#pragma once

#include "State.hpp"
#include "Singleton.hpp"

namespace realtrick
{
    
    class EntityHuman;
    class Telegram;
    
    
    
    //
    // HumanAxeIdleLoop
    //
    class HumanAxeIdleLoop : public State<EntityHuman>, public Singleton<HumanAxeIdleLoop>
    {
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    private:
        
        friend Singleton<HumanAxeIdleLoop>;
        HumanAxeIdleLoop() = default;
        virtual ~HumanAxeIdleLoop() = default;
        
    };
    
    
    
    //
    // HumanAxeOut
    //
    class HumanAxeOut : public State<EntityHuman>, public Singleton<HumanAxeOut>
    {
        
    private:
        
        friend Singleton<HumanAxeOut>;
        HumanAxeOut() = default;
        virtual ~HumanAxeOut() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
    
    
    //
    // HumanAxeIn
    //
    class HumanAxeIn : public State<EntityHuman>, public Singleton<HumanAxeIn>
    {
        
    private:
        
        friend Singleton<HumanAxeIn>;
        HumanAxeIn() = default;
        virtual ~HumanAxeIn() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
    
    
    //
    // HumanAxeMoveLoop
    //
    class HumanAxeMoveLoop : public State<EntityHuman>, public Singleton<HumanAxeMoveLoop>
    {
        
    private:
        
        friend Singleton<HumanAxeMoveLoop>;
        HumanAxeMoveLoop() = default;
        virtual ~HumanAxeMoveLoop() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
    
    //
    // HumanAxeAttack
    //
    class HumanAxeAttack : public State<EntityHuman>, public Singleton<HumanAxeAttack>
    {
        
    private:
        
        friend Singleton<HumanAxeAttack>;
        HumanAxeAttack() = default;
        virtual ~HumanAxeAttack() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
}









