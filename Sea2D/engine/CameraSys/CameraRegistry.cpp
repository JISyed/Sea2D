//
//  CameraRegistry.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/25/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "CameraRegistry.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include "engine/AppSys/ResourceUtility.hpp"
#include "engine/AppSys/App.hpp"


// Sea2D Camera Options

#define S2D_DEFAULT_NEAR_CLIP   (1.0f)
#define S2D_DEFAULT_FAR_CLIP    (300.0f)


namespace sea2d
{
    //
    // Static Data
    //
    
    CameraRegistry* CameraRegistry::s_instance = nullptr;
    
    
    
    //
    // Methods
    //
    
    // Default Ctor
    CameraRegistry::CameraRegistry() :
    resourceList()
    {
        guarantee_that(CameraRegistry::s_instance == nullptr, "CameraRegistry singleton already exists!");
        CameraRegistry::s_instance = this;
    }
    
    // VIRTUAL
    // Dtor
    CameraRegistry::~CameraRegistry()
    {
        guarantee_that(this->resourceList.GetNumberOfElements() == 0, "CameraRegistry list must be empty before destruction");
        guarantee_that(CameraRegistry::s_instance != nullptr, "CameraRegistry singeton instance must exist before destruction!");
        CameraRegistry::s_instance = nullptr;
    }
    
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Decide what resources to load at the start of the App
    void CameraRegistry::Load()
    {
        // Intentionally empty. Add CameraBehaviors to Entities instead.
    }
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Release any resources remaining that are managed by this registry
    void CameraRegistry::Unload()
    {
        while(this->resourceList.GetNumberOfElements() != 0)
        {
            Camera* oldResource = this->resourceList.RemoveFront();
            delete oldResource;
        }
    }
    
    
    /// Get the iterator for the camera list
    const LinkedList<Camera>::Iterator CameraRegistry::GetIterator() const
    {
        return this->resourceList.GetIterator();
    }
    
    
    
    
    
    // STATIC
    /// Find any resource by name
    Camera* const CameraRegistry::Find(const char* const name)
    {
        Camera* currentResource = nullptr;
        auto itr = CameraRegistry::s_instance->resourceList.GetIterator();
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
    Camera* const CameraRegistry::Find(const unsigned int id)
    {
        return CameraRegistry::s_instance->resourceList.FindById((int) id);
    }
    
    
    // STATIC
    /// Creates a camera with given parameters, adds to this registry, and returns the created resource
    Camera* const CameraRegistry::Create(const bool willBeActive, const Vector2& newPosition, const float newRotation)
    {
        guarantee_that(CameraRegistry::s_instance != nullptr, "Registry singeton cannot create new resource because the registry doesn't exist!");
        
        Camera* newResource = new Camera(willBeActive);
        newResource->SetPosition(newPosition);
        newResource->SetRotation(newRotation);
        newResource->SetNearClip(S2D_DEFAULT_NEAR_CLIP);
        newResource->SetFarClip(S2D_DEFAULT_FAR_CLIP);
        newResource->SetProjection(App::GetWindowWidth(), App::GetWindowHeight());
        newResource->SetViewport(0, 0, (int) App::GetWindowWidth(), (int) App::GetWindowHeight());
        
        CameraRegistry::Add(newResource);
        
        return newResource;
    }
    
    
    // STATIC
    /// Creates a camera with given parameters, adds to this registry, and returns the created resource
    Camera* const CameraRegistry::Create(const bool willBeActive, const Vector2& newPosition, const float newRotation, const float newWidth, const float newHeight)
    {
        guarantee_that(CameraRegistry::s_instance != nullptr, "Registry singeton cannot create new resource because the registry doesn't exist!");
        
        Camera* newResource = new Camera(willBeActive);
        newResource->SetPosition(newPosition);
        newResource->SetRotation(newRotation);
        newResource->SetNearClip(S2D_DEFAULT_NEAR_CLIP);
        newResource->SetFarClip(S2D_DEFAULT_FAR_CLIP);
        newResource->SetProjection(newWidth, newHeight);
        newResource->SetViewport(0, 0, (int) App::GetWindowWidth(), (int) App::GetWindowHeight());
        
        CameraRegistry::Add(newResource);
        
        return newResource;
    }
    
    
    // STATIC
    /// Creates a camera with given parameters, adds to this registry, and returns the created resource
    Camera* const CameraRegistry::Create(const bool willBeActive, const Vector2& newPosition, const float newRotation, const float newWidth, const float newHeight, const int newViewportX, const int newViewportY, const int newViewportWidth, const int newViewportHeight)
    {
        guarantee_that(CameraRegistry::s_instance != nullptr, "Registry singeton cannot create new resource because the registry doesn't exist!");
        
        Camera* newResource = new Camera(willBeActive);
        newResource->SetPosition(newPosition);
        newResource->SetRotation(newRotation);
        newResource->SetNearClip(S2D_DEFAULT_NEAR_CLIP);
        newResource->SetFarClip(S2D_DEFAULT_FAR_CLIP);
        newResource->SetProjection(newWidth, newHeight);
        newResource->SetViewport(newViewportX, newViewportY, newViewportWidth, newViewportHeight);
        
        CameraRegistry::Add(newResource);
        
        return newResource;
    }
    
    
    // STATIC
    /// Delete a camera from the registry given a valid camera. Will invalidate pointer
    const bool CameraRegistry::Remove(Camera*& toBeRemoved)
    {
        bool removed = CameraRegistry::s_instance->resourceList.RemoveByObject(toBeRemoved);
        
        if(removed)
        {
            delete toBeRemoved;
            toBeRemoved = nullptr;
        }
        
        return removed;
    }
    
    
    // STATIC
    /// Resource must be dynaically allocated, but it will be deleted by this registry later
    void CameraRegistry::Add(Camera* newResource)
    {
        guarantee_that(newResource != nullptr, "Registry adding a null resource!");
        CameraRegistry::s_instance->resourceList.AddSorted(newResource, (int)newResource->GetId());
    }
    
}