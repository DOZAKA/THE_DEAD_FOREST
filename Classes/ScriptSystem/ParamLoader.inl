//
//  ParamLoader.inl
//  TheDeadForest
//
//  Created by 남준현 on 2015. 10. 20..
//
//

#include "ParamLoader.hpp"

namespace realtrick
{
    
    inline double ParamLoader::getValueAsDouble(const std::string& key) const
    {
        try {
            return atof(_container.at(key).c_str());
        } catch (std::exception& e) {
            cocos2d::log("[\"%s\"] %s",key.c_str(), e.what());
            return 0.0;
        }
    }
    
    inline float ParamLoader::getValueAsFloat(const std::string& key) const
    {
        try {
            return (float)atof(_container.at(key).c_str());
        } catch (std::exception& e) {
            cocos2d::log("[\"%s\"] %s",key.c_str(), e.what());
            return 0.0f;
        }
    }
    
    inline int ParamLoader::getValueAsInt(const std::string& key) const
    {
        try {
            return atoi(_container.at(key).c_str());
        } catch (std::exception& e) {
            cocos2d::log("[\"%s\"] %s",key.c_str(), e.what());
            return 0;
        }
    }
    
    inline std::string ParamLoader::getValueAsString(const std::string& key) const
    {
        try {
            return _container.at(key);
        } catch (std::exception& e) {
            cocos2d::log("[\"%s\"] %s",key.c_str(), e.what());
            return 0;
        }
    }
    
    inline bool ParamLoader::getValueAsBool(const std::string& key) const
    {
        try {
            return _container.at(key) == "true" ? true : false;
        } catch (std::exception& e) {
            cocos2d::log("[\"%s\"] %s",key.c_str(), e.what());
            return false;
        }
    }
    
}





