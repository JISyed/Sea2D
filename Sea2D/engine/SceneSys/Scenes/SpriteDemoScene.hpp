//
//  SpriteDemoScene.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/23/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef SpriteDemoScene_hpp
#define SpriteDemoScene_hpp

#include "Scene.hpp"


namespace sea2d
{
    /// The a scene demoing the sprite system
    class SpriteDemoScene final : public Scene
    {
    public:
        
        //
        // Essentials
        //
        
        SpriteDemoScene() : Scene("SpriteDemoScene") {}       ///< Default Ctor
        virtual ~SpriteDemoScene() {}                    ///< Dtor
        
        
        //
        // Methods
        //
        
    protected:
        
        /// This is where you determine what Entites you want to load for this scene
        virtual void OnLoad() override;
        
        
    };
}
#endif /* SpriteDemoScene_hpp */
