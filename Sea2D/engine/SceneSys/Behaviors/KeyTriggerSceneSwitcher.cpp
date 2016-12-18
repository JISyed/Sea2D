//
//  KeyTriggerSceneSwitcher.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/23/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "KeyTriggerSceneSwitcher.hpp"
#include "engine/SceneSys/Scenes/SceneRegistry.hpp"
#include <iostream>

namespace sea2d
{
    //
    // Ctor / Dtor
    //
    
    /// Default Ctor
    KeyTriggerSceneSwitcher::KeyTriggerSceneSwitcher() :
        keyTrigger(Input::Key::Backspace),
        sceneToLoad(SceneRegistry::Find(1))
    {
    }
    
    // VIRTUAL
    /// Destructor
    KeyTriggerSceneSwitcher::~KeyTriggerSceneSwitcher()
    {
    }
    
    
    
    //
    // Additonal Methods
    //
    
    
    /// Change the key that will trigger the scene switching
    void KeyTriggerSceneSwitcher::ChangeTriggerKey(const Input::Key newTriggerKey)
    {
        this->keyTrigger = newTriggerKey;
    }
    
    /// Set the scene that will be switched to
    void KeyTriggerSceneSwitcher::SetScene(Scene* const newScene)
    {
        this->sceneToLoad = newScene;
    }
    
    
    
    
    //
    // Behavior Identity
    //
    
    // VIRTUAL OVERRIDE
    /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
    const BehaviorIdentity KeyTriggerSceneSwitcher::GetBehaviorIdentity() const
    {
        return BehaviorIdentity::KeyTriggerSceneSwitcher;
    }
    
    
    
    
    //
    // Events
    //
    
    // VIRTUAL OVERRIDE
    /// Called when the Behavior is added to an Entity (called after constructor)
    void KeyTriggerSceneSwitcher::OnStart()
    {
        
    }
    
    
    // VIRTUAL OVERRIDE
    /// Called every iteration of the game loop
    void KeyTriggerSceneSwitcher::OnUpdate()
    {
        if(Input::Keyboard::GetKeyUp(this->keyTrigger))
        {
            this->sceneToLoad->Load();
        }
    }
    
    
    // VIRTUAL OVERRIDE
    /// Called whene the Behavior is removed from an Entity (called before destructor)
    void KeyTriggerSceneSwitcher::OnDestroy()
    {
        // Intentionally empty
    }
}