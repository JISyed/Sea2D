//
//  TextureRegistry.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/25/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef TextureRegistry_hpp
#define TextureRegistry_hpp

#include "engine/AppSys/IRegistry.hpp"
#include "engine/DataTypes/LinkedList.hpp"
#include "engine/GraphicsSys/Texture.hpp"


namespace sea2d
{
    /// Serves as a container for holding all loaded Textures in the app
    class TextureRegistry final : public IRegistry
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        TextureRegistry();
        
        /// Destructor
        virtual ~TextureRegistry();
        
        
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
        static Texture* const Find(const char* const name);
        
        /// Find any resource by ID
        static Texture* const Find(const unsigned int id);
        
        
        /// Creates a resource with given parameters, adds to this registry, and returns the created resource
        static Texture* const Create(const char* const filename, const char* const textureName, const Texture::Sampling textureSampling);
        
        
        
    private:
        
        //
        // Data
        //
        
        LinkedList<Texture> resourceList;      ///< List of managed resources
        static TextureRegistry* s_instance;    ///< Singeton instance of this registry
        
        
        //
        // Private Routines
        //
        
        /// Resource must be dynaically allocated, but it will be deleted by this registry later
        static void Add(Texture* newResource);
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Copy Ctor
        TextureRegistry(const TextureRegistry& other) = delete;
        
        /// No Copy Assignment
        TextureRegistry& operator=(const TextureRegistry& rhs) = delete;
        
        /// No Move Ctor
        TextureRegistry(TextureRegistry&& other) = delete;
        
        /// No Move Assignment
        TextureRegistry& operator=(TextureRegistry&& rhs) = delete;
    };
}
#endif /* TextureRegistry_hpp */
