//
//  MeshRegistry.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/24/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "MeshRegistry.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include "engine/AppSys/ResourceUtility.hpp"


namespace sea2d
{
    //
    // Static Data
    //
    
    MeshRegistry* MeshRegistry::s_instance = nullptr;
    
    
    
    //
    // Methods
    //
    
    // Default Ctor
    MeshRegistry::MeshRegistry() :
        resourceList()
    {
        guarantee_that(MeshRegistry::s_instance == nullptr, "MeshRegistry singleton already exists!");
        MeshRegistry::s_instance = this;
    }
    
    // VIRTUAL
    // Dtor
    MeshRegistry::~MeshRegistry()
    {
        guarantee_that(this->resourceList.GetNumberOfElements() == 0, "MeshRegistry list must be empty before destruction");
        guarantee_that(MeshRegistry::s_instance != nullptr, "MeshRegistry singeton instance must exist before destruction!");
        MeshRegistry::s_instance = nullptr;
    }
    
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Decide what resources to load at the start of the App
    void MeshRegistry::Load()
    {
        // Get the quad mesh data from the App System
        const GLfloat* vertData = nullptr;
        size_t vertDataElements = 0;
        const GLuint* triData = nullptr;
        size_t triDataElements = 0;
        ResouceUtility::GetQuadMesh(vertData, vertDataElements, triData, triDataElements);
        
        // Load into registry
        MeshRegistry::Create(vertData, vertDataElements, triData, triDataElements, "Quad");
    }
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Release any resources remaining that are managed by this registry
    void MeshRegistry::Unload()
    {
        while(this->resourceList.GetNumberOfElements() != 0)
        {
            Mesh* oldResource = this->resourceList.RemoveFront();
            delete oldResource;
        }
    }
    
    
    
    
    
    
    // STATIC
    /// Find any resource by name
    Mesh* const MeshRegistry::Find(const char* const name)
    {
        Mesh* currentResource = nullptr;
        auto itr = MeshRegistry::s_instance->resourceList.GetIterator();
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
    Mesh* const MeshRegistry::Find(const unsigned int id)
    {
        return MeshRegistry::s_instance->resourceList.FindById((int) id);
    }
    
    
    // STATIC
    /// Creates a resource with given parameters, adds to this registry, and returns the created resource
    Mesh* const MeshRegistry::Create(const GLfloat* const vertexData, const size_t elementsInVertexData, const GLuint* const triangeData, const size_t elementsInTriangleData, const char* const newName)
    {
        guarantee_that(MeshRegistry::s_instance != nullptr, "Registry singeton cannot create new resource because the registry doesn't exist!");
        
        Mesh* newResource = new Mesh(vertexData, elementsInVertexData, triangeData, elementsInTriangleData, newName);
        
        MeshRegistry::Add(newResource);
        
        return newResource;
    }
    
    
    
    // STATIC
    /// Resource must be dynaically allocated, but it will be deleted by this registry later
    void MeshRegistry::Add(Mesh* newResource)
    {
        guarantee_that(newResource != nullptr, "Registry adding a null resource!");
        MeshRegistry::s_instance->resourceList.AddFront(newResource, (int)newResource->GetId());
    }
    
}