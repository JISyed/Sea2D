//
//  EntityRegistry.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/1/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef EntityRegistry_hpp
#define EntityRegistry_hpp

#include "Entity.hpp"
#include "engine/AppSys/IRegistry.hpp"
#include "engine/DataTypes/PCS/PCSTree.hpp"

namespace sea2d
{
    /// Serves as a container for holding all loaded Entities in the app
    class EntityRegistry final : public IRegistry
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        EntityRegistry();
        
        /// Destructor
        virtual ~EntityRegistry();
        
        
        //
        // Methods
        //
        
        /// Decide what resources to load at the start of the App
        virtual void Load() override;
        
        /// Release any resources remaining that are managed by this registry
        virtual void Unload() override;
        
        /// Update every Entity that currently exists
        void Update();
        
        
        
        //
        // Static Methods
        //
        
        /// Find any resource by name
        static Entity* const Find(const char* const name);
        
        /// Find any resource by ID
        static Entity* const Find(const unsigned int id);
        
        
        /// Creates a resource with given parameters, adds to this registry, and returns the created resource. Also define a parent entity for this entity
        static Entity* const Create(Entity* const parentEntity, const char* const newName);
        
        /// Creates a resource with given parameters, adds to this registry, and returns the created resource. Parent of this entity will be the "root" entity
        static Entity* const Create(const char* const newName);
        
        
        
    private:
        
        //
        // Data
        //
        
        lge::PCSTree entityHierarchy;           ///< Current hierarchy of Entities
        Entity* rootEntity;                     ///< The root of the entity hierarchy
        
        static EntityRegistry* s_instance;      ///< Singeton instance of this registry
        
        
        //
        // Private Routines
        //
        
        /// Entity must be dynaically allocated, but it will be deleted by this registry later
        static void Add(Entity* const newEntity, Entity* const parentEntity);
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Copy Ctor
        EntityRegistry(const EntityRegistry& other) = delete;
        
        /// No Copy Assignment
        EntityRegistry& operator=(const EntityRegistry& rhs) = delete;
        
        /// No Move Ctor
        EntityRegistry(EntityRegistry&& other) = delete;
        
        /// No Move Assignment
        EntityRegistry& operator=(EntityRegistry&& rhs) = delete;
    };
}
#endif /* EntityRegistry_hpp */
