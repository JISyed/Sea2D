//
//  Behavior.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/1/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef Behavior_hpp
#define Behavior_hpp

#include "BehaviorIdentity.hpp"

namespace sea2d
{
    // Forward declare Entity
    class Entity;
    
    // Note: Making a new Behavior requires a switch entry to be added in Entity::AddBehavior()
    
    /// Base class of any behavior that an Entity can have, modulalizing Entity properties
    class Behavior
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        Behavior();
        
        /// Destructor
        virtual ~Behavior();
        
        // Entity can access Behavior (to call events)
        friend class Entity;
        
        
        //
        // Methods
        //
        
        
        
        /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
        virtual const BehaviorIdentity GetBehaviorIdentity() const = 0;
        
        /// Get the Entity this Behavior is attached to (will never return nullptr)
        Entity* const GetEntity();
        
        
    protected:
        
        //
        // Events
        //
        
        /// Called when the Behavior is added to an Entity (called after constructor)
        virtual void OnStart() = 0;
        
        /// Called every iteration of the game loop
        virtual void OnUpdate() = 0;
        
        /// Called whene the Behavior is removed from an Entity (called before destructor)
        virtual void OnDestroy() = 0;
        
        
    private:
        
        //
        // Data
        //
        
        Entity* entity;     ///< The Entity that this Behavior is attached to
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Copy Ctor
        Behavior(const Behavior& other) = delete;
        
        /// No Copy Assignment
        Behavior& operator=(const Behavior& rhs) = delete;
        
        /// No Move Ctor
        Behavior(Behavior&& other) = delete;
        
        /// No Move Assignment
        Behavior& operator=(Behavior&& rhs) = delete;
    };
}
#endif /* Behavior_hpp */
