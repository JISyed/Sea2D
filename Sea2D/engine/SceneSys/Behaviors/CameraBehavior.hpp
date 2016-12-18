//
//  CameraBehavior.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/7/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef CameraBehavior_hpp
#define CameraBehavior_hpp

#include "Behavior.hpp"
#include "CameraProjection.hpp"
#include "CameraViewport.hpp"
#include "engine/DataTypes/StringFixed.hpp"

namespace sea2d
{
    // Forward declare Camera
    class Camera;
    
    /// Behavior that constantly rotates an Entity
    class CameraBehavior : public Behavior
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        CameraBehavior();
        
        /// Destructor
        virtual ~CameraBehavior();
        
        /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
        virtual const BehaviorIdentity GetBehaviorIdentity() const override;
        
        
        
        //
        // Additonal Methods
        //
        
        /// Set the projection data set (advanced)
        void SetProjection(const float newRightEdge, const float newTopEdge, const float newLeftEdge, const float newBottomEdge);
        
        /// Set the projection width and height of the camera in world space (projection origin will be in the center)
        void SetProjection(const float projectionWidth, const float projectionHeight);
        
        /// Set all OpenGL viewport properties of this camera at once
        void SetViewport(const int originX, const int originY, const int width, const int height);
        
        /// Get the projection data of this camera
        const CameraProjection& GetProjection() const;
        
        /// Get the OpenGL viewport data of this camera
        const CameraViewport& GetViewport() const;
        
        /// Get the read only name of this camera
        const StringFixed& GetName() const;
        
        /// Get the instance ID of the camera controlled by this behavior (unique for every camera)
        const unsigned int GetId() const;
        
        /// Will this camera render? (Multiple cameras can render depending on order and viewports)
        const bool IsActive() const;
        
        /// Change whether this camera will render or not
        void SetActive(bool willBeActive);
        
        
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
        
        Camera* camera;     ///< Actual camera controlled by this behavior
        
    };
}
#endif /* CameraBehavior_hpp */
