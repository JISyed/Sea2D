//
//  Texture.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/11/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Texture.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include <string>
#include "engine/AppSys/ResourceUtility.hpp"
#include "engine/AppSys/IdGenerator.hpp"
#include <yaml-cpp/yaml.h>
#include <cstdio>
#include "engine/YamlConverters/YamlRectConverter.hpp"
#include "engine/YamlConverters/YamlStringFixedConverter.hpp"

// Define these STBI macros in only one file that includes stb_image.h
#define STBI_NO_JPEG
#define STBI_NO_BMP
#define STBI_NO_PSD
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM
#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>


// Texture Options
#define S2D_DEF_TEX_WRAP                GL_CLAMP_TO_EDGE
#define S2D_DEF_TEX_TARGET              GL_TEXTURE_2D
#define S2D_IMG_FORMAT_GPU              GL_RGBA
#define S2D_IMG_FORMAT_SRC              GL_RGBA
#define S2D_SPRITE_SHEET_DEF_EXT        ".yml"
#define S2D_SPRITE_SHEET_YML_BASE_KEY   "ImageFrames"


namespace sea2d
{
    //
    // Statics
    //
    
    /// Generates IDs for every texture when the game runs
    static IdGenerator s_idGen;
    
    
    
    //
    // Methods
    //
    
    /// Constructor that takes in the texture filename (with extension) and a name
    Texture::Texture(const char* const filename, const char* const newName, const Texture::Sampling textureSampling) :
        textureHandle(0u),
        imageFrames(),
        id(s_idGen.MakeNewId()),
        name(newName),
        width(0),
        height(0)
    {
        guarantee_that(filename != nullptr, "Texture: Filename is null!");
        guarantee_that(newName != nullptr, "Texture: Name string is null");
        
        
        
        // --- Texture Setup --- //
        
        
        
        // Generate a new texture object in OpenGL for this instance
        glGenTextures(1, &this->textureHandle);
        
        // Make this texture active (Texture Unit 0, 2D Texture)
        this->MakeActive();
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        // Set wrapping
        glTexParameteri(S2D_DEF_TEX_TARGET, GL_TEXTURE_WRAP_S, S2D_DEF_TEX_WRAP);
        glTexParameteri(S2D_DEF_TEX_TARGET, GL_TEXTURE_WRAP_T, S2D_DEF_TEX_WRAP);
        
        // Set texture sampling (called filtering in OpenGL)
        this->SetSampling(textureSampling);
        
        // Load the image from file
        stbi_set_flip_vertically_on_load(GL_TRUE);
        const std::string filePath = ResouceUtility::GetFullPathForFileName(filename);
        int imgWidth = 0;
        int imgHeight = 0;
        int bytesPerPixel = 0;
        unsigned char* imgData = stbi_load(filePath.c_str(), &imgWidth, &imgHeight, &bytesPerPixel, STBI_rgb_alpha);
        
        // Set texture dimensions
        this->width = imgWidth;
        this->height = imgHeight;
        
        // Image needs to be PNG or TGA with 4-channel (RBGA)
        guarantee_that(imgData != nullptr, "Texture: Image failed to load! Make sure it's 4 channel PNG or TGA. Or add it to the app bundle!");
        
        // Only RGBA texture are supported (ie: there must be an alpha)
        guarantee_that(bytesPerPixel == 4, "Texture: Image has to be 4 bytes per pixel (RGBA)");
        
        // Image should have valid dimensions
        guarantee_that(imgWidth != 0, "Texture: Width is 0");
        guarantee_that(imgHeight != 0, "Texture: Height is 0");
        
        // Upload the image into the GPU
        glTexImage2D(S2D_DEF_TEX_TARGET,     // Texture Target (2D, 3D, etc)
                     0,                 // Level of detail,
                     S2D_IMG_FORMAT_GPU,// Image format in GPU
                     imgWidth,          // Width of texture in pixels
                     imgHeight,         // Height of texture in pixels
                     0,                 // Border
                     S2D_IMG_FORMAT_SRC,// Image format from loaded source image
                     GL_UNSIGNED_BYTE,  // Data type of source buffer
                     imgData            // The image source itself
        );
        
        // Done setting up texture. Don't mess up its state later
        glBindTexture(S2D_DEF_TEX_TARGET, 0);
        
        // Image source data no longer needed
        stbi_image_free(imgData);
        
        
        
        
        // --- ImageFrame Setup --- //
        
        
        /// Get the filename of the sprite sheet definition (YAML file)
        std::string ssFilename = filename;
        {
            const std::size_t ssExtStart = ssFilename.find_last_of(".");
            const std::string fileWithoutExt = ssFilename.substr(0, ssExtStart);
            ssFilename = fileWithoutExt + std::string(S2D_SPRITE_SHEET_DEF_EXT);
        }
        
        // Try to open the sprite sheet definition file
        const std::string ssFilePath = ResouceUtility::GetFullPathForFileName(ssFilename.c_str());
        FILE* yamlFileHandle = std::fopen(ssFilePath.c_str(), "r");
        
        // Process image frames of this texture if definition file exists
        if(yamlFileHandle != nullptr)
        {
            // Close the test file stream
            std::fclose(yamlFileHandle);
            
            // Open from YAML-CPP API
            YAML::Node yamlRoot = YAML::LoadFile(ssFilePath);
            const YAML::Node& spriteSheetRoot = yamlRoot[S2D_SPRITE_SHEET_YML_BASE_KEY];
            
            // Extract every ImageFrame from the YAML sequence
            const unsigned int NumberOfImageFrames = (unsigned int) spriteSheetRoot.size();
            for(unsigned int i = 0; i < NumberOfImageFrames; i++)
            {
                const YAML::Node& currentFrame = spriteSheetRoot[i];
                const unsigned int imageIndex = i+1;    // Needed because 0 is invalid in this engine
                
                // Extract data about current image frame
                const Rect imageRect = currentFrame["Rect"].as<Rect>();
                const StringFixed imageName = currentFrame["Name"].as<StringFixed>();
                
                // Make new image frame object to be managed by this texture
                ImageFrame* currentFrameObject = new ImageFrame(imageIndex,
                                                                imageRect,
                                                                imgWidth,
                                                                imgHeight,
                                                                this->id,
                                                                imageName
                );
                this->imageFrames.AddSorted(currentFrameObject, (int) imageIndex);
            }
        }
        else
        {
            // If no YAML file exists for this texture, just make the whole texture 1 image frame
            ImageFrame* soloImageFrame = new ImageFrame(1,
                                                        Rect(0.0f, 0.0f, (float) imgWidth, (float) imgHeight),
                                                        imgWidth,
                                                        imgHeight,
                                                        this->id,
                                                        this->name
            );
            this->imageFrames.AddFront(soloImageFrame, 1);
        }
    }
    
    // Dtor
    Texture::~Texture()
    {
        glBindTexture(S2D_DEF_TEX_TARGET, 0);
        glDeleteTextures(1, &this->textureHandle);
        
        while(this->imageFrames.GetNumberOfElements() != 0)
        {
            ImageFrame* oldResource = this->imageFrames.RemoveFront();
            delete oldResource;
        }
    }
    
    
    
    /// Make this texture the current texture when rendering in the draw loop
    void Texture::MakeActive()
    {
        glActiveTexture(GL_TEXTURE0 /* plus some offset to other units */);
        glBindTexture(S2D_DEF_TEX_TARGET, this->textureHandle);
    }
    
    
    /// Set the sampling of this texture. Affects all sprites of this texture
    void Texture::SetSampling(const Texture::Sampling newSampling)
    {
        this->MakeActive();
        
        /// GL_NEAREST or GL_LINEAR
        GLint filterType = 0;
        
        switch (newSampling)
        {
            case Texture::Sampling::Point:
            {
                filterType = GL_NEAREST;
                break;
            }
            case Texture::Sampling::Linear:
            {
                filterType = GL_LINEAR;
                break;
            }
        }
        
        glTexParameteri(S2D_DEF_TEX_TARGET, GL_TEXTURE_MIN_FILTER, filterType);
        glTexParameteri(S2D_DEF_TEX_TARGET, GL_TEXTURE_MAG_FILTER, filterType);
    }
    
    
    /// Get the read only name of this texture
    const StringFixed& Texture::GetName() const
    {
        return this->name;
    }
    
    /// Get the instance ID of this texture (unique for every texture) (not OpenGL handle!)
    const unsigned int Texture::GetId() const
    {
        return this->id;
    }
    
    
    /// Get the width of this texture
    const int Texture::GetWidth() const
    {
        return this->width;
    }
    
    /// Get the height of this texture
    const int Texture::GetHeight() const
    {
        return this->height;
    }
    
    
    /// Get an ImageFrame from this Texture given the frame's ID (1 or more)
    ImageFrame* const Texture::GetImageFrame(const unsigned int frameId) const
    {
        guarantee_that(frameId > 0, "FrameImage ID look up: 0 is invalid ID!");
        return this->imageFrames.FindById((int)frameId);
    }
    
    /// Get an ImageFrame from this Texture given the frame's name
    ImageFrame* const Texture::GetImageFrame(const StringFixed& frameName) const
    {
        ImageFrame* foundFrame = nullptr;
        
        for(auto itr = this->imageFrames.GetIterator(); itr.IsDone() == false; itr.Next())
        {
            ImageFrame* const currentFrame = itr.CurrentItem();
            
            if(frameName == currentFrame->GetName())
            {
                // Found it
                foundFrame = currentFrame;
                break;
            }
        }
        
        return foundFrame;
    }
    
}