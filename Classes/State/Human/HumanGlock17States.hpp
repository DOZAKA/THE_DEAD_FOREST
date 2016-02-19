#pragma once

#include "State.hpp"
#include "Singleton.hpp"

namespace realtrick
{
    
    class EntityHuman;
    class Telegram;
    
    
    
    //
    // HumanGlock17IdleLoop
    //
    class HumanGlock17IdleLoop : public State<EntityHuman>, public Singleton<HumanGlock17IdleLoop>
    {
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    private:
        
        friend Singleton<HumanGlock17IdleLoop>;
        HumanGlock17IdleLoop() = default;
        virtual ~HumanGlock17IdleLoop() = default;
        
    };
    
    
    
    
    //
    // HumanGlock17IdleToMove
    //
    class HumanGlock17IdleToMove : public State<EntityHuman>, public Singleton<HumanGlock17IdleToMove>
    {
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    private:
        
        friend Singleton<HumanGlock17IdleToMove>;
        HumanGlock17IdleToMove() = default;
        virtual ~HumanGlock17IdleToMove() = default;
        
    };
    
    
    
    //
    // HumanGlock17MoveToIdle
    //
    class HumanGlock17MoveToIdle : public State<EntityHuman>, public Singleton<HumanGlock17MoveToIdle>
    {
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    private:
        
        friend Singleton<HumanGlock17MoveToIdle>;
        HumanGlock17MoveToIdle() = default;
        virtual ~HumanGlock17MoveToIdle() = default;
        
    };
    
    
    //
    // HumanGlock17Out
    //
    class HumanGlock17Out : public State<EntityHuman>, public Singleton<HumanGlock17Out>
    {
        
    private:
        
        friend Singleton<HumanGlock17Out>;
        HumanGlock17Out() = default;
        virtual ~HumanGlock17Out() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
    
    
    //
    // HumanGlock17In
    //
    class HumanGlock17In : public State<EntityHuman>, public Singleton<HumanGlock17In>
    {
        
    private:
        
        friend Singleton<HumanGlock17In>;
        HumanGlock17In() = default;
        virtual ~HumanGlock17In() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
    
    
    //
    // HumanGlock17MoveLoop
    //
    class HumanGlock17MoveLoop : public State<EntityHuman>, public Singleton<HumanGlock17MoveLoop>
    {
        
    private:
        
        friend Singleton<HumanGlock17MoveLoop>;
        HumanGlock17MoveLoop() = default;
        virtual ~HumanGlock17MoveLoop() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
    
    //
    // HumanGlock17Attack
    //
    class HumanGlock17Attack : public State<EntityHuman>, public Singleton<HumanGlock17Attack>
    {
        
    private:
        
        friend Singleton<HumanGlock17Attack>;
        HumanGlock17Attack() = default;
        virtual ~HumanGlock17Attack() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
    //
    // HumanGlock17Reload
    //
    class HumanGlock17Reload : public State<EntityHuman>, public Singleton<HumanGlock17Reload>
    {
        
    private:
        
        friend Singleton<HumanGlock17Reload>;
        HumanGlock17Reload() = default;
        virtual ~HumanGlock17Reload() = default;
        
    public:
        
        virtual void enter(EntityHuman* human) override;
        virtual void execute(EntityHuman* human) override;
        virtual void exit(EntityHuman* human) override;
        virtual bool onMessage(EntityHuman* human, const Telegram& msg) override;
        
    };
    
}









