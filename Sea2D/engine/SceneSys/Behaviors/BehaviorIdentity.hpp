//
//  BehaviorIdentity.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/1/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef BehaviorIdentity_h
#define BehaviorIdentity_h

namespace sea2d
{
    /// All Behaviors must have a unique identifier defined in this enum.
    /// The order these are declared is the order it is added to the entity (important for updating)
    enum class BehaviorIdentity : int
    {
        //
        // Custom Behaivor Names
        //
        
        ConstantRotation,
        KeyTriggerSceneSwitcher,
        KeyTriggeredMovement,
        
        
        
        //
        // Built-in (Do NOT modify)
        //
        
        CameraBehavior,
        SpriteRenderer,
        BitmapText,
        TexturedMeshRenderer,
        
        
    };
}

#endif /* BehaviorIdentity_h */
