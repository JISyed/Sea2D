//
//  KeyTriggerSceneSwitcher.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/23/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef KeyTriggerSceneSwitcher_hpp
#define KeyTriggerSceneSwitcher_hpp

#include "Behavior.hpp"
#include "engine/InputSys/Keyboard.hpp"
#include "engine/SceneSys/Scenes/Scene.hpp"

namespace sea2d
{
    /// Behavior that constantly rotates an Entity
    class KeyTriggerSceneSwitcher : public Behavior
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        KeyTriggerSceneSwitcher();
        
        /// Destructor
        virtual ~KeyTriggerSceneSwitcher();
        
        /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
        virtual const BehaviorIdentity GetBehaviorIdentity() const override;
        
        
        
        //
        // Additonal Methods
        //
        
        /// Change the key that will trigger the scene switching
        void ChangeTriggerKey(const Input::Key newTriggerKey);
        
        /// Set the scene that will be switched to
        void SetScene(Scene* const newScene);
        
        
        
    protected:
        
        
        //
        // Events
        //
        
        /// Called when the Behavior is added to an Entity (called after constructor)
        virtual void OnStart() override;
        
        /// Called every iteration of the game loop
        virtual void OnUpdate() override;
        
        /// Called whene the Behavior is removed from an Entity (called before destructor)
        virtual void OnDestroy() override;
        
        
    private:
        
        //
        // Data
        //
        
        Input::Key keyTrigger;
        Scene* sceneToLoad;
        
        
    };
}
#endif /* KeyTriggerSceneSwitcher_hpp */
