//
//  CameraViewport.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/23/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "CameraViewport.hpp"
#include "engine/AppSys/App.hpp"

namespace sea2d
{
    // Default Ctor
    CameraViewport::CameraViewport() :
        originX(0),
        originY(0),
        width((int)App::GetWindowWidth()),
        height((int)App::GetWindowHeight())
    {
        
    }
    
    // Copy Ctor
    CameraViewport::CameraViewport(const CameraViewport& other) :
        originX(other.originX),
        originY(other.originY),
        width(other.width),
        height(other.height)
    {
    }
    
    // Copy Assignment Overload
    CameraViewport& CameraViewport::operator=(const CameraViewport& rhs)
    {
        if(this != &rhs)
        {
            this->originX = rhs.originX;
            this->originY = rhs.originY;
            this->width = rhs.width;
            this->height = rhs.height;
        }
        
        return *this;
    }
    
    // Dtor
    CameraViewport::~CameraViewport()
    {
    }

}