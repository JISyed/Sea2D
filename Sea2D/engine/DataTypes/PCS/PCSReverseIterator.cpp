//
//  PCSReverseIterator.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/30/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "PCSReverseIterator.hpp"
#include "PCSTree.hpp"

namespace lge
{
    PCSReverseIterator::PCSReverseIterator(const PCSTree& pcsTree) :
        root(pcsTree.getRoot()),
        current(nullptr)
    {
        if (this->root != nullptr)
        {
            this->current = this->root->getReverse();
        }
    }
    
    PCSNode* const PCSReverseIterator::First()
    {
        this->current = this->root->getReverse();
        return this->current;
    }
    
    PCSNode* const PCSReverseIterator::Next()
    {
        if (!this->IsDone())
        {
            this->current = this->current->getReverse();
        }
        return this->current;
    }
    
    const bool PCSReverseIterator::IsDone() const
    {
        return this->current == nullptr;
    }
    
    PCSNode* const PCSReverseIterator::CurrentItem() const
    {
        return this->current;
    }
}