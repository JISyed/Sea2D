//
//  Entity.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/1/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef Entity_hpp
#define Entity_hpp

#include "engine/SceneSys/Behaviors/Behavior.hpp"
#include "engine/DataTypes/LinkedList.hpp"
#include "engine/DataTypes/PCS/PCSNode.hpp"
#include "engine/DataTypes/StringFixed.hpp"
#include "Transform.hpp"

namespace sea2d
{
    /// Represents an entity in a scene that can have different behaviors. Basically a GameObject. Should NOT be inherited from
    class Entity final : public lge::PCSNode
    {
    public:
        
        //
        // Friendship
        //
        
        // EntityRegistry can access Entity
        friend class EntityRegistry;
        
        
        //
        // Methods
        //
        
        /// Add a Behavior to this Entity and return it.
        /// @remark  Can add multiple of the same Behaviors. Don't do it on accident
        Behavior* const AddBehavior(const BehaviorIdentity behavior);
        
        /// Get a Behavior from this Entity. Returns nullptr if it doesn't exist
        Behavior* const GetBehavior(const BehaviorIdentity behavior);
        
        /// Remove a Behavior from this Entity. Returns false if it doesn't exist
        const bool RemoveBehavior(const BehaviorIdentity behavior);
        
        /// Get the name of this Entity
        const StringFixed& GetName() const;
        
        /// Get the unique ID of this Entity
        const unsigned int GetId() const;
        
        /// Get the Transform of this Entity
        Transform& GetTransform();
        
        
        
        //
        // Static Methods
        //
        
        /// Create a new Entity that will be managed by the engine. Does not add any Behaviors. Also define a parent entity for this entity
        static Entity* const Create(Entity* const parentEntity, const char* const newName = "NamelessEntity");
        
        /// Create a new Entity that will be managed by the engine. Does not add any Behaviors. Parent of this entity will be the "root" entity
        static Entity* const Create(const char* const newName = "NamelessEntity");
        
        /// Find an Entity by name. Returns nullptr if not found
        static Entity* const Find(const char* const inquiredName);
        
        /// Find an Entity by ID. Returns nullptr if not found
        static Entity* const Find(const unsigned int inquriedId);
        
        
    private:
        
        //
        // Data
        //
        
        LinkedList<Behavior> behaviors;     ///< All Behaviors attached to this Entity
        unsigned int id;                    ///< The unique ID of this Entity
        Transform* transform;               ///< The transform data of this Entity
        StringFixed name;                   ///< The name of this Entity
        
        
        
        //
        // Private Methods (Called by EntityRegistry)
        //
        
        /// Update every Behavior in this Entity
        void Update();
        
        /// Default Ctor
        Entity();
        
        /// Name Ctor
        Entity(const char* const newName);
        
        /// Destructor
        ~Entity();
        
        
        
        
        
        //
        // Deleted Methods
        //
        
        
        /// No Copy Ctor
        Entity(const Entity& other) = delete;
        
        /// No Copy Assignment
        Entity& operator=(const Entity& rhs) = delete;
        
        /// No Move Ctor
        Entity(Entity&& other) = delete;
        
        /// No Move Assignment
        Entity& operator=(Entity&& rhs) = delete;
    };
}
#endif /* Entity_hpp */
