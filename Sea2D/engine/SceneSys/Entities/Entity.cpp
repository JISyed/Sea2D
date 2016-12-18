//
//  Entity.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/1/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Entity.hpp"
#include "engine/AppSys/IdGenerator.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include "EntityRegistry.hpp"
#include "engine/SceneSys/Behaviors/EveryBehaviorInclude.hpp"

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
    
    /// PRIVATE
    // Default Ctor
    Entity::Entity() :
        behaviors(),
        id(s_idGen.MakeNewId()),
        transform(nullptr),
        name("NamelessEntity")
    {
        this->transform = new Transform(this);
    }
    
    /// PRIVATE
    // Name Ctor
    Entity::Entity(const char* const newName) :
        behaviors(),
        id(s_idGen.MakeNewId()),
        transform(nullptr),
        name(newName)
    {
        guarantee_that(newName != nullptr, "New name for Entity is null!");
        this->transform = new Transform(this);
    }
    
    /// PRIVATE
    // Dtor
    Entity::~Entity()
    {
        while(this->behaviors.GetNumberOfElements() != 0)
        {
            Behavior* oldBehavior = this->behaviors.RemoveFront();
            oldBehavior->OnDestroy();
            delete oldBehavior;
        }
        
        delete this->transform;
    }
    
    
    
    
    /// Add a Behavior to this Entity and return it.
    /// @remark  Can add multiple of the same Behaviors. Don't do it on accident
    Behavior* const Entity::AddBehavior(const BehaviorIdentity behavior)
    {
        Behavior* newBehavior = nullptr;
        
        switch (behavior)
        {
            case BehaviorIdentity::SpriteRenderer:
            {
                newBehavior = new SpriteRenderer();
                break;
            }
            case BehaviorIdentity::ConstantRotation:
            {
                newBehavior = new ConstantRotation();
                break;
            }
            case BehaviorIdentity::CameraBehavior:
            {
                newBehavior = new CameraBehavior();
                break;
            }
            case BehaviorIdentity::BitmapText:
            {
                newBehavior = new BitmapText();
                break;
            }
            case BehaviorIdentity::TexturedMeshRenderer:
            {
                newBehavior = new TexturedMeshRenderer();
                break;
            }
            case BehaviorIdentity::KeyTriggeredMovement:
            {
                newBehavior = new KeyTriggeredMovement();
                break;
            }
            case BehaviorIdentity::KeyTriggerSceneSwitcher:
            {
                newBehavior = new KeyTriggerSceneSwitcher();
                break;
            }
            default:
            {
                guarantee_that(false, "AddBehavior() needs new case for an unsupported BehaviorIdentity");
                break;
            }
        }
        
        
        if(newBehavior != nullptr)
        {
            this->behaviors.AddSorted(newBehavior, (int) behavior);
            newBehavior->entity = this;
            newBehavior->OnStart();
        }
        
        return newBehavior;
    }
    
    /// Get a Behavior from this Entity. Returns nullptr if it doesn't exist
    Behavior* const Entity::GetBehavior(const BehaviorIdentity behavior)
    {
        Behavior* foundBehavior = nullptr;
        
        for(auto itr = this->behaviors.GetIterator(); itr.IsDone() == false; itr.Next())
        {
            Behavior* const currentBehavior = itr.CurrentItem();
            if(currentBehavior->GetBehaviorIdentity() == behavior)
            {
                foundBehavior = currentBehavior;
                break;
            }
        }
        
        return foundBehavior;
    }

    
    /// Remove a Behavior from this Entity. Returns false if it doesn't exist
    const bool Entity::RemoveBehavior(const BehaviorIdentity behavior)
    {
        Behavior* oldBehavior = this->GetBehavior(behavior);
        bool removedSuccessfully = false;
        
        if(oldBehavior != nullptr)
        {
            removedSuccessfully = true;
            this->behaviors.RemoveByObject(oldBehavior);
            oldBehavior->OnDestroy();
            delete oldBehavior;
        }
        
        return removedSuccessfully;
    }

    
    /// Get the name of this Entity
    const StringFixed& Entity::GetName() const
    {
        return this->name;
    }

    
    /// Get the unique ID of this Entity
    const unsigned int Entity::GetId() const
    {
        return this->id;
    }

    /// Get the Transform of this Entity
    Transform& Entity::GetTransform()
    {
        return *(this->transform);
    }
    
    
    
    // STATIC
    /// Create a new Entity that will be managed by the engine. Does not add any Behaviors
    Entity* const Entity::Create(Entity* const parentEntity, const char* const newName)
    {
        guarantee_that(newName != nullptr, "Creating an Entity, but given a null name!");
        return EntityRegistry::Create(parentEntity, newName);
    }
    
    // STATIC
    /// Create a new Entity that will be managed by the engine. Does not add any Behaviors
    Entity* const Entity::Create(const char* const newName)
    {
        guarantee_that(newName != nullptr, "Creating an Entity, but given a null name!");
        return EntityRegistry::Create(newName);
    }
    
    

    // STATIC
    /// Find an Entity by name. Returns nullptr if not found
    Entity* const Entity::Find(const char* const inquiredName)
    {
        guarantee_that(inquiredName != nullptr, "Finding an Entity, but given a null name!");
        return EntityRegistry::Find(inquiredName);
    }

    // STATIC
    /// Find an Entity by ID. Returns nullptr if not found
    Entity* const Entity::Find(const unsigned int inquriedId)
    {
        return EntityRegistry::Find(inquriedId);
    }

    
    
    
    
    /// Update every Behavior in this Entity
    void Entity::Update()
    {
        // Update the global transform data
        {
            Entity* parent = (Entity*) this->getParent();
            if(parent != nullptr)
            {
                Transform& parentTransform = parent->GetTransform();
                this->transform->SetParentWorldPosition(parentTransform.GetGlobalPosition());
                this->transform->SetParentWorldRotation(parentTransform.GetGlobalRotation());
                this->transform->SetParentWorldScale(parentTransform.GetGlobalScale());
            }
        }
        
        // Update the Behaviors (if it has any)
        for(auto itr = this->behaviors.GetIterator(); itr.IsDone() == false; itr.Next())
        {
            Behavior* const currentBehavior = itr.CurrentItem();
            currentBehavior->OnUpdate();
        }
    }

    
    
}
