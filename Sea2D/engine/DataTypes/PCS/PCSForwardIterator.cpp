//
//  PCSForwardIterator.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/30/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "PCSForwardIterator.hpp"
#include <assert.h>
#include "PCSTree.hpp"

namespace lge
{
    PCSForwardIterator::PCSForwardIterator(const PCSTree& pcsTree) :
        root(pcsTree.getRoot()),
        current(nullptr)
    {
        if (this->root != nullptr)
        {
            this->current = this->root->getForward();
        }
    }
    
    PCSNode* const PCSForwardIterator::First()
    {
        this->current = this->root->getForward();
        return this->current;
    }
    
    PCSNode* const PCSForwardIterator::Next()
    {
        if (!this->IsDone())
        {
            this->current = this->current->getForward();
        }
        return this->current;
    }
    
    const bool PCSForwardIterator::IsDone() const
    {
        return this->current == nullptr;
    }
    
    PCSNode* const PCSForwardIterator::CurrentItem() const
    {
        return this->current;
    }
}