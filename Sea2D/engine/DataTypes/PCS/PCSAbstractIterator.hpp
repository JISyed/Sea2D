//
//  PCSAbstractIterator.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/30/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef PCSAbstractIterator_h
#define PCSAbstractIterator_h

#include "PCSNode.hpp"

namespace lge
{
    /// An iterator for the Parent-Child-Sibling Tree
    class PCSAbstractIterator
    {
    public:
        
        PCSAbstractIterator() {}
        virtual ~PCSAbstractIterator() {}
        
        
        //
        // Contracts
        //
        
        virtual PCSNode* const First() = 0;
        virtual PCSNode* const Next() = 0;
        virtual const bool IsDone() const = 0;
        virtual PCSNode* const CurrentItem() const = 0;
    };
}

#endif /* PCSAbstractIterator_h */
