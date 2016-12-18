//
//  CameraRegistry.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/25/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef CameraRegistry_hpp
#define CameraRegistry_hpp

#include "engine/AppSys/IRegistry.hpp"
#include "engine/DataTypes/LinkedList.hpp"
#include "Camera.hpp"


namespace sea2d
{
    /// Serves as a container for holding all loaded Cameras in the app
    class CameraRegistry final : public IRegistry
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        CameraRegistry();
        
        /// Destructor
        virtual ~CameraRegistry();
        
        
        //
        // Methods
        //
        
        /// Decide what resources to load at the start of the App
        virtual void Load() override;
        
        /// Release any resources remaining that are managed by this registry
        virtual void Unload() override;
        
        /// Get the iterator for the camera list
        const LinkedList<Camera>::Iterator GetIterator() const;
        
        
        //
        // Static Methods
        //
        
        /// Find any resource by name
        static Camera* const Find(const char* const name);
        
        /// Find any resource by ID
        static Camera* const Find(const unsigned int id);
        
        
        /// Creates a camera with given parameters, adds to this registry, and returns the created resource
        static Camera* const Create(const bool willBeActive, const Vector2& newPosition, const float newRotation);
        
        /// Creates a camera with given parameters, adds to this registry, and returns the created resource
        static Camera* const Create(const bool willBeActive, const Vector2& newPosition, const float newRotation, const float newWidth, const float newHeight);
        
        /// Creates a camera with given parameters, adds to this registry, and returns the created resource
        static Camera* const Create(const bool willBeActive, const Vector2& newPosition, const float newRotation, const float newWidth, const float newHeight, const int newViewportX, const int newViewportY, const int newViewportWidth, const int newViewportHeight);
        
        /// Delete a camera from the registry given a valid camera. Will invalidate pointer
        static const bool Remove(Camera*& toBeRemoved);
        
        
    private:
        
        //
        // Data
        //
        
        LinkedList<Camera> resourceList;      ///< List of managed resources
        static CameraRegistry* s_instance;    ///< Singeton instance of this registry
        
        
        //
        // Private Routines
        //
        
        /// Resource must be dynaically allocated, but it will be deleted by this registry later
        static void Add(Camera* newResource);
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Copy Ctor
        CameraRegistry(const CameraRegistry& other) = delete;
        
        /// No Copy Assignment
        CameraRegistry& operator=(const CameraRegistry& rhs) = delete;
        
        /// No Move Ctor
        CameraRegistry(CameraRegistry&& other) = delete;
        
        /// No Move Assignment
        CameraRegistry& operator=(CameraRegistry&& rhs) = delete;
    };
}
#endif /* CameraRegistry_hpp */
