//
//  EntityRegistry.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/1/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "EntityRegistry.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include "engine/DataTypes/PCS/PCSForwardIterator.hpp"

namespace sea2d
{
    //
    // Static Data
    //
    
    EntityRegistry* EntityRegistry::s_instance = nullptr;
    
    
    
    
    //
    // Methods
    //
    
    /// Default Ctor
    EntityRegistry::EntityRegistry() :
        entityHierarchy(),
        rootEntity(nullptr)
    {
        guarantee_that(EntityRegistry::s_instance == nullptr, "EntityRegistry singleton already exists!");
        EntityRegistry::s_instance = this;
        
        // Create the root entity and send it to the hierarchy
        this->rootEntity = new Entity("ROOT");
        this->entityHierarchy.insert(this->rootEntity, nullptr);
    }
    
    // VIRTUAL
    /// Destructor
    EntityRegistry::~EntityRegistry()
    {
        guarantee_that(EntityRegistry::s_instance != nullptr, "EntityRegistry singeton instance must exist before destruction!");
        EntityRegistry::s_instance = nullptr;
        
        this->entityHierarchy.remove(this->rootEntity); // This deletes the root
        this->rootEntity = nullptr;
    }
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Decide what resources to load at the start of the App
    void EntityRegistry::Load()
    {
        // Intentionally empty. Please use scenes to setup Entities
    }
    
    // VIRTUAL OVERRIDE
    /// Release any resources remaining that are managed by this registry
    void EntityRegistry::Unload()
    {
        // Delete every child of root, and all of their children, but not the root itself
        lge::PCSNode* rootChild = this->rootEntity->getChild();
        lge::PCSNode* nextSibling = nullptr;
        while (rootChild != nullptr)
        {
            nextSibling = rootChild->getNextSibling();
            
            this->entityHierarchy.remove(rootChild);
            
            rootChild = nextSibling;
        }
        
        guarantee_that(this->entityHierarchy.getInfo().currNumNodes == 1, "Unloading every Entity except the ROOT Entity should have a node count of 1");
    }
    
    
    
    
    
    /// Update every Entity that currently exists
    void EntityRegistry::Update()
    {
        lge::PCSForwardIterator itr(this->entityHierarchy);
        Entity* currentEntity = (Entity*) itr.First(); // Root always bypassed
        while (itr.IsDone() == false)
        {
            // Update
            currentEntity->Update();
            
            // Next entity
            currentEntity = (Entity*) itr.Next();
        }
    }
    
    
    
    
    
    // STATIC
    /// Find any resource by name
    Entity* const EntityRegistry::Find(const char* const name)
    {
        lge::PCSForwardIterator itr(EntityRegistry::s_instance->entityHierarchy);
        Entity* foundEntity = (Entity*) itr.First();
        while (itr.IsDone() == false)
        {
            if(foundEntity->GetName() == name)
            {
                break;  // Found it
            }
            
            // Next entity
            foundEntity = (Entity*) itr.Next();
        }
        
        return foundEntity;
    }
    
    
    // STATIC
    /// Find any resource by ID
    Entity* const EntityRegistry::Find(const unsigned int id)
    {
        lge::PCSForwardIterator itr(EntityRegistry::s_instance->entityHierarchy);
        Entity* foundEntity = (Entity*) itr.First();
        while (itr.IsDone() == false)
        {
            if(foundEntity->GetId() == id)
            {
                break;  // Found it
            }
            
            // Next entity
            foundEntity = (Entity*) itr.Next();
        }
        
        return foundEntity;
    }
    
    
    // STATIC
    /// Creates a resource with given parameters, adds to this registry, and returns the created resource. Also define a parent entity for this entity
    Entity* const EntityRegistry::Create(Entity* const parentEntity, const char* const newName)
    {
        guarantee_that(EntityRegistry::s_instance != nullptr, "Registry singeton cannot create new resource because the registry doesn't exist!");
        
        guarantee_that(parentEntity != nullptr, "New Entity creation with a given parent, but the parent is null!");
        
        Entity* newResource = new Entity(newName);
        
        EntityRegistry::Add(newResource, parentEntity);
        
        return newResource;
    }
    
    // STATIC
    /// Creates a resource with given parameters, adds to this registry, and returns the created resource. Parent of this entity will be the "root" entity
    Entity* const EntityRegistry::Create(const char* const newName)
    {
        guarantee_that(EntityRegistry::s_instance != nullptr, "Registry singeton cannot create new resource because the registry doesn't exist!");
        
        Entity* newResource = new Entity(newName);
        
        EntityRegistry::Add(newResource, EntityRegistry::s_instance->rootEntity);
        
        return newResource;
    }
    
    
    
    // STATIC
    /// Resource must be dynaically allocated, but it will be deleted by this registry later
    void EntityRegistry::Add(Entity* const newEntity, Entity* const parentEntity)
    {
        guarantee_that(newEntity != nullptr, "Registry adding a null resource!");
        
        EntityRegistry::s_instance->entityHierarchy.insert(newEntity, parentEntity);
    }
    
}
