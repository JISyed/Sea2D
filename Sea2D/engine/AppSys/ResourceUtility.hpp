//
//  ResourceUtility.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef ResourceUtility_hpp
#define ResourceUtility_hpp

#include <string>

namespace sea2d
{
    /// Utility class that performs operations on game resources
    class ResouceUtility
    {
    public:
        
        //
        // Methods
        //
        
        /// Given a file name for a resource, get the full path in the app bundle
        static const std::string GetFullPathForFileName(const char* const fileName);
        
        /// Get all the data neede to make a quad mesh (using in-out returns)
        static void GetQuadMesh(const float*& vertData, size_t& elementsInVertData, const unsigned int*& triangleData, size_t& elementsInTriangeData);
        
    private:
        
        //
        // Deleted Methods
        //
        
        // No Default Ctor
        ResouceUtility() = delete;
        
        // No Copy Ctor
        ResouceUtility(const ResouceUtility& other) = delete;
        
        // No Copy Assignment
        ResouceUtility& operator=(const ResouceUtility& rhs) = delete;
        
        // No Destructor
        ~ResouceUtility() = delete;
        
        
    };
}

#endif /* ResourceUtility_hpp */
