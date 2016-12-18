//
//  RenderUnitRegistry.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/2/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef RenderUnitRegistry_hpp
#define RenderUnitRegistry_hpp

#include "engine/AppSys/IRegistry.hpp"
#include "engine/DataTypes/LinkedList.hpp"
#include "RenderUnit.hpp"

namespace sea2d
{
    // Forward declare Camera
    class Camera;
    
    /// Serves as a container for holding all loaded Meshes in the app
    class RenderUnitRegistry final : public IRegistry
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        RenderUnitRegistry();
        
        /// Destructor
        virtual ~RenderUnitRegistry();
        
        
        //
        // Methods
        //
        
        /// Decide what resources to load at the start of the App
        virtual void Load() override;
        
        /// Release any resources remaining that are managed by this registry
        virtual void Unload() override;
        
        /// Draw every render unit currently being managed with the given camera
        void Draw(const Camera* const currentCamera);
        
        
        
        //
        // Static Methods
        //
        
        /// Find any resource by ID
        static RenderUnit* const Find(const unsigned int id);
        
        /// Deletes any RenderUnit, given its ID. Should only be called by a Renderer Behavior!
        static const bool Remove(const unsigned int id);
        
        /// Resource must be dynaically allocated, but it will be deleted by this registry later
        static void Add(RenderUnit* newResource);
        
    private:
        
        //
        // Data
        //
        
        LinkedList<RenderUnit> resourceList;      ///< List of managed resources
        static RenderUnitRegistry* s_instance;    ///< Singeton instance of this registry
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Copy Ctor
        RenderUnitRegistry(const RenderUnitRegistry& other) = delete;
        
        /// No Copy Assignment
        RenderUnitRegistry& operator=(const RenderUnitRegistry& rhs) = delete;
        
        /// No Move Ctor
        RenderUnitRegistry(RenderUnitRegistry&& other) = delete;
        
        /// No Move Assignment
        RenderUnitRegistry& operator=(RenderUnitRegistry&& rhs) = delete;
    };

}
#endif /* RenderUnitRegistry_hpp */
