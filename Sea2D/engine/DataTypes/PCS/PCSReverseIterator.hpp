//
//  PCSReverseIterator.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/30/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef PCSReverseIterator_hpp
#define PCSReverseIterator_hpp

#include "PCSAbstractIterator.hpp"

namespace lge
{
    // Forward declare
    class PCSTree;
    
    /// Iterator that moves backwards in a Parent-Child-Sibling Tree
    class PCSReverseIterator : public PCSAbstractIterator
    {
    public:
        
        // Ctor
        PCSReverseIterator(const PCSTree& pcsTree);
        // Dtor
        virtual ~PCSReverseIterator() {}
        
        // Contracts
        virtual PCSNode* const First() override;
        virtual PCSNode* const Next() override;
        virtual const bool IsDone() const override;
        virtual PCSNode* const CurrentItem() const override;
        
    private:
        
        PCSNode* const root;
        PCSNode* current;
        
        PCSReverseIterator& operator=(const PCSReverseIterator& o) = delete;
    };
}

#endif /* PCSReverseIterator_hpp */
