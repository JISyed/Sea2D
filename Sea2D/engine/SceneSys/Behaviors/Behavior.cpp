//
//  Behavior.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/1/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Behavior.hpp"

namespace sea2d
{
    // Default Ctor
    Behavior::Behavior() :
        entity(nullptr)
    {
    }
    
    // VIRTUAL
    // Dtor
    Behavior::~Behavior()
    {
    }
    
    /// Get the Entity this Behavior is attached to (will never return nullptr)
    Entity* const Behavior::GetEntity()
    {
        return this->entity;
    }
    
}
