//
//  SceneRegistry.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/5/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "SceneRegistry.hpp"
#include "engine/SceneSys/Entities/EntityRegistry.hpp"
#include "EveryCustomScene.hpp"

namespace sea2d
{
    //
    // Static Data
    //
    
    SceneRegistry* SceneRegistry::s_instance = nullptr;
    
    
    
    //
    // Methods
    //
    
    // Default Ctor
    SceneRegistry::SceneRegistry() :
    resourceList()
    {
        guarantee_that(SceneRegistry::s_instance == nullptr, "SceneRegistry singleton already exists!");
        SceneRegistry::s_instance = this;
    }
    
    // VIRTUAL
    // Dtor
    SceneRegistry::~SceneRegistry()
    {
        guarantee_that(this->resourceList.GetNumberOfElements() == 0, "SceneRegistry list must be empty before destruction");
        guarantee_that(SceneRegistry::s_instance != nullptr, "SceneRegistry singeton instance must exist before destruction!");
        SceneRegistry::s_instance = nullptr;
    }
    
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Decide what resources to load at the start of the App
    void SceneRegistry::Load()
    {
        this->Add(new SpriteDemoScene());
        
        this->Add(new FirstScene());
        
    }
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Release any resources remaining that are managed by this registry
    void SceneRegistry::Unload()
    {
        while(this->resourceList.GetNumberOfElements() != 0)
        {
            Scene* oldResource = this->resourceList.RemoveFront();
            delete oldResource;
        }
    }
    
    
    /// Check of a new scene was requested to load and then load that scene
    void SceneRegistry::LoadNewSceneIfRequested(EntityRegistry* const entityRegistry)
    {
        // Only load a new scene if there was a request to do so
        if(this->currentLoadRequest.requestType != Scene::LoadingType::DoNotLoad)
        {
            guarantee_that(this->currentLoadRequest.sceneToLoad != nullptr, "New Scene Loading request cannot process a null scene!");
            
            // Unload existing entities if requested to load solo (not additive)
            if(this->currentLoadRequest.requestType == Scene::LoadingType::Solo)
            {
                entityRegistry->Unload();
            }
            
            // Load the scene's entities
            this->currentLoadRequest.sceneToLoad->OnLoad();
            
            // Clear the request, otherwise this will always reload the same scene!
            this->currentLoadRequest.sceneToLoad = nullptr;
            this->currentLoadRequest.requestType = Scene::LoadingType::DoNotLoad;
        }
    }
    
    
    
    
    // STATIC
    /// Find any resource by name
    Scene* const SceneRegistry::Find(const char* const name)
    {
        Scene* currentResource = nullptr;
        auto itr = SceneRegistry::s_instance->resourceList.GetIterator();
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
    Scene* const SceneRegistry::Find(const unsigned int id)
    {
        return SceneRegistry::s_instance->resourceList.FindById((int) id);
    }
    
    
    // STATIC
    /// Receive a new request to load a scene (will replacing exisitng request)
    void SceneRegistry::RecieveNewLoadingRequest(const Scene::LoadRequest& newRequest)
    {
        s_instance->currentLoadRequest = newRequest;
        guarantee_that(newRequest.sceneToLoad != nullptr, "SceneRegistry recieved a new load request, but the requested scene is null!");
    }
    
    
    
    
    /// Resource must be dynaically allocated, but it will be deleted by this registry later
    void SceneRegistry::Add(Scene* const newResource)
    {
        guarantee_that(newResource != nullptr, "Registry adding a null resource!");
        this->resourceList.AddSorted(newResource, (int)newResource->GetId());
    }
}
