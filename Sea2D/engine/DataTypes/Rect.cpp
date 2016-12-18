//
//  Rect.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/9/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Rect.hpp"

namespace sea2d
{
    Rect::Rect() :
        origin(0.0f, 0.0f),
        width(0.0f),
        height(0.0f)
    {
    }
    
    Rect::Rect(const float newX, const float newY, const float newWidth, const float newHeight) :
        origin(newX, newY),
        width(newWidth),
        height(newHeight)
    {
    }
    
    Rect::Rect(const Vector2& newOrigin, const float newWidth, const float newHeight) :
        origin(newOrigin),
        width(newWidth),
        height(newHeight)
    {
    }
    
}
