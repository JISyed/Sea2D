//
//  MeshRegistry.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/24/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef MeshRegistry_hpp
#define MeshRegistry_hpp

#include "engine/AppSys/IRegistry.hpp"
#include "engine/DataTypes/LinkedList.hpp"
#include "Mesh.hpp"


namespace sea2d
{
    /// Serves as a container for holding all loaded Meshes in the app
    class MeshRegistry final : public IRegistry
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        MeshRegistry();
        
        /// Destructor
        virtual ~MeshRegistry();
        
        
        //
        // Methods
        //
        
        /// Decide what resources to load at the start of the App
        virtual void Load() override;
        
        /// Release any resources remaining that are managed by this registry
        virtual void Unload() override;
        
        
        //
        // Static Methods
        //
        
        /// Find any resource by name
        static Mesh* const Find(const char* const name);
        
        /// Find any resource by ID
        static Mesh* const Find(const unsigned int id);
        
        
        /// Creates a resource with given parameters, adds to this registry, and returns the created resource
        static Mesh* const Create(const GLfloat* const vertexData, const size_t elementsInVertexData, const GLuint* const triangeData, const size_t elementsInTriangleData, const char* const newName);
        
        
        
    private:
        
        //
        // Data
        //
        
        LinkedList<Mesh> resourceList;      ///< List of managed resources
        static MeshRegistry* s_instance;    ///< Singeton instance of this registry
        
        
        //
        // Private Routines
        //
        
        /// Resource must be dynaically allocated, but it will be deleted by this registry later
        static void Add(Mesh* newResource);
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Copy Ctor
        MeshRegistry(const MeshRegistry& other) = delete;
        
        /// No Copy Assignment
        MeshRegistry& operator=(const MeshRegistry& rhs) = delete;
        
        /// No Move Ctor
        MeshRegistry(MeshRegistry&& other) = delete;
        
        /// No Move Assignment
        MeshRegistry& operator=(MeshRegistry&& rhs) = delete;
    };
}
#endif /* MeshRegistry_hpp */
