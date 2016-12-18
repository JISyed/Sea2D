//
//  CameraBehavior.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/7/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "CameraBehavior.hpp"
#include "engine/CameraSys/CameraRegistry.hpp"
#include "engine/CameraSys/Camera.hpp"
#include "engine/SceneSys/Entities/Transform.hpp"
#include "engine/SceneSys/Entities/Entity.hpp"

namespace sea2d
{
    //
    // Ctor / Dtor
    //
    
    /// Default Ctor
    CameraBehavior::CameraBehavior() :
        camera(nullptr)
    {
        this->camera = CameraRegistry::Create(true, Vector2(0.0f, 0.0f), 0.0f);
    }
    
    // VIRTUAL
    /// Destructor
    CameraBehavior::~CameraBehavior()
    {
        CameraRegistry::Remove(this->camera);
    }
    
    
    
    //
    // Additonal Methods
    //
    
    
    
    
    
    
    
    //
    // Behavior Identity
    //
    
    // VIRTUAL OVERRIDE
    /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
    const BehaviorIdentity CameraBehavior::GetBehaviorIdentity() const
    {
        return BehaviorIdentity::CameraBehavior;
    }
    
    
    
    
    //
    // Events
    //
    
    // VIRTUAL OVERRIDE
    /// Called when the Behavior is added to an Entity (called after constructor)
    void CameraBehavior::OnStart()
    {
        // Intentionally does nothing
    }
    
    
    // VIRTUAL OVERRIDE
    /// Called every iteration of the game loop
    void CameraBehavior::OnUpdate()
    {
        // Align the camera transform the the entity's transform
        const Transform& transform = this->GetEntity()->GetTransform();
        this->camera->SetPosition(transform.GetGlobalPosition());
        this->camera->SetRotation(transform.GetGlobalRotation());
    }
    
    
    // VIRTUAL OVERRIDE
    /// Called whene the Behavior is removed from an Entity (called before destructor)
    void CameraBehavior::OnDestroy()
    {
        // Intentionally does nothing
    }
    
    
    
    
    
    //
    // Additonal Methods
    //
    
    /// Set the projection data set (advanced)
    void CameraBehavior::SetProjection(const float newRightEdge, const float newTopEdge, const float newLeftEdge, const float newBottomEdge)
    {
        this->camera->SetProjection(newRightEdge, newTopEdge, newLeftEdge, newBottomEdge);
    }
    
    /// Set the projection width and height of the camera in world space (projection origin will be in the center)
    void CameraBehavior::SetProjection(const float projectionWidth, const float projectionHeight)
    {
        this->camera->SetProjection(projectionWidth, projectionHeight);
    }
    
    /// Set all OpenGL viewport properties of this camera at once
    void CameraBehavior::SetViewport(const int originX, const int originY, const int width, const int height)
    {
        this->camera->SetViewport(originX, originY, width, height);
    }
    
    /// Get the projection data of this camera
    const CameraProjection& CameraBehavior::GetProjection() const
    {
        return this->camera->GetProjectionData();
    }
    
    /// Get the OpenGL viewport data of this camera
    const CameraViewport& CameraBehavior::GetViewport() const
    {
        return this->camera->GetViewportData();
    }
    
    /// Get the read only name of this camera
    const StringFixed& CameraBehavior::GetName() const
    {
        return this->camera->GetName();
    }
    
    /// Get the instance ID of the camera controlled by this behavior (unique for every camera)
    const unsigned int CameraBehavior::GetId() const
    {
        return this->camera->GetId();
    }
    
    /// Will this camera render? (Multiple cameras can render depending on order and viewports)
    const bool CameraBehavior::IsActive() const
    {
        return this->camera->IsActive();
    }
    
    /// Change whether this camera will render or not
    void CameraBehavior::SetActive(bool willBeActive)
    {
        this->camera->SetActive(willBeActive);
    }
    
    
}
