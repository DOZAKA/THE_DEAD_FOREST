//
//  MessageDispatcher.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 12..
//  
//

#pragma once

#include <set>

#include "MessageTypes.hpp"
#include "Singleton.hpp"

namespace realtrick
{
    class Telegram;
    class MessageNode;
    
#define Dispatch MessageDispatcher::getInstance()
    
    class MessageDispatcher : public Singleton<MessageDispatcher>
    {
        
    public:
        
        void pushMessage(double delaySeconds, MessageNode* receiver, MessageNode* sender, MessageType type, void* extraInfo);
        
        void dispatchDelayedMessages();
        
    private:
        
        std::set<Telegram>          _priorityQ;
        
    private:
        
        void _discharge(const Telegram& msg);
        
    };
    
}





