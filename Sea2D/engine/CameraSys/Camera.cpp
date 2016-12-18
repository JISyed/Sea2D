//
//  Camera.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/21/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Camera.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include "engine/AppSys/IdGenerator.hpp"
#include <string>

namespace sea2d
{
    //
    // Statics
    //
    
    /// Generates IDs for every shader when the game runs
    static IdGenerator s_idGen;
    
    
    
    
    //
    // Methods
    //
    
    // Ctor
    Camera::Camera(const bool willBeActive) :
        id(s_idGen.MakeNewId()),
        camTransform(),
        camProjection(),
        camViewport(),
        name((std::string("Camera ") + std::to_string((int)id)).c_str()),
        isActive(willBeActive)
    {
    }
    
    // Dtor
    Camera::~Camera()
    {
    }
    
    
    
    /// Read only access to the position and rotation of the camera
    const CameraTransform& Camera::GetTransformData() const
    {
        return this->camTransform;
    }
    
    /// Read only access to the orthographical projection of the camera
    const CameraProjection& Camera::GetProjectionData() const
    {
        return this->camProjection;
    }
    
    /// Read only access to the mapping of the camera's OpenGL viewport
    const CameraViewport& Camera::GetViewportData() const
    {
        return this->camViewport;
    }
    
    /// Set the position of the camera
    void Camera::SetPosition(const Vector2& newPosition)
    {
        this->camTransform.position = newPosition;
    }
    
    /// Set the rotation of the camera (in radians)
    void Camera::SetRotation(const float newRotation)
    {
        this->camTransform.rotation = newRotation;
    }
    
    /// Set the projection data set (advanced)
    void Camera::SetProjection(const float newRightEdge, const float newTopEdge, const float newLeftEdge, const float newBottomEdge)
    {
        this->camProjection.rightEdge = newRightEdge;
        this->camProjection.topEdge = newTopEdge;
        this->camProjection.leftEdge = newLeftEdge;
        this->camProjection.bottomEdge = newBottomEdge;
    }
    
    /// Set the projection width and height of the camera in world space (projection origin will be in the center)
    void Camera::SetProjection(const float projectionWidth, const float projectionHeight)
    {
        this->camProjection.rightEdge = projectionWidth / 2.0f;
        this->camProjection.topEdge = projectionHeight / 2.0f;
        this->camProjection.leftEdge = projectionWidth / -2.0f;
        this->camProjection.bottomEdge = projectionHeight / -2.0f;
    }
    
    /// Set the near clip individually
    void Camera::SetNearClip(const float newNearClip)
    {
        this->camProjection.nearClip = newNearClip;
    }
    
    /// Set the far clip individually
    void Camera::SetFarClip(const float newFarClip)
    {
        this->camProjection.farClip = newFarClip;
    }
    
    /// Set the right edge individually
    void Camera::SetRightEdge(const float newRightEdge)
    {
        this->camProjection.rightEdge = newRightEdge;
    }
    
    /// Set the top edge individually
    void Camera::SetTopEdge(const float newTopEdge)
    {
        this->camProjection.topEdge = newTopEdge;
    }
    
    /// Set the left edge individually
    void Camera::SetLeftEdge(const float newLeftEdge)
    {
        this->camProjection.leftEdge = newLeftEdge;
    }
    
    /// Set the bottom edge individually
    void Camera::SetBottomEdge(const float newBottomEdge)
    {
        this->camProjection.bottomEdge = newBottomEdge;
    }
    
    
    /// Set all OpenGL viewport properties of this camera at once
    void Camera::SetViewport(const int originX, const int originY, const int width, const int height)
    {
        guarantee_that(originX >= 0, "Cam Viewport Origin X is negative!");
        guarantee_that(originY >= 0, "Cam Viewport Origin Y is negative!");
        guarantee_that(width > 0, "Cam Viewport Width is negative or zero!");
        guarantee_that(height > 0, "Cam Viewport Height is negative or zero!");
        
        this->camViewport.originX = originX;
        this->camViewport.originY = originY;
        this->camViewport.width = width;
        this->camViewport.height = height;
    }
    
    /// Set the X position (in pixels) of the OpenGL viewport of this camera
    void Camera::SetViewportOriginX(const int originX)
    {
        guarantee_that(originX >= 0, "Cam Viewport Origin X is negative!");
        this->camViewport.originX = originX;
    }
    
    /// Set the Y position (in pixels) of the OpenGL viewport of this camera
    void Camera::SetViewportOriginY(const int originY)
    {
        guarantee_that(originY >= 0, "Cam Viewport Origin Y is negative!");
        this->camViewport.originY = originY;
    }
    
    /// Set the width (in pixels) of the OpenGL viewport of this camera
    void Camera::SetViewportWidth(const int width)
    {
        guarantee_that(width > 0, "Cam Viewport Width is negative or zero!");
        this->camViewport.width = width;
    }
    
    /// Set the height (in pixels) of the OpenGL viewport of this camera
    void Camera::SetViewportHeight(const int height)
    {
        guarantee_that(height > 0, "Cam Viewport Height is negative or zero!");
        this->camViewport.height = height;
    }
    
    
    /// Get the read only name of this camera
    const StringFixed& Camera::GetName() const
    {
        return this->name;
    }
    
    /// Get the instance ID of this camera (unique for every camera) (not OpenGL handle!)
    const unsigned int Camera::GetId() const
    {
        return this->id;
    }
    
    /// Will this camera render? (Multiple cameras can render depending on order and viewports)
    const bool Camera::IsActive() const
    {
        return this->isActive;
    }
    
    /// Change whether this camera will render or not
    void Camera::SetActive(bool willBeActive)
    {
        this->isActive = willBeActive;
    }
    
    
}