#ifndef _BINARY_TREE_NODE_H__
#define _BINARY_TREE_NODE_H__

#include <string.h>


struct cmpStr {
    int compare(const char* thisKey, const char* otherKey) {
        return strcmp(thisKey,otherKey);
    }
};

struct cmpLong {
    int compare(long thisKey, long otherKey) {
        return thisKey - otherKey ;
    }
};

/**
 *   Base class for BinaryTreeNode
 */

template <typename K, class T, class _cmp>
class BinaryTreeNodeBase 
{
    protected:
    T* _value;
    _cmp* _comparator;
    K _key;

    public:
    BinaryTreeNodeBase<K,T,_cmp>* Left;
    BinaryTreeNodeBase<K,T,_cmp>* Right;

    BinaryTreeNodeBase(K key = 0, T* value = 0, _cmp* comp = new _cmp);
    ~BinaryTreeNodeBase();

    virtual K getKey();
    virtual void setKey(K key);
    virtual T* getValue();
    virtual void setValue(T* value);
    virtual BinaryTreeNodeBase<K,T,_cmp>* getLeft();
    virtual BinaryTreeNodeBase<K,T,_cmp>* getRight();
    virtual BinaryTreeNodeBase<K,T,_cmp>* setLeft(BinaryTreeNodeBase<K,T,_cmp>* lNode);
    virtual BinaryTreeNodeBase<K,T,_cmp>* setRight(BinaryTreeNodeBase<K,T,_cmp>* rNode);
    /// 
    /// Сравнивает текущий узел с данным.
    /// 
    /// Сравнение производится по полю Value.
    /// Метод возвращает 1, если значение текущего узла больше,
    /// чем переданного методу, -1, если меньше и 0, если они равны
    virtual int CompareTo(K other);
    
};



template <typename K, class T, class _cmp>
BinaryTreeNodeBase<K,T,_cmp>::BinaryTreeNodeBase(K key, T* value, _cmp* comp) {
    _value = value;
    _comparator = comp;
    _key = key;
    Left=0;
    Right=0;
}


/** 
    Сравнивает текущий узел с данным.

    Сравнение производится по полю Value.
    Метод возвращает 1, если значение текущего узла больше,
    чем переданного методу, -1, если меньше и 0, если они равны

*/
template <typename K, class T, class _cmp>
int BinaryTreeNodeBase<K,T,_cmp>::CompareTo(K other) {
    return _comparator->compare(_key,other);
      
}

template <typename K, class T, class _cmp>
T* BinaryTreeNodeBase<K,T,_cmp>::getValue() {
    return _value;
}

template <typename K, class T, class _cmp>
void BinaryTreeNodeBase<K,T,_cmp>::setValue(T* value) {
    if (_value != 0) delete _value;
    _value = value;
}

template <typename K, class T, class _cmp>
K BinaryTreeNodeBase<K,T,_cmp>::getKey() {
    return _key;
}

template <typename K, class T, class _cmp>
void BinaryTreeNodeBase<K,T,_cmp>::setKey(K key) {
    _key = key;
}


template <typename K, class T, class _cmp>
BinaryTreeNodeBase<K,T,_cmp>::~BinaryTreeNodeBase() {
    delete _comparator;
    delete _value;
    // delete _key;
}
template <typename K, class T, class _cmp>
BinaryTreeNodeBase<K,T,_cmp>* BinaryTreeNodeBase<K,T,_cmp>::getLeft() {
    return Left;
}
template <typename K, class T, class _cmp>
BinaryTreeNodeBase<K,T,_cmp>* BinaryTreeNodeBase<K,T,_cmp>::getRight() {
    return Right;
}
template <typename K, class T, class _cmp>
BinaryTreeNodeBase<K,T,_cmp>* BinaryTreeNodeBase<K,T,_cmp>::setLeft(BinaryTreeNodeBase<K,T,_cmp>* lNode) {
    return Left = lNode;
}
template <typename K, class T, class _cmp>
BinaryTreeNodeBase<K,T,_cmp>* BinaryTreeNodeBase<K,T,_cmp>::setRight(BinaryTreeNodeBase<K,T,_cmp>* rNode) {
    return Right = rNode;
}


/**
 *  For using with const char* key 
 */

template <class _K, class _T, class _C>
class BinaryTreeNode:  public BinaryTreeNodeBase<_K,_T,_C> {
    public:
    BinaryTreeNode(_K key =0, _T* value=0, _C* comp = new _C);
    // int CompareTo(_K other);
};


template <class _K, class _T, class _C>
BinaryTreeNode<_K,_T,_C>::BinaryTreeNode(_K key, _T* value, _C* comp):
    BinaryTreeNodeBase<_K,_T,_C>(key,value,comp){}


// #include "BinaryTreeNode.tpp"

#endif
