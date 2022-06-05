#pragma once
#include <stdexcept>
#include <algorithm>
template<typename T>
struct BinaryTreeNode
{
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;

    T key;
    BTreeNode left;
    BTreeNode right;

    static BNode NIL;

    const T& findMax() const
    {
        if (empty())
        {
            throw std::domain_error("Empty tree encountered.");
        }

        return right->empty() ? key : right->findMax();
    }
    const T& findMin() const
    {
        if (empty())
        {
            throw std::domain_error("Empty tree encountered.");
        }

        return left->empty() ? key : left->findMin();
    }
    bool remove(const T& aKey, BTreeNode aParent)
    {
        BTreeNode x = this;
        BTreeNode y = aParent;
        while (!x->empty())
        {
            if (aKey == x->key)
            {
                break;
            }
            y = x;                                      // new parent

            x = aKey < x->key ? x->left : x->right;
        }
        if (x->empty())
        {
            return false;                               // delete failed
        }

        if (!x->left->empty())
        {
            const T& lKey = x->left->findMax();         // find max to left
            x->key = lKey;
            x->left->remove(lKey, x);
        }
        else
        {
            if (!x->right->empty())
            {
                const T& lKey = x->right->findMin();    // find min to right
                x->key = lKey;
                x->right->remove(lKey, x);
            }
            else
            {
                if (y != &NIL)                        // y can be NIL
                {
                    if (y->left == x)
                    {
                        y->left = &NIL;
                    }
                    else
                    {
                        y->right = &NIL;
                    }
                }

                delete x;                               // free deleted node
            }
        }
        return true;
    }

    // PS4 starts here

    BinaryTreeNode() : key(T()), left(&NIL), right (&NIL) {}
    BinaryTreeNode(const T& aKey) : key(aKey), left(&NIL), right(&NIL) { }
    BinaryTreeNode(T&& aKey) : key(std::move(aKey)), left(&NIL), right(&NIL) {}

    ~BinaryTreeNode() {

        if (empty()) {

            if (!left->empty()) {

                delete left;
            }

            if (!right->empty()) {

                delete right;
            }
                       
        throw std::domain_error("Empty Binary Tree found.");
            
        }
    }


    bool empty() const {

        return this == &NIL;
    }

    bool leaf() const {

        if (empty()) {

            return false;
        }
        else if (left == &NIL && right == &NIL) {

            return true;
        }
        return false;

    }
    size_t height() const {

        size_t h = 0;

        //empty tree has no height 
        if (empty())
        {
            throw std::domain_error("Empty Binary Tree found.");
            
        }
        //if a subtree of a given BTree node is leaf Height = 0;
        else if (leaf()) {

            return h;
        }
        else {

            size_t leftHeigth = 0;
            size_t rightHeigth = 0;

            if (!left->empty()){
                leftHeigth = left->height();
            }
            if (!right->empty()) {
                rightHeigth = right->height();
            }

            h = max(leftHeigth, rightHeigth) + 1;

        }
       
        return h;
    }

    bool insert(const T& aKey) {

        BNode* x = this;
        BNode* y = &NIL;

        if (x->empty()) {
            return false;
        }

        while (!x->empty()) {

            y = x;

            if (aKey == x->key) {

                return false;
            }

            x = aKey < x->key ? x->left : x->right;
        }

        BNode* z = new BNode(aKey);

        if (y->empty()) {

            return false;
        }
        else {

            if (aKey < y->key) {

                y->left = z;
            }
            else {

                y->right = z;
            }
        }

        return true;
    }

    
};
template<typename T>
BinaryTreeNode<T> BinaryTreeNode<T>::NIL;