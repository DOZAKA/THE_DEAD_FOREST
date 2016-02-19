//
//  StateMachine.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 12..
//  
//

#pragma once

#include "Telegram.hpp"
#include "State.hpp"
#include "HumanOwnedStates.hpp"


namespace realtrick
{
    
    template <class entityType>
    class StateMachine
    {
        
    public:
        
        StateMachine(entityType* owner) :
        _owner(owner),
        _currState(nullptr),
        _prevState(nullptr),
        _globalState(nullptr) {}
        
        virtual ~StateMachine() {}
        
        void setCurrState(State<entityType>* s)     { _currState = s; }
        void setPrevState(State<entityType>* s)     { _prevState = s; }
        void setGlobalState(State<entityType>* s)   { _globalState = s; }
        
        State<entityType>* getCurrState() const     { return _currState; }
        State<entityType>* getPrevState() const     { return _prevState; }
        State<entityType>* getGlobalState() const   { return _globalState; }
        
        void update(float dt)
        {
            if(_currState)
            {
                _currState->execute(_owner);
            }
            
            if(_globalState)
            {
                _globalState->execute(_owner);
            }
        }
        
        bool handleMessage(const Telegram& msg)
        {
            int flag {};
            if(_currState)
            {
                if(_currState->onMessage(_owner, msg))
                {
                    flag ++;
                }
            }
            if(_globalState)
            {
                if(_globalState->onMessage(_owner, msg))
                {
                    flag ++;
                }
            }
            if( flag > 0)
                return true;
            
            return false;
        }
        
        void changeState(State<entityType>* newState)
        {
            _prevState = _currState;
            _currState->exit(_owner);
            _currState = newState;
            _currState->enter(_owner);
        }
        
        void revertToPreviousState()
        {
            changeState(_prevState);
        }
        
    private:
        
        entityType*             _owner;
        State<entityType>*      _currState;
        State<entityType>*      _prevState;
        State<entityType>*      _globalState;
        
    };
    
    
}








