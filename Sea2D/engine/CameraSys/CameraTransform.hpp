//
//  CameraTransform.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/21/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef CameraTransform_hpp
#define CameraTransform_hpp

#include "engine/MathSys/Vector2.hpp"

namespace sea2d
{
    /// Contains data about a camera's position and rotation in the world
    struct CameraTransform
    {
        //
        // Methods
        //
        
        /// Default Ctor
        CameraTransform();
        
        /// Copy Ctor
        CameraTransform(const CameraTransform& other);
        
        /// Copy Assignment
        CameraTransform& operator=(const CameraTransform& other);
        
        /// Dtor
        ~CameraTransform();
        
        
        
        //
        // Data
        //
        
        Vector2 position;   ///< The world space position of the camera
        float rotation;     ///< The world space rotation of the camera (in radians)
        
    };
}

#endif /* CameraTransform_hpp */
