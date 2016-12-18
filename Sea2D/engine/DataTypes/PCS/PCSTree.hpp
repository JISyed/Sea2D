//
//  PCSTree.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/30/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef PCSTree_hpp
#define PCSTree_hpp

#include "PCSNode.hpp"

namespace lge
{
    /// Data about a PCSTree
    struct PCSTreeInfo
    {
        int currNumNodes;
        int maxNumNodes;
        int currNumLevels;
        int maxNumLevels;
        
        PCSTreeInfo() :
            currNumNodes(0),
            maxNumNodes(0),
            currNumLevels(0),
            maxNumLevels(0)
        {
        }
    };
    
    
    
    
    
    /// Parent-Child-Sibling Tree
    class PCSTree
    {
    public:
        // constructor
        PCSTree();
        
        // destructor
        ~PCSTree();
        
        // get Root
        PCSNode* const getRoot() const;
        
        // insert
        void insert(PCSNode * const inNode, PCSNode * const parent);
        
        // remove
        void remove(PCSNode * const inNode);
        
        // get info
        const PCSTreeInfo& getInfo();
        //void printTree() const;
        const int getNumberOfNodes() const;
        
    private:
        
        void IncrementNode();
        void DecrementNode();
        void IncrementLevel();
        void DecrementLevel();
        
        // Itr pointer corrections for node removal
        void correctItrPointersWithNextSibling(PCSNode* oldNode);
        void correctItrPointersNoNextSibling(PCSNode* oldNode);
        PCSNode* getForwardAfterChildrenOf(PCSNode* target);
        
        // Used to unlink an entire local branch of the tree
        void unlinkBranchesFrom(PCSNode* headNode);
        
        // copy constructor 
        PCSTree(const PCSTree &in);
        
        // assignment operator
        PCSTree & operator = (const PCSTree &in);
        
        // Data
        PCSNode     *root;
        PCSTreeInfo mInfo;
        
    };
    
}

#endif /* PCSTree_hpp */
