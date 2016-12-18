//
//  Sprite.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef Sprite_hpp
#define Sprite_hpp

#include "ImageFrame.hpp"
#include "engine/DataTypes/StringFixed.hpp"
#include "SpriteAnimationData.hpp"

namespace sea2d
{
    // Forward declare Texture
    class Texture;
    
    /// A 2D image that can be rendered. Can be optionally animated if specified in its definition file
    class Sprite
    {
    public:
        
        //
        // Essentials
        //
        
        /// Ctor
        Sprite(const StringFixed& newName, const unsigned int numOfFrames, ImageFrame** const framesArray, SpriteAnimationData* const newAnimation, Texture* const originatingTexture);
        
        /// Destructor
        ~Sprite();
        
        
        //
        // Methods
        //
        
        /// Get the unique ID for this sprite
        const unsigned GetId() const;
        
        /// Get the name of this sprite
        const StringFixed& GetName() const;
        
        /// Indexer to get to an frame in the imageFrames array. Don't go out of bounds!
        const ImageFrame* const operator[](const unsigned int index) const;
        
        /// Get the number of frames in this sprite
        const unsigned int GetNumberOfFrames() const;
        
        /// Get the animation data of this sprite, if any. Will return null if sprite is not animated
        const SpriteAnimationData* const GetAnimationData() const;
        
        /// Get the texture from which this sprite originates
        Texture* const GetOriginatingTexture() const;
        
        
    private:
        
        //
        // Data
        //
        
        unsigned int id;                ///< The unique ID of this sprite
        ImageFrame** imageFrames;       ///< The ImageFrames that make up this sprite
        unsigned int numberOfFrames;    ///< The number of frames for this animation
        const SpriteAnimationData* animation; ///< Animation data for this sprite, if any
        Texture* textureOfOrigin;       ///< Texture that this sprite originates from
        StringFixed name;               ///< The name of this sprite
        
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Default Ctor
        Sprite() = delete;
        
        /// No Copy Ctor
        Sprite(const Sprite& other) = delete;
        
        /// No Copy Assignment
        Sprite& operator=(const Sprite& rhs) = delete;
        
    };
}
#endif /* Sprite_hpp */
