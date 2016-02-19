//
//  ParamLoader.cpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 10. 20..
//
//

#include "ParamLoader.hpp"

namespace realtrick
{
    
    //
    // Constructor
    //
    ParamLoader::ParamLoader()
    {
        _fileName = "Params.ini";
        cocos2d::FileUtils* fileUtils = cocos2d::FileUtils::getInstance();
        std::string fullPathFile = fileUtils->fullPathForFilename(_fileName);
        if ( fullPathFile.empty() )
        {
            throw std::runtime_error("<ParamLoader::ParamLoader> " + _fileName + " is not exist.");
        }
        else
        {
            _fileData = fileUtils->getStringFromFile(fullPathFile);
            _pointer = 0;
            _parse(); // start parse
        }
    }
    
    void ParamLoader::_parse()
    {
        while( _fileData.size() > _pointer )
        {
            std::string::size_type end = _fileData.find_first_of('\n', _pointer);
            std::string line = _fileData.substr(_pointer, end - _pointer);
            _removeCommentFromLine(line);
            if ( line.empty() )
            {
                const std::string::size_type interval = end - _pointer;
                _pointer += interval + 1;
                continue;
            }
            
            std::string::size_type begIdx;
            std::string::size_type endIdx;
            const std::string delims(" \\;=,");
            
            // find key
            begIdx = line.find_first_not_of(delims);
            if(begIdx != std::string::npos)
            {
                endIdx = line.find_first_of(delims, begIdx);
                if( endIdx == std::string::npos)
                {
                    endIdx = line.size();
                }
            }
            std::string key = line.substr(begIdx, endIdx);
            
            // find value
            begIdx = line.find_first_not_of(delims, endIdx);
            if(begIdx != std::string::npos)
            {
                endIdx = line.find_first_of(delims, begIdx);
                if(endIdx == std::string::npos)
                {
                    endIdx = line.size();
                }
            }
            std::string value = line.substr(begIdx, endIdx);
            
            // insert key, value
            _container.insert(std::make_pair(key, value));
            
            // go to next line
            const std::string::size_type interval = end - _pointer;
            _pointer += interval + 1;
        }
    }
    
    
    //
    // RemoveCommentFromLine
    //
    void ParamLoader::_removeCommentFromLine(std::string& line)
    {
        std::string::size_type idx = line.find("--");
        if(idx != std::string::npos)
        {
            line = line.substr(0, idx);
        }
    }
    
    
    
}





