//
//  ConstantRotation.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/1/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "ConstantRotation.hpp"
#include "engine/SceneSys/Entities/Entity.hpp"
#include "engine/MathSys/Mathf.hpp"
#include "engine/TimeSys/Time.hpp"


namespace sea2d
{
    //
    // Ctor / Dtor
    //
    
    /// Default Ctor
    ConstantRotation::ConstantRotation() :
        rotationSpeed(MathConstants::EighthPi)
    {
    }
    
    // VIRTUAL
    /// Destructor
    ConstantRotation::~ConstantRotation()
    {
    }

    
    
    //
    // Additonal Methods
    //
    
    /// Get the rotation speed
    const float ConstantRotation::GetRotationSpeed() const
    {
        return this->rotationSpeed;
    }
    
    /// Set the rotation speed
    void ConstantRotation::SetRotationSpeed(const float newSpeed)
    {
        this->rotationSpeed = newSpeed;
    }
    
    
    
    
    
    //
    // Behavior Identity
    //
    
    // VIRTUAL OVERRIDE
    /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
    const BehaviorIdentity ConstantRotation::GetBehaviorIdentity() const
    {
        return BehaviorIdentity::ConstantRotation;
    }
    
    
    
    
    //
    // Events
    //
    
    // VIRTUAL OVERRIDE
    /// Called when the Behavior is added to an Entity (called after constructor)
    void ConstantRotation::OnStart()
    {
        this->rotationSpeed = MathConstants::Pi / 4.0f;
    }

    
    // VIRTUAL OVERRIDE
    /// Called every iteration of the game loop
    void ConstantRotation::OnUpdate()
    {
        Transform& transform = this->GetEntity()->GetTransform();
        transform.SetRotation(transform.GetRotation() + (this->rotationSpeed * Time::GetDeltaTimeInSeconds()));
    }

    
    // VIRTUAL OVERRIDE
    /// Called whene the Behavior is removed from an Entity (called before destructor)
    void ConstantRotation::OnDestroy()
    {
        // Intentionally empty
    }

    
    
    
    
}
