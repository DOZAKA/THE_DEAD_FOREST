//
//  Inventory.hpp
//  TheDeadForest-v2
//
//  Created by mac on 2016. 2. 20..
//
//

#pragma once

#include "cocos2d.h"

namespace realtrick
{
    namespace userinterface
    {
        
        class Inventory : cocos2d::Node
        {
            
        public:
            
            static Inventory* create();
            
        private:
            
            Inventory();
            virtual ~Inventory();
            bool init() override;
            
        };
        
    }
}









