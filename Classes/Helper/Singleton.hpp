//
//  Singleton.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 12..
//  
//

#pragma once

namespace realtrick
{
    
    template <typename Derived>
    class Singleton
    {
        
    public:
        
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        
        static Derived& getInstance()
        {
            static Derived instance;
            return instance;
        }
        
    protected:
        
        Singleton() = default;
        virtual ~Singleton() = default;
        
    };
    
}