//
//  KeyTriggeredMovement.cpp
//  Sea2D
//
//  Created by Jibran Syed on 6/8/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "KeyTriggeredMovement.hpp"
#include "engine/SceneSys/Entities/Entity.hpp"
#include "engine/SceneSys/Entities/Transform.hpp"
#include "engine/TimeSys/Time.hpp"

namespace sea2d
{
    //
    // Ctor / Dtor
    //
    
    /// Default Ctor
    KeyTriggeredMovement::KeyTriggeredMovement() :
        rightKey(Input::Key::ArrowRight),
        leftKey(Input::Key::ArrowLeft),
        upKey(Input::Key::ArrowUp),
        downKey(Input::Key::ArrowDown),
        movementSpeed(80.0f),
        invertControls(false)
    {
    }
    
    // VIRTUAL
    /// Destructor
    KeyTriggeredMovement::~KeyTriggeredMovement()
    {
    }
    
    
    
    //
    // Additonal Methods
    //
    
    void KeyTriggeredMovement::SetMovementKeys(const Input::Key right, const Input::Key left, const Input::Key up, const Input::Key down)
    {
        this->rightKey = right;
        this->leftKey = left;
        this->upKey = up;
        this->downKey = down;
    }
    
    void KeyTriggeredMovement::SetMovementSpeed(const float newSpeed)
    {
        this->movementSpeed = newSpeed;
    }
    
    const float KeyTriggeredMovement::GetMovementSpeed() const
    {
        return this->movementSpeed;
    }
    
    void KeyTriggeredMovement::SetInvertControls(const bool shouldInvert)
    {
        this->invertControls = shouldInvert;
    }
    
    
    
    //
    // Behavior Identity
    //
    
    // VIRTUAL OVERRIDE
    /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
    const BehaviorIdentity KeyTriggeredMovement::GetBehaviorIdentity() const
    {
        return BehaviorIdentity::KeyTriggeredMovement;
    }
    
    
    
    
    //
    // Events
    //
    
    // VIRTUAL OVERRIDE
    /// Called when the Behavior is added to an Entity (called after constructor)
    void KeyTriggeredMovement::OnStart()
    {
        
    }
    
    
    // VIRTUAL OVERRIDE
    /// Called every iteration of the game loop
    void KeyTriggeredMovement::OnUpdate()
    {
        Transform& transform = this->GetEntity()->GetTransform();
        const Vector2 oldPosition = transform.GetPosition();
        Vector2 newPosition = oldPosition;
        
        if(this->invertControls)
        {
            if(Input::Keyboard::GetKey(this->rightKey))
            {
                newPosition.set(oldPosition.x() - this->movementSpeed * Time::GetDeltaTimeInSeconds(), oldPosition.y());
            }
            if(Input::Keyboard::GetKey(this->leftKey))
            {
                newPosition.set(oldPosition.x() + this->movementSpeed * Time::GetDeltaTimeInSeconds(), oldPosition.y());
            }
            if(Input::Keyboard::GetKey(this->upKey))
            {
                newPosition.set(oldPosition.x(), oldPosition.y() - this->movementSpeed * Time::GetDeltaTimeInSeconds());
            }
            if(Input::Keyboard::GetKey(this->downKey))
            {
                newPosition.set(oldPosition.x(), oldPosition.y() + this->movementSpeed * Time::GetDeltaTimeInSeconds());
            }
        }
        else
        {
            if(Input::Keyboard::GetKey(this->rightKey))
            {
                newPosition.set(oldPosition.x() + this->movementSpeed * Time::GetDeltaTimeInSeconds(), oldPosition.y());
            }
            if(Input::Keyboard::GetKey(this->leftKey))
            {
                newPosition.set(oldPosition.x() - this->movementSpeed * Time::GetDeltaTimeInSeconds(), oldPosition.y());
            }
            if(Input::Keyboard::GetKey(this->upKey))
            {
                newPosition.set(oldPosition.x(), oldPosition.y() + this->movementSpeed * Time::GetDeltaTimeInSeconds());
            }
            if(Input::Keyboard::GetKey(this->downKey))
            {
                newPosition.set(oldPosition.x(), oldPosition.y() - this->movementSpeed * Time::GetDeltaTimeInSeconds());
            }
        }
            
        transform.SetPosition(newPosition);
    }
    
    
    // VIRTUAL OVERRIDE
    /// Called whene the Behavior is removed from an Entity (called before destructor)
    void KeyTriggeredMovement::OnDestroy()
    {
        // Intentionally empty
    }
}