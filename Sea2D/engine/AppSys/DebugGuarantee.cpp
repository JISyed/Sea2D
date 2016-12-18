//
//  DebugGurarantee.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/24/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "DebugGuarantee.hpp"
#include <cassert>
#include <iostream>
#include <string>

namespace sea2d
{
    void s2d_guarantee_assertion(const bool condition, const char* const conditionExpression, const char* const errorMessage, const char* const filePath, const unsigned int lineNumber)
    {
    #ifdef NDEBUG
        condition;
        conditionExpression;
        errorMessage;
        filePath;
        lineNumber;
    #else
        // Print error if condition failed
        if(!condition)
        {
            std::string fullFilePath(filePath);
            std::size_t fileNameStartIndex = fullFilePath.find_last_of("/\\");
            std::string fileName = fullFilePath.substr(fileNameStartIndex + 1);
            
            std::cerr << "\n   !Guarantee Assertion Failed: {" << conditionExpression << "} \n      \"" << errorMessage << "\"\n      @File: " << fileName << ": Line " << lineNumber << std::endl << std::endl;
        }
        
        /////////////////////////////////
        // !!!! Go up the call stack !!!!
        assert(condition);
        /////////////////////////////////
        
    #endif
    }
}