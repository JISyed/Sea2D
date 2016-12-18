//
//  PCSForwardIterator.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/30/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef PCSForwardIterator_hpp
#define PCSForwardIterator_hpp

#include "PCSAbstractIterator.hpp"

namespace lge
{
    // Forward declare
    class PCSTree;
    
    /// Iterator that moves forward in a Parent-Child-Sibling Tree
    class PCSForwardIterator : public PCSAbstractIterator
    {
    public:
        
        // Ctor
        PCSForwardIterator(const PCSTree& pcsTree);
        // Dtor
        virtual ~PCSForwardIterator() {}
        
        // Contracts
        virtual PCSNode* const First() override;
        virtual PCSNode* const Next() override;
        virtual const bool IsDone() const override;
        virtual PCSNode* const CurrentItem() const override;
        
    private:
        
        PCSNode* const root;
        PCSNode* current;
        
        PCSForwardIterator& operator=(const PCSForwardIterator& o) = delete;
    };
}

#endif /* PCSForwardIterator_hpp */
