//
//  Scene.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/1/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Scene.hpp"
#include "engine/AppSys/IdGenerator.hpp"
#include "SceneRegistry.hpp"

namespace sea2d
{
    //
    // Statics
    //
    
    /// Generates IDs for every Entity when the game runs
    static IdGenerator s_idGen;
    
    
    
    
    //
    // Methods
    //
    
    
    // Default Ctor
    Scene::Scene(const char* const newName) :
        id(s_idGen.MakeNewId()),
        name(newName)
    {
    }
    
    // VIRTUAL
    // Dtor
    Scene::~Scene()
    {
    }
    
    
    /// Get the unique ID of this scene
    const unsigned int Scene::GetId() const
    {
        return this->id;
    }
    
    /// Get the name of this scene
    const StringFixed& Scene::GetName() const
    {
        return this->name;
    }
    
    
    /// Load the entities of this scene (will unload existing entities)
    void Scene::Load()
    {
        // Make new scene loading request
        Scene::LoadRequest newRequest;
        newRequest.sceneToLoad = this;
        newRequest.requestType = Scene::LoadingType::Solo;
        
        // Send request to SceneRegistry
        SceneRegistry::RecieveNewLoadingRequest(newRequest);
    }
    
    /// Load the entties of this scene on top of already existing entities
    void Scene::LoadAdditive()
    {
        // Make new scene loading request
        Scene::LoadRequest newRequest;
        newRequest.sceneToLoad = this;
        newRequest.requestType = Scene::LoadingType::Additive;
        
        // Send request to SceneRegistry
        SceneRegistry::RecieveNewLoadingRequest(newRequest);
    }
    
    
}
