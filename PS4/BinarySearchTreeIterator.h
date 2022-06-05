#pragma once
#include "BinarySearchTree.h"
#include <stack>
template<typename T>
class BinarySearchTreeIterator
{
private:

    using BSTree = BinarySearchTree<T>;
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    using BTNStack = std::stack<BTreeNode>;
    const BSTree& fBSTree; // binary search tree
    BTNStack fStack; // DFS traversal stack

    void pushLeft(BTreeNode aNode) {

        while (!aNode->empty()) {
            //pushleft push the node onto the traversal stack 
            //set aNode to its leftNode 
            fStack.push(aNode);
            aNode = aNode->left;                       
        }
    }

public:

    using Iterator = BinarySearchTreeIterator<T>;

    //constructor
    BinarySearchTreeIterator(const BSTree& aBSTree) : fBSTree (aBSTree) {}

    //dereference 
    const T& operator*() const {

        return *fBSTree.begin();

    }

    //prefix increment
    Iterator& operator++() {

        if (!fStack.empty()) {
           
        pushLeft(fBSTree.fRoot); // Go to the left most descendant
        fBSTree.fRoot->left = fStack.top(); // Left most node (leaf)
        fStack.pop(); // removes top from the stack
        
            if (fBSTree.fRoot->right->empty()) {
            
                fBSTree.fRoot->right = fStack.top(); // Left most node (leaf)
                fStack.pop(); // removes top from the stack
            }
            else {

                fBSTree.fRoot->right = fBSTree.fRoot->right; //go right   
                fStack.push(fBSTree.fRoot);

            }          
        

        }

        return *this;

    }

    // postfix increment
    Iterator operator++(int) {

        Iterator i = *this;

        ++(*this);

        return i;
    }

    // equivalence
    bool operator==(const Iterator& aOtherIter) const {

        return fBSTree.fRoot == aOtherIter.fBSTree.fRoot;
    }

    //not equal
    bool operator!=(const Iterator& aOtherIter) const {

        return !(*this == aOtherIter);
    }

    // first element forward
    Iterator begin() const {

        Iterator result = *this;

        result.fBSTree.fRoot; //first element     

        return result;
    }

    // last element forward
    Iterator end() const {

        return *this;
    }
};