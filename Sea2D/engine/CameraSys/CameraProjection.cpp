//
//  CameraProjection.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/21/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "CameraProjection.hpp"

namespace sea2d
{
    // Default Ctor
    CameraProjection::CameraProjection() :
        nearClip(1.0f),
        farClip(500.0f),
        rightEdge(1.0f),
        topEdge(1.0f),
        leftEdge(0.0f),
        bottomEdge(0.0f)
    {
    }
    
    // Copy Ctor
    CameraProjection::CameraProjection(const CameraProjection& other) :
        nearClip(other.nearClip),
        farClip(other.farClip),
        rightEdge(other.rightEdge),
        topEdge(other.topEdge),
        leftEdge(other.leftEdge),
        bottomEdge(other.bottomEdge)
    {
    }
    
    // Copy Assignment Overload
    CameraProjection& CameraProjection::operator=(const CameraProjection& rhs)
    {
        if(this != &rhs)
        {
            this->nearClip = rhs.nearClip;
            this->farClip = rhs.farClip;
            this->rightEdge = rhs.rightEdge;
            this->topEdge = rhs.topEdge;
            this->leftEdge = rhs.leftEdge;
            this->bottomEdge = rhs.bottomEdge;
        }
        
        return *this;
    }
    
    // Dtor
    CameraProjection::~CameraProjection()
    {
    }
}