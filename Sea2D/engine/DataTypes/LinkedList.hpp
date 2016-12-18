//
//  LinkedList.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/24/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef LinkedList_hpp
#define LinkedList_hpp

#include "engine/AppSys/DebugGuarantee.hpp"

namespace sea2d
{
    /// A generic list that holds objects internally as pointers using aggregation (not composition).
    /// The template paramater should not be a pointer!
    template<typename T> class LinkedList
    {
    private:
        
        //
        // Private Types
        //
        
        /// A list node that can only hold objects of type T.
        /// Holds the object with aggregation, not composition.
        class Node
        {
        public:
            
            /// No default ctor
            Node() = delete;
            
            /// Object Ctor
            Node(T* const newObject, const int newId = 0)  :
                nextNode(nullptr),
                object(newObject),
                objectId(newId),
                prevNode(nullptr)
            {}
            
            /// Object and Links Ctor
            Node(Node* const newNext, Node* const newPrev, T* const newObject, const int newId = 0) :
                nextNode(newNext),
                object(newObject),
                objectId(newId),
                prevNode(newPrev)
            {}
            
            /// Dtor
            ~Node() {}
            
            /// Get the node "right" of this node
            Node* const GetNextNode() const
            {
                return this->nextNode;
            }
            
            /// Get the node "left" of this node
            Node* const GetPrevNode() const
            {
                return this->prevNode;
            }
            
            /// Get the object held in this node
            T* const GetDataObject() const
            {
                return this->object;
            }
            
            /// Get the id assigned to the object of this node
            const int GetDataObjectId() const
            {
                return this->objectId;
            }
            
            /// Set the "right" node of this node
            void SetNextNode(Node* const newNext)
            {
                this->nextNode = newNext;
            }
            
            /// Set the "left" node of this node
            void SetPrevNode(Node* const newPrev)
            {
                this->prevNode = newPrev;
            }
            
            /// Set the object to be held in this node
            void SetObject(T* const newObject)
            {
                this->object = newObject;
                this->objectId = 0u;
            }
            
            
        private:
            
            Node* nextNode;         ///< Right neighbor
            int objectId;           ///< Node's id
            T* object;              ///< Object stored in the node
            Node* prevNode;         ///< Left neighbor
        };
        
        
        
    public:
        
        //
        // Public Types
        //
        
        /// Forward Iterator used to access element of LinkedList
        class Iterator
        {
        public:
            
            /// Ctor
            /// @remark  Only LinkedList should construct a LinkedList<T>::Iterator
            Iterator(Node* headNode) :
                currentNode(headNode),
                firstNode(headNode)
            {
            }
            
            /// Copy ctor
            Iterator(const Iterator& other) :
                currentNode(other.currentNode),
                firstNode(other.firstNode)
            {
            }
            
            /// Dtor
            ~Iterator() {}
            
            
            /// Move to the first node and return it
            T* const First()
            {
                this->currentNode = this->firstNode;
                return this->firstNode->GetDataObject();
            }
            
            /// Go to the next node and return it
            T* const Next()
            {
                if(this->currentNode == nullptr)
                {
                    return nullptr;
                }
                
                this->currentNode = this->currentNode->GetNextNode();
                if (this->currentNode == nullptr)
                {
                    return nullptr;
                }
                
                return this->currentNode->GetDataObject();
            }
            
            /// Use this to check if looping through iteration is done.
            /// Stop iterating if this returns true.
            const bool IsDone() const
            {
                return this->currentNode == nullptr;
            }
            
            /// Get the current item pointed by this iterator
            T* const CurrentItem() const
            {
                if(this->currentNode == nullptr)
                {
                    return nullptr;
                }
                
                return this->currentNode->GetDataObject();
            }
            
            
            
        private:
            
            Node* currentNode;      ///< The current node this iterator is pointing at
            Node* const firstNode;  ///< The first node of the list of this iterator
            
            
            
            /// No default ctor
            Iterator() = delete;
            
            /// No copy assignment
            Iterator& operator=(const Iterator& other) = delete;
        };
        
        
        
    public:
        
        //
        // Ctor / Dtor
        //
        
        /// Default Ctor
        LinkedList() :
            head(nullptr),
            numElements(0)
        {
        }
        
        /// Dtor
        ~LinkedList()
        {
            if(this->numElements > 0)
            {
                this->Clear();
            }
        }
        
        
        
        
        
        //
        // Methods
        //
        
        /// Add a new object to the front of the list
        void AddFront(T* const newObject, const int newId = 0)
        {
            //assert(newObject != nullptr);
            LinkedList<T>::Node* newNode = new LinkedList<T>::Node(newObject, newId);
            
            // If there is no head
            if (this->head == nullptr)
            {
                guarantee_that(this->numElements == 0, "LinkedList: no head implies no elements");
                
                this->head = newNode;
            }
            // If there is a head
            else
            {
                guarantee_that(this->numElements != 0, "LinkedList: having a head implies there is at least 1 element, but is 0");
                
                this->head->SetPrevNode(newNode);
                newNode->SetNextNode(this->head);
                
                this->head = newNode;
            }
            
            // Increment
            this->numElements++;
        }
        
        /// Add a new object to the back of the list
        void AddBack(T* const newObject, const int newId = 0)
        {
            guarantee_that(newObject != nullptr, "LinkedList: new object being added should not be null!");
            LinkedList<T>::Node* newNode = new LinkedList<T>::Node(newObject, newId);
            
            // If there is no head
            if (this->head == nullptr)
            {
                guarantee_that(this->numElements == 0, "LinkedList: no head implies no elements");
                
                this->head = newNode;
            }
            // If there is a head
            else
            {
                guarantee_that(this->numElements != 0, "LinkedList: having a head implies there is at least 1 element, but is 0");
                
                // Get the last node
                LinkedList<T>::Node* preItr = this->head;
                LinkedList<T>::Node* postItr = this->head->GetNextNode();
                while(postItr != nullptr)
                {
                    preItr = postItr;
                    postItr = postItr->GetNextNode();
                }
                
                // Add newNode after preItr
                this->AddAfter(newNode, preItr);
            }
            
            // Increment
            this->numElements++;
        }
        
        /// Add a new object based on the ordering of the object's IDs (object must have GetId() or compiler will complain)
        /// WARNNIG: Assumes that the list is already sorted!! Don't call this if it isn't
        void AddSorted(T* const newObject, const int newId)
        {
            guarantee_that(newObject != nullptr, "LinkedList: new object being added should not be null!");
            LinkedList<T>::Node* newNode = new LinkedList<T>::Node(newObject, newId);
            
            // Search for the node that newNode should be added before
            LinkedList<T>::Node* currNode = this->head;
            while (currNode != nullptr)
            {
                if (currNode->GetDataObjectId() > newNode->GetDataObjectId())
                {
                    break;
                }
                
                currNode = currNode->GetNextNode();
            }
            
            
            // If there was a node to add before newNode
            if (currNode != nullptr)
            {
                // Add the new node before the current node
                this->AddBefore(newNode, currNode);
            }
            // If the newNode is bigger then everyone
            else
            {
                // Add the new node after the current node
                this->AddAfter(newNode, currNode);
            }
            
            
            // Increment
            this->numElements++;
        }
        
        
        /// Get the number of elements in this list
        const int GetNumberOfElements() const
        {
            return this->numElements;
        }
        
        
        /// Get an iterator to this list
        LinkedList<T>::Iterator GetIterator() const
        {
            return LinkedList<T>::Iterator(this->head);
        }
        
        
        
        /// Remove an object from the list given a pointer to that object
        /// Does NOT delete
        bool RemoveByObject(T* const toBeRemoved)
        {
            // Search the list for an node that holds the same reference
            LinkedList<T>::Node* currNode = this->head;
            while (currNode != nullptr)
            {
                if (currNode->GetDataObject() == toBeRemoved)
                {
                    // Found the node
                    break;
                }
                
                currNode = currNode->GetNextNode();
            }
            
            // If the node was found
            if (currNode != nullptr)
            {
                this->RemoveNode(currNode);
                this->numElements--;
                return true;
            }
            
            // If the node wasn't found
            return false;
        }
        
        /// Remove an object from the list given
        /// Does NOT delete
        T* const RemoveById(const int idToRemove)
        {
            // Search the list for an node that holds the same ID
            LinkedList<T>::Node* currNode = this->head;
            while (currNode != nullptr)
            {
                if (currNode->GetDataObjectId() == idToRemove)
                {
                    // Found the node
                    break;
                }
                
                currNode = currNode->GetNextNode();
            }
            
            // If the node was found
            if (currNode != nullptr)
            {
                T* const removedObject = currNode->GetDataObject();
                this->RemoveNode(currNode);
                this->numElements--;
                guarantee_that(removedObject != nullptr, "LinkedList: Removed object should not be null!");
                return removedObject;
            }
            
            // If the node wasn't found
            return nullptr;
        }
        
        /// Remove the first element in the list
        T* const RemoveFront()
        {
            // If there is no head
            if (this->head == nullptr)
            {
                //assert(this->numElements == 0);
                return nullptr;
            }
            
            // If there is a head
            T* const removedObject = this->head->GetDataObject();
            this->RemoveNode(this->head);
            this->numElements--;
            guarantee_that(removedObject != nullptr, "LinkedList: Removed object should not be null!");
            return removedObject;
        }
        
        
        /// Removes every node from the list
        /// @remark  Contained objects are NOT deleted
        void Clear()
        {
            while (this->head != nullptr)
            {
                this->RemoveNode(this->head);
                this->numElements--;
            }
        }
        
        
        
        
        /// Find the object by its ID. Does not remove anything
        T* const FindById(const int queriedId) const
        {
            // Search the list for an node that holds the same ID
            LinkedList<T>::Node* currNode = this->head;
            while (currNode != nullptr)
            {
                if (currNode->GetDataObjectId() == queriedId)
                {
                    // Found the node
                    break;
                }
                
                currNode = currNode->GetNextNode();
            }
            
            // If the node was found
            if (currNode != nullptr)
            {
                return currNode->GetDataObject();
            }
            
            // If the node wasn't found
            return nullptr;
        }
        
        
        
        
    private:
        
        //
        // Data
        //
        
        LinkedList<T>::Node* head;      ///< First node of the list
        int numElements;                ///< Number of nodes in the list
        
        
        
        
        
        
        
        
        //
        // Private Routines
        //
        
        // Does not create a new node or increment numElement
        void AddAfter(LinkedList<T>::Node* newNode, LinkedList<T>::Node* nodeBeforeNewNode)
        {
            guarantee_that(newNode != nullptr, "LinkedList: Adding new node that is null!");
            
            if(nodeBeforeNewNode == nullptr)
            {
                // Add to back...
                
                // If there is no head
                if (this->head == nullptr)
                {
                    guarantee_that(this->numElements == 0, "LinkedList: no head implies no elements");
                    
                    this->head = newNode;
                }
                // If there is a head
                else
                {
                    guarantee_that(this->numElements != 0, "LinkedList: having a head implies there is at least 1 element, but is 0");
                    
                    // Get the last node
                    LinkedList<T>::Node* preItr = this->head;
                    LinkedList<T>::Node* postItr = this->head->GetNextNode();
                    while(postItr != nullptr)
                    {
                        preItr = postItr;
                        postItr = postItr->GetNextNode();
                    }
                    
                    // Add newNode after preItr
                    this->AddAfter(newNode, preItr);
                }

            }
            else
            {
                // If there is nothing after the "nodeBeforeNewNode"
                if (nodeBeforeNewNode->GetNextNode() == nullptr)
                {
                    nodeBeforeNewNode->SetNextNode(newNode);
                    newNode->SetPrevNode(nodeBeforeNewNode);
                    
                    // Just in case
                    newNode->SetNextNode(nullptr);
                }
                // If there is something after the "nodeBeforeNewNode"
                else
                {
                    newNode->SetNextNode(nodeBeforeNewNode->GetNextNode());
                    nodeBeforeNewNode->GetNextNode()->SetPrevNode(newNode);
                    newNode->SetPrevNode(nodeBeforeNewNode);
                    nodeBeforeNewNode->SetNextNode(newNode);
                }
            }
        }
        
        
        // Does not create a new node or increment numElement
        void AddBefore(LinkedList<T>::Node* newNode, LinkedList<T>::Node* nodeAfterNewNode)
        {
            //assert(nodeAfterNewNode != nullptr);
            //assert(newNode != nullptr);
            
            if(nodeAfterNewNode == nullptr)
            {
                // Add to front...
                
                // If there is no head
                if (this->head == nullptr)
                {
                    guarantee_that(this->numElements == 0, "LinkedList: no head implies no elements");
                    
                    this->head = newNode;
                }
                // If there is a head
                else
                {
                    guarantee_that(this->numElements != 0, "LinkedList: having a head implies there is at least 1 element, but is 0");
                    
                    this->head->SetPrevNode(newNode);
                    newNode->SetNextNode(this->head);
                    
                    this->head = newNode;
                }
            }
            else
            {
                // If there is nothing before the "nodeAfterNewNode"
                if (nodeAfterNewNode->GetPrevNode() == nullptr)
                {
                    guarantee_that(nodeAfterNewNode == this->head, "LinkedList: nodeAfterNewNode must be the head");
                    guarantee_that(this->numElements != 0, "LinkedList: having a head (nodeAfterNewNode) implies there is at least 1 element, but is 0");
                    
                    this->head->SetPrevNode(newNode);
                    newNode->SetNextNode(this->head);
                    
                    this->head = newNode;
                }
                // There is something before the new node
                else
                {
                    newNode->SetNextNode(nodeAfterNewNode);
                    newNode->SetPrevNode(nodeAfterNewNode->GetPrevNode());
                    
                    nodeAfterNewNode->GetPrevNode()->SetNextNode(newNode);
                    nodeAfterNewNode->SetPrevNode(newNode);
                }
            }
        }
        
        // Does not decrement numElement,
        // but will nullify the head pointer, and delete the old node
        void RemoveNode(LinkedList<T>::Node* oldNode)
        {
            guarantee_that(oldNode != nullptr, "LinkedList: Removing a node, but it's null");
            
            // If solo node
            if (oldNode->GetNextNode() == nullptr && oldNode->GetPrevNode() == nullptr)
            {
                // Nullify the head pointer
                this->head = nullptr;
            }
            // If first node
            else if (oldNode->GetNextNode() != nullptr && oldNode->GetPrevNode() == nullptr)
            {
                // oldNode should be the head here!
                guarantee_that(this->head == oldNode, "LinkedList::RemoveNode: oldNode should be the head if first node");
                
                this->head = this->head->GetNextNode();
                this->head->SetPrevNode(nullptr);
                
                oldNode->SetNextNode(nullptr);
            }
            // If last node
            else if (oldNode->GetNextNode() == nullptr && oldNode->GetPrevNode() != nullptr)
            {
                oldNode->GetPrevNode()->SetNextNode(nullptr);
                oldNode->SetPrevNode(nullptr);
            }
            // If a middle node
            else if (oldNode->GetNextNode() != nullptr && oldNode->GetPrevNode() != nullptr)
            {
                oldNode->GetPrevNode()->SetNextNode(oldNode->GetNextNode());
                oldNode->GetNextNode()->SetPrevNode(oldNode->GetPrevNode());
                
                oldNode->SetNextNode(nullptr);
                oldNode->SetPrevNode(nullptr);
            }
            // Shouldn't really be here
            else
            {
                guarantee_that(false, "LinkedList::RemoveNode: Unhandled case for node deletion!");
            }
            
            // If you're here, the node was unlinked. Now delete the node.
            // The object in the node should never be deleted
            delete oldNode;
        }
        

        
        
        //
        // Deleted Methods
        //
        
        /// No copy ctor
        LinkedList(const LinkedList& other) = delete;
        
        /// No copy assignment
        LinkedList& operator=(const LinkedList& other) = delete;
    };
}

#endif /* LinkedList_hpp */
