//
//  SceneRegistry.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/5/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef SceneRegistry_hpp
#define SceneRegistry_hpp

#include "Scene.hpp"
#include "engine/DataTypes/LinkedList.hpp"
#include "engine/AppSys/IRegistry.hpp"

namespace sea2d
{
    // Forward declare EntityRegistry
    class EntityRegistry;
    
    
    /// Serves as a container for holding all loaded Camera s in the app
    class SceneRegistry final : public IRegistry
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        SceneRegistry();
        
        /// Destructor
        virtual ~SceneRegistry();
        
        
        //
        // Methods
        //
        
        /// Decide what resources to load at the start of the App
        virtual void Load() override;
        
        /// Release any resources remaining that are managed by this registry
        virtual void Unload() override;
        
        /// Check of a new scene was requested to load and then load that scene
        void LoadNewSceneIfRequested(EntityRegistry* const entityRegistry);
        
        
        
        //
        // Static Methods
        //
        
        /// Find any resource by name
        static Scene* const Find(const char* const name);
        
        /// Find any resource by ID
        static Scene* const Find(const unsigned int id);
        
        /// Receive a new request to load a scene (will replacing exisitng request)
        static void RecieveNewLoadingRequest(const Scene::LoadRequest& newRequest);
        
        
        
    private:
        
        //
        // Data
        //
        
        LinkedList<Scene> resourceList;         ///< List of managed resources
        Scene::LoadRequest currentLoadRequest;  ///< Determines which scene to load
        
        static SceneRegistry* s_instance;       ///< Singeton instance of this registry
        
        
        
        //
        // Private Routines
        //
        
        /// Resource must be dynaically allocated, but it will be deleted by this registry later
        void Add(Scene* const newResource);
        
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Copy Ctor
        SceneRegistry(const SceneRegistry& other) = delete;
        
        /// No Copy Assignment
        SceneRegistry& operator=(const SceneRegistry& rhs) = delete;
        
        /// No Move Ctor
        SceneRegistry(SceneRegistry&& other) = delete;
        
        /// No Move Assignment
        SceneRegistry& operator=(SceneRegistry&& rhs) = delete;
    };
}
#endif /* SceneRegistry_hpp */
