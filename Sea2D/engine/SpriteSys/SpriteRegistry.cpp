//
//  SpriteRegistry.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "SpriteRegistry.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include "engine/AppSys/ResourceUtility.hpp"
#include <yaml-cpp/yaml.h>
#include "engine/YamlConverters/YamlStringFixedConverter.hpp"
#include <cstdio>
#include "engine/GraphicsSys/TextureRegistry.hpp"
#include <string>
#include "engine/TimeSys/TimeValue.hpp"


//
// Sprite YAML Options
//

#define S2D_SPRITE_COLLECTION_YML_BASE_KEY  "Sprites"
#define S2D_SPRITE_TEXTURE_YAML_KEY         "TextureName"




namespace sea2d
{
    //
    // Static Data
    //
    
    SpriteRegistry* SpriteRegistry::s_instance = nullptr;
    
    
    
    //
    // Methods
    //
    
    // Default Ctor
    SpriteRegistry::SpriteRegistry() :
        resourceList()
    {
        guarantee_that(SpriteRegistry::s_instance == nullptr, "SpriteRegistry singleton already exists!");
        SpriteRegistry::s_instance = this;
    }
    
    // VIRTUAL
    // Dtor
    SpriteRegistry::~SpriteRegistry()
    {
        guarantee_that(this->resourceList.GetNumberOfElements() == 0, "SpriteRegistry list must be empty before destruction");
        guarantee_that(SpriteRegistry::s_instance != nullptr, "SpriteRegistry singeton instance must exist before destruction!");
        SpriteRegistry::s_instance = nullptr;
    }
    
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Decide what resources to load at the start of the App
    void SpriteRegistry::Load()
    {
        SpriteRegistry::Create("spr_green_alien.yml");
        SpriteRegistry::Create(TextureRegistry::Find("AppIcon"));
        SpriteRegistry::Create("spr_enemies.yml");
        SpriteRegistry::Create("spr_hud_elements.yml");
        SpriteRegistry::Create("spr_level_items.yml");
        SpriteRegistry::Create("spr_level_tiles.yml");
    }
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Release any resources remaining that are managed by this registry
    void SpriteRegistry::Unload()
    {
        while(this->resourceList.GetNumberOfElements() != 0)
        {
            Sprite* oldResource = this->resourceList.RemoveFront();
            delete oldResource;
        }
    }
    
    
    
    
    
    
    // STATIC
    /// Find any resource by name
    Sprite* const SpriteRegistry::Find(const char* const name)
    {
        Sprite* currentResource = nullptr;
        auto itr = SpriteRegistry::s_instance->resourceList.GetIterator();
        while (itr.IsDone() == false)
        {
            currentResource = itr.CurrentItem();
            
            if(currentResource->GetName() == name)
            {
                break;
            }
            
            itr.Next();
        }
        
        return currentResource;
    }
    
    // STATIC
    /// Find any resource by ID
    Sprite* const SpriteRegistry::Find(const unsigned int id)
    {
        return SpriteRegistry::s_instance->resourceList.FindById((int) id);
    }
    
    
    // STATIC
    /// Creates a resource with given parameters, adds to this registry, and returns the created resource
    void SpriteRegistry::Create(const char* const spriteCollectionFilename)
    {
        guarantee_that(SpriteRegistry::s_instance != nullptr, "Registry singeton cannot create new resource because the registry doesn't exist!");
        
        Sprite* newSprite = nullptr;
        
        // Try to open the YAML file containing the sprite definitions
        const std::string filePath = ResouceUtility::GetFullPathForFileName(spriteCollectionFilename);
        FILE* yamlFileHandle = std::fopen(filePath.c_str(), "r");
        guarantee_that(yamlFileHandle != nullptr, "Sprite could not find YAML definition file!");
        
        if(yamlFileHandle != nullptr)
        {
            // Close the test file stream
            std::fclose(yamlFileHandle);
            
            
            // Open the sprite definition as a YAML file
            YAML::Node yamlRoot = YAML::LoadFile(filePath);
            const YAML::Node& spriteCollection = yamlRoot[S2D_SPRITE_COLLECTION_YML_BASE_KEY];
            
            // Get the texture for this sprite
            const YAML::Node& textureNameNode = yamlRoot[S2D_SPRITE_TEXTURE_YAML_KEY];
            std::string textureName = textureNameNode.as<std::string>();
            Texture* const spritesTexture = TextureRegistry::Find(textureName.c_str());
            guarantee_that(spritesTexture != nullptr, "Could not find the texture associated to a sprite!");
            
            // Create a new sprite for every sprite listed in this YAML file
            const unsigned int NumOfSpritesToExtract = (unsigned int) spriteCollection.size();
            for(unsigned int i = 0; i < NumOfSpritesToExtract; i++)
            {
                // Get the current sprite node
                const YAML::Node& currSprite = spriteCollection[i]["Sprite"];
                
                // Name
                const StringFixed spriteName = currSprite["Name"].as<StringFixed>();
                
                // Number of frames
                const unsigned int numOfFrames = (unsigned int) currSprite["ImageFrames"].size();
                guarantee_that(numOfFrames > 0, "Sprite YAML has a sprite that has no frames indices defined!");
                
                // The frames themselves
                ImageFrame** spriteFrames = new ImageFrame*[numOfFrames];
                for(unsigned int f = 0; f < numOfFrames; f++)
                {
                    const unsigned int currFrameIdx = (unsigned int) currSprite["ImageFrames"][f].as<int>();
                    
                    ImageFrame* currFrame = spritesTexture->GetImageFrame(currFrameIdx);
                    guarantee_that(currFrame != nullptr, "Sprite could nor find an ImageFrame index in the texture!");
                    
                    spriteFrames[f] = currFrame;
                }
                
                // Animaiton data, if any
                SpriteAnimationData* animation = nullptr;
                if(numOfFrames > 1)
                {
                    const bool willLoop = currSprite["Loops"].as<bool>();
                    const int frameTimeMs = currSprite["FrameTimeInMs"].as<int>();
                    const TimeValue frameTime = frameTimeMs * TimeValue(TimeBasis::OneMillisecond);
                    
                    animation = new SpriteAnimationData(frameTime, numOfFrames, willLoop);
                }
                
                
                newSprite = new Sprite(spriteName, numOfFrames, spriteFrames, animation, spritesTexture);
                
                SpriteRegistry::Add(newSprite);
            }
        }
    }
    
    
    // STATIC
    /// Creates a resource with given parameters, adds to this registry, and returns the created resource
    void SpriteRegistry::Create(Texture* const textureForOneSprite)
    {
        guarantee_that(textureForOneSprite != nullptr, "Making 1 sprite from a whole texture, but the texture is null!");
        
        // Get the only image frame in this texture
        ImageFrame* currFrame = textureForOneSprite->GetImageFrame(1);
        ImageFrame** const oneElementArray = new ImageFrame*[1];
        oneElementArray[0] = currFrame;
        
        // Make new sprite from whole texture (not animated)
        Sprite* const newSprite = new Sprite(currFrame->GetName(), 1, oneElementArray, nullptr, textureForOneSprite);
        
        SpriteRegistry::Add(newSprite);
    }
    
    
    // STATIC
    /// Resource must be dynaically allocated, but it will be deleted by this registry later
    void SpriteRegistry::Add(Sprite* newResource)
    {
        guarantee_that(newResource != nullptr, "Registry adding a null resource!");
        SpriteRegistry::s_instance->resourceList.AddFront(newResource, (int)newResource->GetId());
    }
}
