//
//  ImageFrame.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/9/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "ImageFrame.hpp"

namespace sea2d
{
    // Default Ctor
    ImageFrame::ImageFrame(const unsigned int newId, const Rect& rectDimensions, const int textureWidth, const int textureHeight, const unsigned int idOfTexture, const StringFixed& newName) :
        id(newId),
        normalizedDim(),
        pixelDimensions(rectDimensions),
        textureId(idOfTexture),
        name(newName)
    {
        // Calculate the normalized dimensions of this ImageFrame based off this frame's dimensions and texture dimensions
        normalizedDim.origin.x() = rectDimensions.origin.x() / (float) textureWidth;
        normalizedDim.origin.y() = rectDimensions.origin.y() / (float) textureHeight;
        normalizedDim.width = rectDimensions.width / (float) textureWidth;
        normalizedDim.height = rectDimensions.height / (float) textureHeight;
    }
    
    // Dtor
    ImageFrame::~ImageFrame()
    {
    }
    
    
    
    /// Get the ID of this ImageFrame (unique per Texture, NOT per game!)
    const unsigned int ImageFrame::GetId() const
    {
        return this->id;
    }
    
    /// Get the name of this ImageFrame
    const StringFixed& ImageFrame::GetName() const
    {
        return this->name;
    }
    
    /// Get the ID of the Texture holding this ImageFrame
    const unsigned int ImageFrame::GetTextureId() const
    {
        return this->textureId;
    }
    
    /// Get the pixel dimensions of this ImageFrame (to locate it on a Texture)
    const Rect& ImageFrame::GetPixelDimensions() const
    {
        return this->pixelDimensions;
    }
    
    /// Get the normalized dimensions of this ImageFrame (to use in shaders)
    const Rect& ImageFrame::GetNormalizedDimensions() const
    {
        return this->normalizedDim;
    }
    
}
