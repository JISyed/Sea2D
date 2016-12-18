//
//  PCSNode.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/30/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef PCSNode_hpp
#define PCSNode_hpp

//#define PCSNODE_NAME_SIZE (20)
//#define PCSNODE_VERSION 2.1

/// Another game engine separate from Sea2D
namespace lge
{
    /// Return codes for PCSNode
//    enum class PCSError : int
//    {
//        Success = 0,            ///< No error
//        FailPointerWasNull,
//        FailReturnNotInitailzed,
//    };
    
    
    /// Represents a node on a Parent-Child-Sibling Tree
    class PCSNode
    {
    public:
        /// constructor
        PCSNode();
        
        /// copy constructor
        //PCSNode(const PCSNode &in);
        
        // Specialize Constructor
        //PCSNode(const char * const inName);
        
        /// destructor
        virtual ~PCSNode();
        
        /// assignment operator
        //PCSNode &operator = (const PCSNode &in);
        
        // PCS Tree can access PCSNode
        friend class PCSTree;
        
        // getters
        PCSNode* getParent() const;
        PCSNode* getChild() const;
        PCSNode* getNextSibling() const;
        PCSNode* getPrevSibling() const;
        PCSNode* getForward() const;
        PCSNode* getReverse() const;
        
        // name
        //PCSError setName(const char * const inName);
        //PCSError getName(char * const outBuffer, unsigned int sizeOutBuffer) const;
        
        // print
        //void printNode() const;
        //void printChildren() const;
        //void printSiblings() const;
        
        // get number of children/siblings
        int getNumSiblings() const;
        int getNumChildren() const;
        
        
        
    private:
        PCSNode *parent;
        PCSNode *child;
        PCSNode *nextSibling;
        PCSNode *prevSibling;
        PCSNode *forward;
        PCSNode *reverse;
        
        //char     name[PCSNODE_NAME_SIZE];
        
        // accessors (can only be called by PCSTree)
        void setParent(PCSNode * const in);
        void setChild(PCSNode * const in);
        void setNextSibling(PCSNode * const in);
        void setPrevSibling(PCSNode * const in);
        void setForward(PCSNode * const in);
        void setReverse(PCSNode * const in);
        
    };
}

#endif /* PCSNode_hpp */
