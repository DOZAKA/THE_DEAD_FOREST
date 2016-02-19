//
//  MessageDispatcher.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 12..
//  
//

#include <chrono>

#include "MessageDispatcher.hpp"
#include "MessageNode.hpp"
#include "Telegram.hpp"

#include "cocos2d.h"

namespace realtrick
{

    void MessageDispatcher::_discharge(const Telegram& msg)
    {
        bool ret = msg.receiver->handleMessage(msg);
        if( ret == false)
        {
            cocos2d::log("<MessageDispatcher:_discharge> Message is not handled.");
        }
    }
    
    void MessageDispatcher::pushMessage(double delaySeconds,
                                        MessageNode* receiver,
                                        MessageNode* sender,
                                        MessageType type,
                                        void* extraInfo)
    {
        Telegram tel(delaySeconds, receiver, sender, type, extraInfo);
        if(tel.dispatchTime <= std::chrono::duration<double>::zero())
        {
            _discharge(tel);
        }
        else
        {
            std::chrono::duration<double> curr = std::chrono::system_clock::now().time_since_epoch();
            tel.dispatchTime += curr;
            _priorityQ.insert(tel);
        }
    }
    
    void MessageDispatcher::dispatchDelayedMessages()
    {
        std::chrono::duration<double> curr = std::chrono::system_clock::now().time_since_epoch();
        
        while (!_priorityQ.empty() &&
               (_priorityQ.begin()->dispatchTime < curr) &&
               (_priorityQ.begin()->dispatchTime >= std::chrono::duration<double>::zero()))
        {
            const Telegram& telegram = *_priorityQ.begin();
            _discharge(telegram);
            _priorityQ.erase(_priorityQ.begin());
        }
    }
    
}










