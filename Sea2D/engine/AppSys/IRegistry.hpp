//
//  ResourceRegistry.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/24/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef IRegistry_hpp
#define IRegistry_hpp

namespace sea2d
{
    /// Interface for Registries (container objects that hold resources)
    class IRegistry
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        IRegistry() {}
        
        /// Destructor
        virtual ~IRegistry() {}
        
        
        //
        // Abstract Methods
        //
        
        /// Decide what resources to load at the start of the App
        virtual void Load() = 0;
        
        /// Release any resources remaining that are managed by this registry
        virtual void Unload() = 0;
        

    };
}
#endif /* IRegistry_hpp */
