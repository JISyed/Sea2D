//
//  CameraProjection.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/21/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef CameraProjection_hpp
#define CameraProjection_hpp

namespace sea2d
{
    /// Contains data about a camera's projection (only supports orthographical)
    struct CameraProjection
    {
        //
        // Methods
        //
        
        /// Default Ctor
        CameraProjection();
        
        /// Copy Ctor
        CameraProjection(const CameraProjection& other);
        
        /// Copy Assignment
        CameraProjection& operator=(const CameraProjection& other);
        
        /// Dtor
        ~CameraProjection();
        
        
        
        //
        // Data
        //
        
        float nearClip;     ///< The near clipping point
        float farClip;      ///< The far clipping point
        float rightEdge;    ///< The right edge of the view box
        float topEdge;      ///< The top edge of the view box
        float leftEdge;     ///< The left edge of the view box
        float bottomEdge;   ///< The bottom odge of the view box
    };
}

#endif /* CameraProjection_hpp */
