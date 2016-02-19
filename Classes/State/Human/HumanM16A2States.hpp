#pragma once

#include "State.hpp"
#include "Singleton.hpp"

namespace realtrick
{
    
    class EntityHuman;
    class Telegram;
    
    
    
    //
    // HumanM16A2IdleLoop
    //
    class HumanM16A2IdleLoop : public State<EntityHuman>, public Singleton<HumanM16A2IdleLoop>
    {
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    private:
        
        friend Singleton<HumanM16A2IdleLoop>;
        HumanM16A2IdleLoop() = default;
        virtual ~HumanM16A2IdleLoop() = default;
        
    };
    
    
    
    //
    // HumanM16A2Out
    //
    class HumanM16A2Out : public State<EntityHuman>, public Singleton<HumanM16A2Out>
    {
        
    private:
        
        friend Singleton<HumanM16A2Out>;
        HumanM16A2Out() = default;
        virtual ~HumanM16A2Out() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
    
    
    //
    // HumanM16A2In
    //
    class HumanM16A2In : public State<EntityHuman>, public Singleton<HumanM16A2In>
    {
        
    private:
        
        friend Singleton<HumanM16A2In>;
        HumanM16A2In() = default;
        virtual ~HumanM16A2In() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
    
    
    //
    // HumanM16A2MoveLoop
    //
    class HumanM16A2MoveLoop : public State<EntityHuman>, public Singleton<HumanM16A2MoveLoop>
    {
        
    private:
        
        friend Singleton<HumanM16A2MoveLoop>;
        HumanM16A2MoveLoop() = default;
        virtual ~HumanM16A2MoveLoop() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
    
    //
    // HumanM16A2Attack
    //
    class HumanM16A2Attack : public State<EntityHuman>, public Singleton<HumanM16A2Attack>
    {
        
    private:
        
        friend Singleton<HumanM16A2Attack>;
        HumanM16A2Attack() = default;
        virtual ~HumanM16A2Attack() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
    //
    // HumanM16A2Reload
    //
    class HumanM16A2Reload : public State<EntityHuman>, public Singleton<HumanM16A2Reload>
    {
        
    private:
        
        friend Singleton<HumanM16A2Reload>;
        HumanM16A2Reload() = default;
        virtual ~HumanM16A2Reload() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
}









