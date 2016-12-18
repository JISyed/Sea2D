//
//  Transform.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/2/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef Transform_hpp
#define Transform_hpp

#include "engine/MathSys/Vector2.hpp"

namespace sea2d
{
    // Forward declare Entity
    class Entity;
    
    
    /// Represents world transformations of Entities (position, scale, rotation)
    class Transform
    {
    public:
        
        //
        // Essentials
        //
        
        // Ctor
        Transform(Entity* const associatedEntity);
        
        // Copy Assignment (only copies local transform)
        Transform& operator=(const Transform& rhs);
        
        // Destructor
        ~Transform();
        
        // Entity can access Transform
        friend class Entity;
        
        
        //
        // Methods
        //
        
        /// Get the local position (recommended)
        const Vector2 GetPosition() const;
        /// Get the local rotation in radians (recommended)
        const float GetRotation() const;
        /// Get the local scale (recommended)
        const Vector2 GetScale() const;
        
        /// Set the local position
        void SetPosition(const Vector2& newPosition);
        /// Set the local rotation in radians
        void SetRotation(const float newRotation);
        /// Set the local scale
        void SetScale(const Vector2& newScale);
        
        /// Get the global position in world space
        const Vector2 GetGlobalPosition() const;
        /// Get the global rotation in world space
        const float GetGlobalRotation() const;
        /// Get the global scale in world space
        const Vector2 GetGlobalScale() const;
        
        /// Get the local right direction (recommended)
        const Vector2 GetRight() const;
        /// Get the local up direction (recommended)
        const Vector2 GetUp() const;
        
        /// Get the global right direction in world space
        const Vector2 GetGlobalRight() const;
        /// Get the global up direction in world space
        const Vector2 GetGlobalUp() const;
        
        /// Get the depth of this transform
        const float GetDepth() const;
        
        /// Set the depth of this transform (must be between -100 and +100)
        void SetDepth(const float newDepth);
        
        
    private:
        
        //
        // Data
        //
        
        Vector2 position;       ///< Position relative to the parent
        float rotation;         ///< Rotation relative to the parent (in radians)
        Vector2 scale;          ///< Scale relative to the parent
        float depth;            ///< Depth of 2D transform (between -100 and +100)
        
        Vector2 parentWorldPosition;    ///< Parent's position in world space
        float parentWorldRotation;      ///< Parent's rotation in world space
        Vector2 parentWorldScale;       ///< Parent's scale in world space
        
        Entity* entity;         ///< The entity this transform applies to
        
        
        
        //
        // Private Methods (can only be called by Entity)
        //
        
        void SetParentWorldPosition(const Vector2& value);
        void SetParentWorldRotation(const float value);
        void SetParentWorldScale(const Vector2& value);
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Default Ctor
        Transform() = delete;
        
        /// No Copy Ctor
        Transform(const Transform& other) = delete;
    };
}
#endif /* Transform_hpp */
