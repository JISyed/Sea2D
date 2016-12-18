//
//  ImageFrame.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/9/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef ImageFrame_hpp
#define ImageFrame_hpp

#include "engine/DataTypes/StringFixed.hpp"
#include "engine/DataTypes/Rect.hpp"

namespace sea2d
{
    /// Represents a portion of a Texture used to construct a Sprite.
    /// (One Sprite can be made of multiple ImageFrames)
    class ImageFrame
    {
    public:
        
        //
        // Essentials
        //
        
        /// Ctor
        ImageFrame(const unsigned int newId, const Rect& rectDimensions, const int textureWidth, const int textureHeight, const unsigned int idOfTexture, const StringFixed& newName);
        
        /// Destructor
        ~ImageFrame();
        
        
        //
        // Methods
        //
        
        /// Get the ID of this ImageFrame (unique per Texture, NOT per game!)
        const unsigned int GetId() const;
        
        /// Get the name of this ImageFrame
        const StringFixed& GetName() const;
        
        /// Get the ID of the Texture holding this ImageFrame
        const unsigned int GetTextureId() const;
        
        /// Get the pixel dimensions of this ImageFrame (to locate it on a Texture)
        const Rect& GetPixelDimensions() const;
        
        /// Get the normalized dimensions of this ImageFrame (to use in shaders)
        const Rect& GetNormalizedDimensions() const;
        
        
    private:
        
        //
        // Data
        //
        
        unsigned int id;        ///< The ID of this image frame (unique per Texture)
        Rect normalizedDim;     ///< The normalized dimensions of this frame in a Texture
        Rect pixelDimensions;   ///< The pixel dimensions of this frame within a Texture
        unsigned int textureId; ///< The ID of the texture holding this image frame
        StringFixed name;       ///< The name of this image frame
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Default Ctor
        ImageFrame() = delete;
        
        /// No Copy Ctor
        ImageFrame(const ImageFrame& other) = delete;
        
        /// No Copy Assignment
        ImageFrame& operator=(const ImageFrame& rhs) = delete;
        
    };
}
#endif /* ImageFrame_hpp */
