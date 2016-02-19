//
//  MessageNode.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 2..
//
//

#pragma once

namespace realtrick
{
    
    class Telegram;
    
    class MessageNode
    {
        
    public:
        
        virtual bool handleMessage(const Telegram& msg) = 0;
        
    };
    
}