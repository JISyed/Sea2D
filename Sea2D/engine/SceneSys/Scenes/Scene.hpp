//
//  Scene.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/1/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef Scene_hpp
#define Scene_hpp

#include "engine/DataTypes/StringFixed.hpp"

namespace sea2d
{
    /// Base class of any setup of Entities belonging to a "scene" organization. Must be inherited
    class Scene
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        Scene(const char* const newName);
        
        /// Destructor
        virtual ~Scene();
        
        /// Scene Registry can access Scene
        friend class SceneRegistry;
        
        
        //
        // Methods
        //
        
        /// Get the unique ID of this scene
        const unsigned int GetId() const;
        
        /// Get the name of this scene
        const StringFixed& GetName() const;
        
        /// Load the entities of this scene (will unload existing entities)
        void Load();
        
        /// Load the entties of this scene on top of already existing entities
        void LoadAdditive();
        
        
    protected:
        
        /// This is where you determine what Entites you want to load for this scene
        virtual void OnLoad() = 0;
        
        
    private:
        
        //
        // Data
        //
        
        unsigned int id;    ///< The unique ID for this scene
        StringFixed name;   ///< The name of this scene
        
        
        
        //
        // Private Data Type (SceneRegisty can access)
        //
        
        /// Defines the different ways of loading a scene
        enum class LoadingType : int
        {
            DoNotLoad,  ///< Don't load a new scene at all (used to clear request)
            Solo,       ///< Clears the entity hierarchy before loading
            Additive,   ///< Loads new entities ontop of existing entity hierarchy
        };
        
        /// Request packet for loading new scene
        struct LoadRequest
        {
            Scene* sceneToLoad;         ///< The scene that was requested for loading
            LoadingType requestType;    ///< The type of loading that was requested
            
            LoadRequest() :
                sceneToLoad(nullptr),
                requestType(LoadingType::DoNotLoad)
            {
            }
            
            LoadRequest& operator=(const LoadRequest& other)
            {
                this->sceneToLoad = other.sceneToLoad;
                this->requestType = other.requestType;
                return *this;
            }
        };
        
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Default Ctor
        Scene() = delete;
        
        /// No Copy Ctor
        Scene(const Scene& other) = delete;
        
        /// No Copy Assignment
        Scene& operator=(const Scene& rhs) = delete;
        
        /// No Move Ctor
        Scene(Scene&& other) = delete;
        
        /// No Move Assignment
        Scene& operator=(Scene&& rhs) = delete;
    };
}
#endif /* Scene_hpp */
