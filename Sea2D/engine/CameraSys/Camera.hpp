//
//  Camera.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/21/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef Camera_hpp
#define Camera_hpp

#include "CameraTransform.hpp"
#include "CameraProjection.hpp"
#include "CameraViewport.hpp"
#include "engine/DataTypes/StringFixed.hpp"

namespace sea2d
{
    /// Camera with orthographic project fit for 2D views
    class Camera
    {
    public:
        
        //
        // Essentials
        //
        
        /// Ctor
        Camera(const bool willBeActive);
        
        /// Destructor
        ~Camera();
        
        
        
        //
        // Methods
        //
        
        /// Read only access to the position and rotation of the camera
        const CameraTransform& GetTransformData() const;
        
        /// Read only access to the orthographical projection of the camera
        const CameraProjection& GetProjectionData() const;
        
        /// Read only access to the mapping of the camera's OpenGL viewport
        const CameraViewport& GetViewportData() const;
        
        /// Set the position of the camera
        void SetPosition(const Vector2& newPosition);
        
        /// Set the rotation of the camera (in radians)
        void SetRotation(const float newRotation);
        
        /// Set the projection data set (advanced)
        void SetProjection(const float newRightEdge, const float newTopEdge, const float newLeftEdge, const float newBottomEdge);
        
        /// Set the projection width and height of the camera in world space (projection origin will be in the center)
        void SetProjection(const float projectionWidth, const float projectionHeight);
        
        /// Set the near clip individually
        void SetNearClip(const float newNearClip);
        
        /// Set the far clip individually
        void SetFarClip(const float newFarClip);
        
        /// Set the right edge individually
        void SetRightEdge(const float newRightEdge);
        
        /// Set the top edge individually
        void SetTopEdge(const float newTopEdge);
        
        /// Set the left edge individually
        void SetLeftEdge(const float newLeftEdge);
        
        /// Set the bottom edge individually
        void SetBottomEdge(const float newBottomEdge);
        
        /// Set all OpenGL viewport properties of this camera at once
        void SetViewport(const int originX, const int originY, const int width, const int height);
        
        /// Set the X position (in pixels) of the OpenGL viewport of this camera
        void SetViewportOriginX(const int originX);
        
        /// Set the Y position (in pixels) of the OpenGL viewport of this camera
        void SetViewportOriginY(const int originY);
        
        /// Set the width (in pixels) of the OpenGL viewport of this camera
        void SetViewportWidth(const int width);
        
        /// Set the height (in pixels) of the OpenGL viewport of this camera
        void SetViewportHeight(const int height);
        
        
        /// Get the read only name of this camera
        const StringFixed& GetName() const;
        
        /// Get the instance ID of this camera (unique for every camera) (not OpenGL handle!)
        const unsigned int GetId() const;
        
        /// Will this camera render? (Multiple cameras can render depending on order and viewports)
        const bool IsActive() const;
        
        /// Change whether this camera will render or not
        void SetActive(bool willBeActive);
        
        
        
    private:
        
        //
        // Data
        //
        
        unsigned int id;                    ///< The unique identifier for this camera
        CameraTransform camTransform;       ///< The camera's transfrom
        CameraProjection camProjection;     ///< The orthographic projection data
        CameraViewport camViewport;         ///< The viewport mapping
        StringFixed name;                   ///< The name of this camera
        bool isActive;                      ///< Active cameras will render
        
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Default Ctor
        Camera() = delete;
        
        /// No Copy Ctor
        Camera(const Camera& other) = delete;
        
        /// No Copy Assignment
        Camera& operator=(const Camera& rhs) = delete;
        
    };
}

#endif /* Camera_hpp */
