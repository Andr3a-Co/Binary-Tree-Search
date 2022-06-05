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
    const BSTree& fBSTree;
    BTNStack fStack;
    
    void pushLeft( BTreeNode aNode )
    {
        while ( !aNode->empty() )                               
        {
            fStack.push( aNode );                               
            aNode = aNode->left;                                
        }
    }
    
public:
    
    using Iterator = BinarySearchTreeIterator<T>;
    
    BinarySearchTreeIterator( const BSTree& aBSTree ) :
        fBSTree(aBSTree)                                        
    {
        pushLeft( fBSTree.fRoot );                              
    }
    const T& operator*() const
    {
        return fStack.top()->key;                               
    }
    Iterator& operator++()
    {
        BTreeNode lNode = fStack.top()->right;                  
        
        fStack.pop();                                           
        
        pushLeft( lNode );                                      
        
        return *this;                                           
    }
    Iterator operator++(int)
    {
        Iterator old = *this;                                   
        
        ++(*this);                                              
        
        return old;                                             
    }
    bool operator==( const Iterator& aOtherIter ) const
    {
        return
            &fBSTree == &aOtherIter.fBSTree &&                  
            fStack.size() == aOtherIter.fStack.size();         
    }
    bool operator!=( const Iterator& aOtherIter ) const
    {
        return !(*this == aOtherIter);                          
    }
    
    Iterator begin() const
    {
        Iterator iter = *this;                                 
        
        iter.fStack = BTNStack();                              
        iter.pushLeft( iter.fRoot );                            
        
        return iter;                                            
    }
    
    Iterator end() const
    {
        Iterator iter = *this;                                  
        
        iter.fStack = BTNStack();                               
        
        return iter;                                            
    }
}; 
