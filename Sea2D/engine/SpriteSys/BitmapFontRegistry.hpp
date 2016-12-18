//
//  BitmapFontRegistry.hpp
//  Sea2D
//
//  Created by Jibran Syed on 6/8/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef BitmapFontRegistry_hpp
#define BitmapFontRegistry_hpp

#include "engine/AppSys/IRegistry.hpp"
#include "engine/DataTypes/LinkedList.hpp"
#include "BitmapFont.hpp"

namespace sea2d
{
    /// Serves as a container for holding all loaded Textures in the app
    class BitmapFontRegistry final : public IRegistry
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        BitmapFontRegistry();
        
        /// Destructor
        virtual ~BitmapFontRegistry();
        
        
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
        static BitmapFont* const Find(const char* const name);
        
        /// Find any resource by ID
        static BitmapFont* const Find(const unsigned int id);
        
        
        
        
    private:
        
        //
        // Data
        //
        
        LinkedList<BitmapFont> resourceList;      ///< List of managed resources
        static BitmapFontRegistry* s_instance;    ///< Singeton instance of this registry
        
        
        //
        // Private Routines
        //
        
        /// Creates a resource with given parameters, adds to this registry, and returns the created resource
        static void Create(const char* const fontDefinitionFilename);
        
        
        /// Resource must be dynaically allocated, but it will be deleted by this registry later
        static void Add(BitmapFont* newResource);
        
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Copy Ctor
        BitmapFontRegistry(const BitmapFontRegistry& other) = delete;
        
        /// No Copy Assignment
        BitmapFontRegistry& operator=(const BitmapFontRegistry& rhs) = delete;
        
        /// No Move Ctor
        BitmapFontRegistry(BitmapFontRegistry&& other) = delete;
        
        /// No Move Assignment
        BitmapFontRegistry& operator=(BitmapFontRegistry&& rhs) = delete;
    };
}

#endif /* BitmapFontRegistry_hpp */
