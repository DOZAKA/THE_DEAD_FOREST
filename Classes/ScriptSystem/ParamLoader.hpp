//
//  ParamLoader.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 10. 20..
//
//

#pragma once

#include <unordered_map>
#include <string>

#include "cocos2d.h"
#include "Singleton.hpp"

namespace realtrick
{
    
#define Prm ParamLoader::getInstance()
    
    class ParamLoader : public Singleton<ParamLoader>
    {
    
    public:
        
        virtual ~ParamLoader()
        {
            _container.clear();
        }
        
        inline double           getValueAsDouble(const std::string& key) const;
        inline float            getValueAsFloat(const std::string& key) const;
        inline int              getValueAsInt(const std::string& key) const;
        inline std::string      getValueAsString(const std::string& key) const;
        inline bool             getValueAsBool(const std::string& key) const;
        
        friend Singleton<ParamLoader>;
        
    private:
        
        std::unordered_map<std::string, std::string>        _container;
        std::string                                         _fileName;
        std::string                                         _fileData;
        std::string::size_type                              _pointer;
        
    private:
        
        void                        _parse();
        void                        _removeCommentFromLine(std::string& line);
        ParamLoader();
        
    };
    
}

#include "ParamLoader.inl"





