//
//  Texture.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/11/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <GL/gl3w.h>
#include "engine/DataTypes/StringFixed.hpp"
#include "engine/SpriteSys/ImageFrame.hpp"
#include "engine/DataTypes/LinkedList.hpp"

namespace sea2d
{
    /// Represents a 2D image in the GPU that is rendered onto a Mesh. Must be power-of-2 dimensions
    class Texture
    {
    public:
        
        //
        // Nested Enums
        //
        
        /// Represents texture sampling parameters
        enum class Sampling : int
        {
            Point,      ///< Samples nearest texture pixel
            Linear      ///< Blends nearest texture pixels linearly
        };
        
        
        
        
        //
        // Essentials
        //
        
        /// Constructor that takes in the texture filename (with extension), a name, and type of sampling
        Texture(const char* const filename, const char* const newName, const Texture::Sampling textureSampling);
        
        /// Destructor
        ~Texture();
        
        
        //
        // Methods
        //
        
        /// Make this texture the current texture when rendering in the draw loop
        void MakeActive();
        
        /// Set the sampling of this texture. Affects all sprites of this texture
        void SetSampling(const Texture::Sampling newSampling);
        
        /// Get the read only name of this texture
        const StringFixed& GetName() const;
        
        /// Get the instance ID of this texture (unique for every texture) (not OpenGL handle!)
        const unsigned int GetId() const;
        
        /// Get the width of this texture
        const int GetWidth() const;
        
        /// Get the height of this texture
        const int GetHeight() const;
        
        /// Get an ImageFrame from this Texture given the frame's ID (1 or more)
        ImageFrame* const GetImageFrame(const unsigned int frameId) const;
        
        /// Get an ImageFrame from this Texture given the frame's name
        ImageFrame* const GetImageFrame(const StringFixed& frameName) const;
        
        
    private:
        
        //
        // Data
        //
        
        GLuint textureHandle;                   ///< OpenGL handle to this texture
        LinkedList<ImageFrame> imageFrames;     ///< Every ImageFrame held in this Texture
        unsigned int id;                        ///< The engine id of this texture
        StringFixed name;                       ///< The name of this texture
        int width;                              ///< The width of the texture
        int height;                             ///< The height of the texture
        
        
        //
        // Deleted Methods
        //
        
        // No Default Ctor
        Texture() = delete;
        
        // No Copy Ctor
        Texture(const Texture& other) = delete;
        
        // No Copy Assignment
        Texture& operator=(const Texture& rhs) = delete;
        
    };
}

#endif /* Texture_hpp */
