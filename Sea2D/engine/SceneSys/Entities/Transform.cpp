//
//  Transform.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/2/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Transform.hpp"
#include "engine/MathSys/Mathf.hpp"

namespace sea2d
{
    // Ctor
    Transform::Transform(Entity* const associatedEntity) :
        position(0.0f, 0.0f),
        rotation(0.0f),
        scale(1.0f, 1.0f),
        depth(0.0f),
        parentWorldPosition(0.0f, 0.0f),
        parentWorldRotation(0.0f),
        parentWorldScale(1.0f, 1.0f),
        entity(associatedEntity)
    {
    }
    
    // Copy Assignment Overload
    Transform& Transform::operator=(const Transform& rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }
        
        this->position = rhs.position;
        this->rotation = rhs.rotation;
        this->scale = rhs.scale;
        
        return *this;
    }
    
    // Dtor
    Transform::~Transform()
    {
    }
    
    
    
    /// Get the local position (recommended)
    const Vector2 Transform::GetPosition() const
    {
        return this->position;
    }
    
    /// Get the local rotation in radians (recommended)
    const float Transform::GetRotation() const
    {
        return this->rotation;
    }
    
    /// Get the local scale (recommended)
    const Vector2 Transform::GetScale() const
    {
        return this->scale;
    }
    
    
    /// Set the local position
    void Transform::SetPosition(const Vector2& newPosition)
    {
        this->position = newPosition;
    }
    
    /// Set the local rotation in radians
    void Transform::SetRotation(const float newRotation)
    {
        this->rotation = newRotation;
    }
    
    /// Set the local scale
    void Transform::SetScale(const Vector2& newScale)
    {
        this->scale = newScale;
    }
    
    
    /// Get the global position in world space
    const Vector2 Transform::GetGlobalPosition() const
    {
        return this->position.getRotated(this->parentWorldRotation) + this->parentWorldPosition;
    }
    
    /// Get the global rotation in world space
    const float Transform::GetGlobalRotation() const
    {
        return this->rotation + this->parentWorldRotation;
    }
    
    /// Get the global scale in world space
    const Vector2 Transform::GetGlobalScale() const
    {
        return Vector2(this->scale.x() * this->parentWorldScale.x() ,
                       this->scale.y() * this->parentWorldScale.y() );
    }
    
    
    /// Get the local right direction (recommended)
    const Vector2 Transform::GetRight() const
    {
        return Vector2::Right.getRotated(this->rotation);
    }
    
    /// Get the local up direction (recommended)
    const Vector2 Transform::GetUp() const
    {
        return Vector2::Up.getRotated(this->rotation);
    }
    
    
    /// Get the global right direction in world space
    const Vector2 Transform::GetGlobalRight() const
    {
        return Vector2::Right.getRotated(this->GetGlobalRotation());
    }
    
    /// Get the global up direction in world space
    const Vector2 Transform::GetGlobalUp() const
    {
        return Vector2::Up.getRotated(this->GetGlobalRotation());
    }
    
    
    /// Get the depth of this transform
    const float Transform::GetDepth() const
    {
        return this->depth;
    }
    
    /// Set the depth of this transform (must be between -100 and +100)
    void Transform::SetDepth(const float newDepth)
    {
        this->depth = Mathf::Clamp(newDepth, -100.0f, 100.0f);
    }
    
    
    
    
    void Transform::SetParentWorldPosition(const Vector2& value)
    {
        this->parentWorldPosition = value;
    }
    
    void Transform::SetParentWorldRotation(const float value)
    {
        this->parentWorldRotation = value;
    }
    
    void Transform::SetParentWorldScale(const Vector2& value)
    {
        this->parentWorldScale = value;
    }
    
    
}
