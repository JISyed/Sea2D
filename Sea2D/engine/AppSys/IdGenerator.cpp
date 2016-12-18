//
//  IdGenerator.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/12/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "IdGenerator.hpp"

namespace sea2d
{
    /// Default Ctor
    IdGenerator::IdGenerator() :
        currentId(0u)
    {
    }
    
    /// Value Ctor
    IdGenerator::IdGenerator(const unsigned int startingValue) :
        currentId(startingValue)
    {
    }
    
    /// Copy Ctor
    IdGenerator::IdGenerator(const IdGenerator& other) :
        currentId(other.currentId)
    {
    }
    
    /// Copy Assignment Overload
    IdGenerator& IdGenerator::operator=(const IdGenerator& rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }
        
        this->currentId = rhs.currentId;
        
        return *this;
    }
    
    /// Dtor
    IdGenerator::~IdGenerator()
    {
    }
    
    /// Generate a new ID and return it. Will return a value between 1 and 4294967295 (man uint32)
    const unsigned int IdGenerator::MakeNewId()
    {
        return ++(this->currentId);
    }
    
}