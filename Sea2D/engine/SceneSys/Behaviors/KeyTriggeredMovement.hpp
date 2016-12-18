//
//  KeyTriggeredMovement.hpp
//  Sea2D
//
//  Created by Jibran Syed on 6/8/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef KeyTriggeredMovement_hpp
#define KeyTriggeredMovement_hpp

#include "Behavior.hpp"
#include "engine/InputSys/Keyboard.hpp"

namespace sea2d
{
    /// Behavior that constantly rotates an Entity
    class KeyTriggeredMovement : public Behavior
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        KeyTriggeredMovement();
        
        /// Destructor
        virtual ~KeyTriggeredMovement();
        
        /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
        virtual const BehaviorIdentity GetBehaviorIdentity() const override;
        
        
        
        //
        // Additonal Methods
        //
        
        void SetMovementKeys(const Input::Key right, const Input::Key left, const Input::Key up, const Input::Key down);
        
        void SetMovementSpeed(const float newSpeed);
        
        const float GetMovementSpeed() const;
        
        void SetInvertControls(const bool shouldInvert);
        
        
    protected:
        
        
        //
        // Events
        //
        
        /// Called when the Behavior is added to an Entity (called after constructor)
        virtual void OnStart() override;
        
        /// Called every iteration of the game loop
        virtual void OnUpdate() override;
        
        /// Called whene the Behavior is removed from an Entity (called before destructor)
        virtual void OnDestroy() override;
        
        
    private:
        
        //
        // Data
        //
        
        Input::Key rightKey;
        Input::Key leftKey;
        Input::Key upKey;
        Input::Key downKey;
        float movementSpeed;
        bool invertControls;
        
        
    };
}
#endif /* KeyTriggeredMovement_hpp */
