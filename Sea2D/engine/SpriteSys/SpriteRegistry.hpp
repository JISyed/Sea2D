//
//  SpriteRegistry.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef SpriteRegistry_hpp
#define SpriteRegistry_hpp

#include "engine/AppSys/IRegistry.hpp"
#include "engine/DataTypes/LinkedList.hpp"
#include "Sprite.hpp"


namespace sea2d
{
    /// Serves as a container for holding all loaded Textures in the app
    class SpriteRegistry final : public IRegistry
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        SpriteRegistry();
        
        /// Destructor
        virtual ~SpriteRegistry();
        
        
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
        static Sprite* const Find(const char* const name);
        
        /// Find any resource by ID
        static Sprite* const Find(const unsigned int id);
        
        /// Resource must be dynaically allocated, but it will be deleted by this registry later
        static void Add(Sprite* newResource);
        
        
    private:
        
        //
        // Data
        //
        
        LinkedList<Sprite> resourceList;      ///< List of managed resources
        static SpriteRegistry* s_instance;    ///< Singeton instance of this registry
        
        
        //
        // Private Routines
        //
        
        /// Creates a resource with given parameters, adds to this registry, and returns the created resource
        static void Create(const char* const spriteCollectionFilename);
        
        /// Creates a resource with given parameters, adds to this registry, and returns the created resource
        static void Create(Texture* const textureForOneSprite);
        
        
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Copy Ctor
        SpriteRegistry(const SpriteRegistry& other) = delete;
        
        /// No Copy Assignment
        SpriteRegistry& operator=(const SpriteRegistry& rhs) = delete;
        
        /// No Move Ctor
        SpriteRegistry(SpriteRegistry&& other) = delete;
        
        /// No Move Assignment
        SpriteRegistry& operator=(SpriteRegistry&& rhs) = delete;
    };
}
#endif /* SpriteRegistry_hpp */
