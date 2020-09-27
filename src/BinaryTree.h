#ifndef _BINARY_TREE_H__
#define _BINARY_TREE_H__
#include "BinaryTreeNode.h"

template<class K,class T, class C>
struct findWithParentResult {
    BinaryTreeNode<K,T,C>* current;
    BinaryTreeNode<K,T,C>* parent;
};

template <class K, class T>
class BinaryTreeAction {
    public:
    virtual void run(K key, T cl) {};
};


/**
 * 
 *    Base BinryTree class
 */

template<class K, class T, class C>
class BinaryTreeBase {  

    protected:
    BinaryTreeNode<K,T,C>* _head;
    int _count;
    findWithParentResult<K,T,C>*  _foundCwP;

    protected:
    BinaryTreeNode<K,T,C>* createNode(K key,T value);
    void addTo(BinaryTreeNode<K,T,C>* node, K key, T value);  
    void preOrderTraversal(BinaryTreeAction<K,T>* action, BinaryTreeNode<K,T,C>* node);
    void postOrderTraversal(BinaryTreeAction<K,T>* action, BinaryTreeNode<K,T,C>* node);
    void inOrderTraversal(BinaryTreeAction<K,T>* action, BinaryTreeNode<K,T,C>* node);
    findWithParentResult<K,T,C>* findWithParent(K key);
    void clearByNode(BinaryTreeNode<K,T,C>* node);

    public:
    BinaryTreeBase();
    ~BinaryTreeBase();
    virtual void add(K key, T value);
    // virtual T* getByKey(K key);

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
    BinaryTree():BinaryTreeBase<_K,_T,_C>() {}
};


/**
    Partail specialization classes  for Bintree class  for use with const char* type key
*/
template<class _K, class _T, class _C>
class BinaryTree<_K,_T*,_C>: public BinaryTreeBase<_K,_T*,_C> {
    public:
    BinaryTree():BinaryTreeBase<_K,_T*,_C>(){}

    _T* getByKey(_K key) {
        BinaryTreeBase<_K,_T*,_C>::_foundCwP = this->findWithParent(key);
        if ((BinaryTreeBase<_K,_T*,_C>::_foundCwP != 0)  &&
          (BinaryTreeBase<_K,_T*,_C>::_foundCwP->current != 0)) {
            return BinaryTreeBase<_K,_T*,_C>::_foundCwP->current->getValue();
        }
        return  nullptr;
    }      
};


template<class _K, class _T, class _C>
class BinaryTree<_K*,_T*,_C>: public BinaryTreeBase<_K*,_T*,_C> {
    public:
    BinaryTree():BinaryTreeBase<_K*,_T*,_C>(){}

    _T* getByKey(_K* key) {
        BinaryTreeBase<_K*,_T*,_C>::_foundCwP = this->findWithParent(key);
        if ((BinaryTreeBase<_K*,_T*,_C>::_foundCwP != 0)  &&
          (BinaryTreeBase<_K*,_T*,_C>::_foundCwP->current != 0)) {
            return BinaryTreeBase<_K*,_T*,_C>::_foundCwP->current->getValue();
        }
        return  nullptr;
    }     
};


#include "BinaryTree.tpp"

#endif