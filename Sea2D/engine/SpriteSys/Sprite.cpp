//
//  Sprite.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Sprite.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include "engine/AppSys/IdGenerator.hpp"
#include "engine/GraphicsSys/Texture.hpp"

namespace sea2d
{
    //
    // Statics
    //
    
    static IdGenerator s_idGen;
    
    
    
    //
    // Methods
    //
    
    // Ctor
    Sprite::Sprite(const StringFixed& newName, const unsigned int numOfFrames, ImageFrame** const framesArray, SpriteAnimationData* const newAnimation, Texture* const originatingTexture) :
        id(s_idGen.MakeNewId()),
        imageFrames(framesArray),
        numberOfFrames(numOfFrames),
        animation(newAnimation),
        textureOfOrigin(originatingTexture),
        name(newName)
    {
        guarantee_that(numOfFrames > 0, "A Sprite cannot have 0 frames!");
        guarantee_that(framesArray != nullptr, "Making a Sprite but ImageFrame data is null!");
    }

    // Dtor
    Sprite::~Sprite()
    {
        delete [] this->imageFrames;
        
        if(this->animation != nullptr)
        {
            delete this->animation;
        }
    }
    
    
    /// Get the unique ID for this sprite
    const unsigned Sprite::GetId() const
    {
        return this->id;
    }
    
    /// Get the name of this sprite
    const StringFixed& Sprite::GetName() const
    {
        return this->name;
    }
    
    /// Indexer to get to an frame in the imageFrames array. Don't go out of bounds!
    const ImageFrame* const Sprite::operator[](const unsigned int index) const
    {
        guarantee_that(index < this->numberOfFrames, "Sprite Indexer[] -> ImageFrame: Out of Bounds!");
        
        return this->imageFrames[index];
    }
    
    /// Get the number of frames in this sprite
    const unsigned int Sprite::GetNumberOfFrames() const
    {
        return this->numberOfFrames;
    }
    
    /// Get the animation data of this sprite, if any. Will return null if sprite is not animated
    const SpriteAnimationData* const Sprite::GetAnimationData() const
    {
        return this->animation;
    }
    
    /// Get the texture from which this sprite originates
    Texture* const Sprite::GetOriginatingTexture() const
    {
        return this->textureOfOrigin;
    }
    
}
