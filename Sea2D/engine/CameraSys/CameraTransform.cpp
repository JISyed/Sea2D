//
//  CameraTransform.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/21/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "CameraTransform.hpp"

namespace sea2d
{
    // Default Ctor
    CameraTransform::CameraTransform() :
        position(0.0f, 0.0f),
        rotation(0.0f)
    {
        
    }
    
    // Copy Ctor
    CameraTransform::CameraTransform(const CameraTransform& other) :
        position(other.position),
        rotation(other.rotation)
    {
    }
    
    // Copy Assignment Overload
    CameraTransform& CameraTransform::operator=(const CameraTransform& rhs)
    {
        if(this != &rhs)
        {
            this->position = rhs.position;
            this->rotation = rhs.rotation;
        }
        
        return *this;
    }
    
    // Dtor
    CameraTransform::~CameraTransform()
    {
    }
}