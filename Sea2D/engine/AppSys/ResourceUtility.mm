//
//  ResourceUtility.mm
//  Sea2D
//
//  Created by Jibran Syed on 4/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "ResourceUtility.hpp"
#import <Foundation/Foundation.h>
#include "engine/AppSys/DebugGuarantee.hpp"

/// The vertex data that makes up a quad mesh
static float quadVertices[] = {
    // Positions        // Texture Coords
    0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // Top Right
    0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // Bottom Right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // Bottom Left
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // Top Left
};

/// The triangle index data that makes up a quad mesh
static unsigned int quadIndices[] = // Note that we start from 0!
{
    0, 1, 3,   // First Triangle
    1, 2, 3    // Second Triangle
};


namespace sea2d
{
    // STATIC
    /// Given a file name for a resource, get the full path in the app bundle
    const std::string ResouceUtility::GetFullPathForFileName(const char *const fileName)
    {
        /// Get the filename as an Objective-C string
        NSString* nsFileName = [NSString stringWithCString:fileName encoding:NSUTF8StringEncoding];
        
        /// Get the main bundle of this app
        NSBundle* theBundle = [NSBundle mainBundle];
        guarantee_that(theBundle != nil, "OS X found not find the main bundle for this app!");
        
        /// Get the resource directory and append the file name to the end
        NSString* path = [[theBundle resourcePath] stringByAppendingPathComponent:nsFileName];
        
        // Return the full file path as our string object
        return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
    }
    
    // STATIC
    /// Get all the data neede to make a quad mesh (using in-out returns)
    void ResouceUtility::GetQuadMesh(const float*& vertData, size_t& elementsInVertData, const unsigned int*& triangleData, size_t& elementsInTriangeData)
    {
        vertData = quadVertices;
        elementsInVertData = sizeof(quadVertices) / sizeof(float);
        triangleData = quadIndices;
        elementsInTriangeData = sizeof(quadIndices) / sizeof(unsigned int);
    }
}