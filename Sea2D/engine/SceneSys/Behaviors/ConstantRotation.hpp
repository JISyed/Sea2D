//
//  ConstantRotation.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/1/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef ConstantRotation_hpp
#define ConstantRotation_hpp

#include "Behavior.hpp"

namespace sea2d
{
    /// Behavior that constantly rotates an Entity
    class ConstantRotation : public Behavior
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        ConstantRotation();
        
        /// Destructor
        virtual ~ConstantRotation();
        
        /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
        virtual const BehaviorIdentity GetBehaviorIdentity() const override;
        
        
        
        //
        // Additonal Methods
        //
        
        /// Get the rotation speed
        const float GetRotationSpeed() const;
        /// Set the rotation speed
        void SetRotationSpeed(const float newSpeed);
        
        
        
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
        
        float rotationSpeed;
        
        
        
    };
}
#endif /* ConstantRotation_hpp */
