//
//  RTTI.hpp
//  TheDeadForest
//
//  Created by mac on 2016. 1. 13..
//
//

#pragma once

#define DECLARE_ROOT_RTTI(className)                                            \
                                                                                \
public:                                                                         \
                                                                                \
    static const RTTI _rtti;                                                    \
    virtual const RTTI* getRTTI() const { return &_rtti; }                      \
                                                                                \
    static bool isKindOf(const RTTI* rtti, const className* object)             \
    {                                                                           \
        if (object == nullptr)                                                  \
            return false;                                                       \
        return object->isKindOf(rtti);                                          \
    }                                                                           \
                                                                                \
    bool isKindOf(const RTTI* rtti) const                                       \
    {                                                                           \
        const RTTI* temp = getRTTI();                                           \
        while ( temp != nullptr )                                               \
        {                                                                       \
            if (temp == rtti )                                                  \
            {                                                                   \
                return true;                                                    \
            }                                                                   \
            temp = temp->getBaseRTTI();                                         \
        }                                                                       \
        return false;                                                           \
    }                                                                           \
                                                                                \
    static className* dynamicCast(const RTTI* rtti, const className* object)    \
    {                                                                           \
        if ( !object )                                                          \
        {                                                                       \
            return nullptr;                                                     \
        }                                                                       \
        return object->dynamicCast(rtti);                                       \
    }                                                                           \
                                                                                \
    className* dynamicCast(const RTTI* rtti) const                              \
    {                                                                           \
        return (isKindOf(rtti) ? (className*)this : nullptr);                   \
    }                                                                           \




#define DECLARE_DERIVED_RTTI                                                    \
                                                                                \
public:                                                                         \
                                                                                \
    static const RTTI _rtti;                                                    \
    virtual const RTTI* getRTTI() const override { return &_rtti; }             \




#define IMPLEMENT_ROOT_RTTI(className)                                          \
const RTTI className::_rtti(nullptr)                                            \




#define IMPLEMENT_DERIVED_RTTI(className, baseClassName)                        \
const RTTI className::_rtti(&baseClassName::_rtti)




#define DynamicCast(className, object)                                          \
(className*)className::dynamicCast(&className::_rtti, object)

namespace realtrick
{
    
    class RTTI
    {
        
    public:
        
        RTTI(const RTTI* baseRTTI) : _baseRTTI(baseRTTI) {}
        const RTTI* getBaseRTTI() const            { return _baseRTTI; }
        
    private:
        
        const RTTI*             _baseRTTI;
        
    };
    
}





