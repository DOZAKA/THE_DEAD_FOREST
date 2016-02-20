//
//  Inventory.cpp
//  TheDeadForest-v2
//
//  Created by mac on 2016. 2. 20..
//
//

#include "Inventory.hpp"

namespace realtrick
{
    namespace userinterface
    {
        
        Inventory::Inventory()
        {}
        
        
        Inventory::~Inventory()
        {
            
        }
        
        
        Inventory* Inventory::create()
        {
            Inventory* ret = new (std::nothrow) Inventory();
            if ( ret && ret->init() )
            {
                ret->autorelease();
                return ret;
            }
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
        
        
        bool Inventory::init()
        {
            if ( !Node::init() )
                return false;
            
            return true;
        }
        
    }
}









