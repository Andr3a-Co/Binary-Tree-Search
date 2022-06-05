#pragma once
#include "BinaryTreeNode.h"
#include <stdexcept>
// Problem 3 requirement
template<typename T>
class BinarySearchTreeIterator;
template<typename T>
class BinarySearchTree
{
private:
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    BTreeNode fRoot;

public:
    BinarySearchTree() : fRoot(&BNode::NIL) {}


    ~BinarySearchTree() {

        fRoot->~BinaryTreeNode();
    }
    bool empty() const {

        return fRoot->empty();
    }
    size_t height() const {

        return fRoot->height();        
    }

    bool insert(const T& aKey) {        


        if (empty()) {
            fRoot = new BNode(aKey);
            return true;
        }
        else {
            return fRoot->insert(aKey);

        }

    }
    bool remove(const T& aKey) {

        if (fRoot->leaf()) {
            fRoot = &BNode::NIL;
            return true;
              
        }
        return fRoot->remove(aKey, &BNode::NIL);
    }

    // Problem 3 methods

    using Iterator = BinarySearchTreeIterator<T>;
    // Allow iterator to access private member variables
    friend class BinarySearchTreeIterator<T>;
    Iterator begin() const {

        return Iterator (*this);
       
    }
    Iterator end() const {

        return begin().end();
    }
};