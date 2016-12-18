//
//  ShaderRegistry.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/25/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef ShaderRegistry_hpp
#define ShaderRegistry_hpp

#include "engine/AppSys/IRegistry.hpp"
#include "engine/DataTypes/LinkedList.hpp"
#include "Shader.hpp"


namespace sea2d
{
    /// Serves as a container for holding all loaded Shaders in the app
    class ShaderRegistry final : public IRegistry
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        ShaderRegistry();
        
        /// Destructor
        virtual ~ShaderRegistry();
        
        
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
        static Shader* const Find(const char* const name);
        
        /// Find any resource by ID
        static Shader* const Find(const unsigned int id);
        
        
        /// Creates a resource with given parameters, adds to this registry, and returns the created resource
        static Shader* const Create(const char* const fileName, const char* const shaderName);
        
        /// Get the iterator for the shader list
        static const LinkedList<Shader>::Iterator GetIterator();
        
        
    private:
        
        //
        // Data
        //
        
        LinkedList<Shader> resourceList;      ///< List of managed resources
        static ShaderRegistry* s_instance;    ///< Singeton instance of this registry
        
        
        //
        // Private Routines
        //
        
        /// Resource must be dynaically allocated, but it will be deleted by this registry later
        static void Add(Shader* newResource);
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Copy Ctor
        ShaderRegistry(const ShaderRegistry& other) = delete;
        
        /// No Copy Assignment
        ShaderRegistry& operator=(const ShaderRegistry& rhs) = delete;
        
        /// No Move Ctor
        ShaderRegistry(ShaderRegistry&& other) = delete;
        
        /// No Move Assignment
        ShaderRegistry& operator=(ShaderRegistry&& rhs) = delete;
    };
}
#endif /* ShaderRegistry_hpp */
