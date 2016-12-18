//
//  CameraViewport.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/23/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef CameraViewport_hpp
#define CameraViewport_hpp

namespace sea2d
{
    /// Contains data about a camera's mapping onto the OpenGL viewport
    struct CameraViewport
    {
        //
        // Methods
        //
        
        /// Default Ctor
        CameraViewport();
        
        /// Copy Ctor
        CameraViewport(const CameraViewport& other);
        
        /// Copy Assignment
        CameraViewport& operator=(const CameraViewport& other);
        
        /// Dtor
        ~CameraViewport();
        
        
        
        //
        // Data
        //
        
        int originX;    ///< X origin (lower left corner)
        int originY;    ///< Y origin (lower left corner)
        int width;      ///< Width of viewport
        int height;     ///< Height of viewport
        
    };

}

#endif /* CameraViewport_hpp */
