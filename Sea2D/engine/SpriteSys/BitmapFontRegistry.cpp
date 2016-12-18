//
//  BitmapFontRegistry.cpp
//  Sea2D
//
//  Created by Jibran Syed on 6/8/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "BitmapFontRegistry.hpp"

namespace sea2d
{
    //
    // Static Data
    //
    
    BitmapFontRegistry* BitmapFontRegistry::s_instance = nullptr;
    
    
    
    //
    // Methods
    //
    
    // Default Ctor
    BitmapFontRegistry::BitmapFontRegistry() :
    resourceList()
    {
        guarantee_that(BitmapFontRegistry::s_instance == nullptr, "BitmapFontRegistry singleton already exists!");
        BitmapFontRegistry::s_instance = this;
    }
    
    // VIRTUAL
    // Dtor
    BitmapFontRegistry::~BitmapFontRegistry()
    {
        guarantee_that(this->resourceList.GetNumberOfElements() == 0, "BitmapFontRegistry list must be empty before destruction");
        guarantee_that(BitmapFontRegistry::s_instance != nullptr, "BitmapFontRegistry singeton instance must exist before destruction!");
        BitmapFontRegistry::s_instance = nullptr;
    }
    
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Decide what resources to load at the start of the App
    void BitmapFontRegistry::Load()
    {
        BitmapFontRegistry::Create("firstBitmapFont_fontdef.yml");
    }
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Release any resources remaining that are managed by this registry
    void BitmapFontRegistry::Unload()
    {
        while(this->resourceList.GetNumberOfElements() != 0)
        {
            BitmapFont* oldResource = this->resourceList.RemoveFront();
            delete oldResource;
        }
    }
    
    
    
    
    
    
    // STATIC
    /// Find any resource by name
    BitmapFont* const BitmapFontRegistry::Find(const char* const name)
    {
        BitmapFont* currentResource = nullptr;
        auto itr = BitmapFontRegistry::s_instance->resourceList.GetIterator();
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
    BitmapFont* const BitmapFontRegistry::Find(const unsigned int id)
    {
        return BitmapFontRegistry::s_instance->resourceList.FindById((int) id);
    }
    
    
    // STATIC
    /// Creates a resource with given parameters, adds to this registry, and returns the created resource
    void BitmapFontRegistry::Create(const char* const fontDefinitionFilename)
    {
        BitmapFont* newFont = new BitmapFont(fontDefinitionFilename);
        BitmapFontRegistry::Add(newFont);
    }
    
    
    // STATIC
    /// Resource must be dynaically allocated, but it will be deleted by this registry later
    void BitmapFontRegistry::Add(BitmapFont* newResource)
    {
        guarantee_that(newResource != nullptr, "Registry adding a null resource!");
        BitmapFontRegistry::s_instance->resourceList.AddFront(newResource, (int)newResource->GetId());
    }
}