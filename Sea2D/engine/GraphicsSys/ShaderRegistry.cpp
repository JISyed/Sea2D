//
//  ShaderRegistry.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/25/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "ShaderRegistry.hpp"

#include "engine/AppSys/DebugGuarantee.hpp"
#include "engine/AppSys/ResourceUtility.hpp"

namespace sea2d
{
    //
    // Static Data
    //
    
    ShaderRegistry* ShaderRegistry::s_instance = nullptr;
    
    
    
    //
    // Methods
    //
    
    // Default Ctor
    ShaderRegistry::ShaderRegistry() :
    resourceList()
    {
        guarantee_that(ShaderRegistry::s_instance == nullptr, "ShaderRegistry singleton already exists!");
        ShaderRegistry::s_instance = this;
    }
    
    // VIRTUAL
    // Dtor
    ShaderRegistry::~ShaderRegistry()
    {
        guarantee_that(this->resourceList.GetNumberOfElements() == 0, "ShaderRegistry list must be empty before destruction");
        guarantee_that(ShaderRegistry::s_instance != nullptr, "ShaderRegistry singeton instance must exist before destruction!");
        ShaderRegistry::s_instance = nullptr;
    }
    
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Decide what resources to load at the start of the App
    void ShaderRegistry::Load()
    {
        ShaderRegistry::Create("sprite", "Sprite");
        ShaderRegistry::Create("standard", "Standard");
        ShaderRegistry::Create("bitmap_font", "BitmapFont");
    }
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Release any resources remaining that are managed by this registry
    void ShaderRegistry::Unload()
    {
        while(this->resourceList.GetNumberOfElements() != 0)
        {
            Shader* oldResource = this->resourceList.RemoveFront();
            delete oldResource;
        }
    }
    
    
    
    
    
    
    // STATIC
    /// Find any resource by name
    Shader* const ShaderRegistry::Find(const char* const name)
    {
        Shader* currentResource = nullptr;
        auto itr = ShaderRegistry::s_instance->resourceList.GetIterator();
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
    Shader* const ShaderRegistry::Find(const unsigned int id)
    {
        return ShaderRegistry::s_instance->resourceList.FindById((int) id);
    }
    
    
    // STATIC
    /// Creates a resource with given parameters, adds to this registry, and returns the created resource
    Shader* const ShaderRegistry::Create(const char* const fileName, const char* const shaderName)
    {
        guarantee_that(ShaderRegistry::s_instance != nullptr, "Registry singeton cannot create new resource because the registry doesn't exist!");
        
        Shader* newResource = new Shader(fileName, shaderName);
        
        ShaderRegistry::Add(newResource);
        
        return newResource;
    }
    
    // STATIC
    /// Get the iterator for the shader list
    const LinkedList<Shader>::Iterator ShaderRegistry::GetIterator()
    {
        return ShaderRegistry::s_instance->resourceList.GetIterator();
    }
    
    
    // STATIC
    /// Resource must be dynaically allocated, but it will be deleted by this registry later
    void ShaderRegistry::Add(Shader* newResource)
    {
        guarantee_that(newResource != nullptr, "Registry adding a null resource!");
        ShaderRegistry::s_instance->resourceList.AddFront(newResource, (int)newResource->GetId());
    }
    
}