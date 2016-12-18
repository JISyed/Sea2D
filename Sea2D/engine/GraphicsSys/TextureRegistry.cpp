//
//  TextureRegistry.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/25/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "TextureRegistry.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include "engine/AppSys/ResourceUtility.hpp"

namespace sea2d
{
    //
    // Static Data
    //
    
    TextureRegistry* TextureRegistry::s_instance = nullptr;
    
    
    
    //
    // Methods
    //
    
    // Default Ctor
    TextureRegistry::TextureRegistry() :
    resourceList()
    {
        guarantee_that(TextureRegistry::s_instance == nullptr, "TextureRegistry singleton already exists!");
        TextureRegistry::s_instance = this;
    }
    
    // VIRTUAL
    // Dtor
    TextureRegistry::~TextureRegistry()
    {
        guarantee_that(this->resourceList.GetNumberOfElements() == 0, "TextureRegistry list must be empty before destruction");
        guarantee_that(TextureRegistry::s_instance != nullptr, "TextureRegistry singeton instance must exist before destruction!");
        TextureRegistry::s_instance = nullptr;
    }
    
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Decide what resources to load at the start of the App
    void TextureRegistry::Load()
    {
        TextureRegistry::Create("sea_icon.png", "AppIcon", Texture::Sampling::Point);
        TextureRegistry::Create("p1_spritesheet.png", "GreenAlien", Texture::Sampling::Point);
        TextureRegistry::Create("enemies_spritesheet.png", "Enemies", Texture::Sampling::Point);
        TextureRegistry::Create("hud_spritesheet.png", "KenneyHud", Texture::Sampling::Point);
        TextureRegistry::Create("tiles_spritesheet.png", "KenneyPlatfomer", Texture::Sampling::Point);
        TextureRegistry::Create("firstBitmapFont.png", "FirstBitmapFont", Texture::Sampling::Point);
    }
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Release any resources remaining that are managed by this registry
    void TextureRegistry::Unload()
    {
        while(this->resourceList.GetNumberOfElements() != 0)
        {
            Texture* oldResource = this->resourceList.RemoveFront();
            delete oldResource;
        }
    }
    
    
    
    
    
    
    // STATIC
    /// Find any resource by name
    Texture* const TextureRegistry::Find(const char* const name)
    {
        Texture* currentResource = nullptr;
        auto itr = TextureRegistry::s_instance->resourceList.GetIterator();
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
    Texture* const TextureRegistry::Find(const unsigned int id)
    {
        return TextureRegistry::s_instance->resourceList.FindById((int) id);
    }
    
    
    // STATIC
    /// Creates a resource with given parameters, adds to this registry, and returns the created resource
    Texture* const TextureRegistry::Create(const char* const filename, const char* const textureName, const Texture::Sampling textureSampling)
    {
        guarantee_that(TextureRegistry::s_instance != nullptr, "Registry singeton cannot create new resource because the registry doesn't exist!");
        
        Texture* newResource = new Texture(filename, textureName, textureSampling);
        
        TextureRegistry::Add(newResource);
        
        return newResource;
    }
    
    
    
    // STATIC
    /// Resource must be dynaically allocated, but it will be deleted by this registry later
    void TextureRegistry::Add(Texture* newResource)
    {
        guarantee_that(newResource != nullptr, "Registry adding a null resource!");
        TextureRegistry::s_instance->resourceList.AddFront(newResource, (int)newResource->GetId());
    }
}
