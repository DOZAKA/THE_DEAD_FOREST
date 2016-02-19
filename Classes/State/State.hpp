//
//  State.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 12..
//  
//

#pragma once

namespace realtrick
{
    
    class Telegram;
    
    template <class entityType>
    class State
    {
        
    public:
        
        virtual ~State(){}
        virtual void enter(entityType*) = 0;
        virtual void execute(entityType*) = 0;
        virtual void exit(entityType*) = 0;
        virtual bool onMessage(entityType*, const Telegram&) = 0;
        
    };
    
}