//
//  FirstScene.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/7/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef FirstScene_hpp
#define FirstScene_hpp

#include "Scene.hpp"


namespace sea2d
{
    /// The first scene that will load in the game
    class FirstScene final : public Scene
    {
    public:
        
        //
        // Essentials
        //
        
        FirstScene() : Scene("FirstScene") {}       ///< Default Ctor
        virtual ~FirstScene() {}                    ///< Dtor
        
        
        //
        // Methods
        //
        
    protected:
        
        /// This is where you determine what Entites you want to load for this scene
        virtual void OnLoad() override;
        
        
    };
}
#endif /* FirstScene_hpp */
