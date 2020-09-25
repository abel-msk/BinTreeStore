#ifndef _BINARY_TREE_H__
#define _BINARY_TREE_H__
#include "BinaryTreeNode.h"
// #include "BinaryTreeAction.h"

template<class K,class T, class C>
struct findWithParentResult {
    BinaryTreeNode<K,T,C>* current;
    BinaryTreeNode<K,T,C>* parent;
};

template <class K, class A>
class BinaryTreeAction {
    public:
    virtual void run(K key, A* cl) {};
};

// template<class K, class T>
// class _removeAction: public BinaryTreeAction<K, T> 
// {
//     public:
//     void run(K key, T* _cl) {
//         delete _cl;
//     };
// };

/**
 * 
 *    Base BinryTree class
 */

template<class K, class T, class C = cmpStr>
class BinaryTreeBase {  

    private:
    BinaryTreeNode<K,T,C>* _head;
    BinaryTreeNode<K,T,C>* _emptyEL;
    int _count;
    findWithParentResult<K,T,C>*  _foundCwP;

    private:
    BinaryTreeNode<K,T,C>* createNode(K key,T* value);
    void addTo(BinaryTreeNode<K,T,C>* node, K key, T* value);  
    void preOrderTraversal(BinaryTreeAction<K,T>* action, BinaryTreeNode<K,T,C>* node);
    void postOrderTraversal(BinaryTreeAction<K,T>* action, BinaryTreeNode<K,T,C>* node);
    void inOrderTraversal(BinaryTreeAction<K,T>* action, BinaryTreeNode<K,T,C>* node);
    findWithParentResult<K,T,C>* findWithParent(K key);
    void clearByNode(BinaryTreeNode<K,T,C>* node);

    public:
    BinaryTreeBase();
    ~BinaryTreeBase();
    virtual void add(K key, T* value);
    virtual T* getByKey(K key);
    
    virtual bool contains(K key);
    virtual bool remove(K key);

    virtual void preOrderTraversal(BinaryTreeAction<K,T>* action);
    virtual void postOrderTraversal(BinaryTreeAction<K,T>* action);
    virtual void inOrderTraversal(BinaryTreeAction<K,T>* action);

    virtual void clear();
    virtual int size();
};


/**
    Specializtion for derived clas BinTree
*/
template<class _K, class _T, class _C>
class BinaryTree : public BinaryTreeBase<_K,_T,_C> {
      public:
      BinaryTree();
};

template<class _K, class _T, class _C>
BinaryTree<_K,_T,_C>::BinaryTree():BinaryTreeBase<_K,_T,_C>() {}

/**
    Partail specialization classes  for Bintree class  for use with const char* type key
*/
template<class _T>
class BinaryTree<const char*,_T,cmpStr>: public BinaryTreeBase<const char*,_T,cmpStr> {
      public:
      BinaryTree();
};

template<class _T>
BinaryTree<const char*,_T,cmpStr>::BinaryTree():BinaryTreeBase<const char*,_T,cmpStr>(){}


/**
    Partail specialization classes  for Bintree class  for use with long type key
*/
template<class _T>
class BinaryTree<long,_T,cmpLong>: public BinaryTreeBase<long,_T,cmpLong> {
      public:
      BinaryTree();
};

template<class _T>
BinaryTree<long,_T,cmpLong>::BinaryTree():BinaryTreeBase<long,_T,cmpLong>(){}


#include "BinaryTree.tpp"

#endif