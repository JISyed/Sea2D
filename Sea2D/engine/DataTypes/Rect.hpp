//
//  Rect.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/9/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef Rect_hpp
#define Rect_hpp

#include "engine/MathSys/Vector2.hpp"

namespace sea2d
{
    struct Rect
    {
        //
        // Methods
        //
        
        /// Default Ctor (0, 0, 0, 0)
        Rect();
        
        /// All Floats Ctor
        Rect(const float newX, const float newY, const float newWidth, const float newHeight);
        
        /// Vector2 and Floats Ctor
        Rect(const Vector2& newOrigin, const float newWidth, const float newHeight);
        
        
        //
        // Data
        //
        
        Vector2 origin;
        float width;
        float height;
        
    };
}
#endif /* Rect_hpp */
