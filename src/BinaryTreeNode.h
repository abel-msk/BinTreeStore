#ifndef _BINARYTREE_NODE_H__
#define _BINARYTREE_NODE_H__

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
    T _value;
    _cmp* _comparator;
    K _key;

    public:
    BinaryTreeNodeBase<K,T,_cmp>* Left;
    BinaryTreeNodeBase<K,T,_cmp>* Right;

    BinaryTreeNodeBase(K key, T value);
    
    ~BinaryTreeNodeBase();

    virtual K getKey();
    virtual void setKey(K key);
    virtual T getValue();
    virtual void setValue(T value);
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
BinaryTreeNodeBase<K,T,_cmp>::BinaryTreeNodeBase(K key, T value) {
    _value = value;
    _comparator = new _cmp();
    _key = key;
    Left=NULL;
    Right=NULL;
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
T BinaryTreeNodeBase<K,T,_cmp>::getValue() {
    return _value;
}

template <typename K, class T, class _cmp>
void BinaryTreeNodeBase<K,T,_cmp>::setValue(T value) {
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


/***************************************************************************************
 * 
 * 
 *  partail specialization
 * 
 */

template <class K, class T, class C>
class BinaryTreeNode:  public BinaryTreeNodeBase<K,T,C> {
    public:
    BinaryTreeNode(K key, T value):BinaryTreeNodeBase<K,T,C>(key,value){}

    //    BinaryTreeNodeBase<K,T,C>::_comparator->compare(
    //        BinaryTreeNodeBase<K,T,C>::_key,
    //        other);

    // }
    // int CompareTo(K other);
    // friend BinaryTreeNodeBase<K,T,C>;
};


/**
 *  
 */

template <class K, class T, class C>
class BinaryTreeNode<K*,T*,C>:  public BinaryTreeNodeBase<K*,T*,C> {

    public:
    BinaryTreeNode(K* key, T* value):BinaryTreeNodeBase<K*,T*,C>(key,value){
    }
    ~BinaryTreeNode() {
        delete BinaryTreeNodeBase<K*,T*,C>::_key;
        delete BinaryTreeNodeBase<K*,T*,C>::_value;
    }
    int CompareTo(K* other) {
       return BinaryTreeNodeBase<K*,T*,C>::_comparator->compare(
           BinaryTreeNodeBase<K*,T*,C>::_key,
           other);
    }
    // friend BinaryTreeNodeBase<K*,T*,C>;
};


template <class K, class T, class C>
class BinaryTreeNode<K,T*,C>:  public BinaryTreeNodeBase<K,T*,C> {

    public:
    BinaryTreeNode(K key, T* value):BinaryTreeNodeBase<K,T*,C>(key,value) {
    }
    ~BinaryTreeNode(){
        delete BinaryTreeNodeBase<K,T*,C>::_value;
    }
    int CompareTo(K other) {
       return BinaryTreeNodeBase<K,T*,C>::_comparator->compare(
           BinaryTreeNodeBase<K,T*,C>::_key,
           other);
    }

    T* getValue() {
        return BinaryTreeNodeBase<K,T*,C>::_value;
    }

    // friend BinaryTreeNodeBase<K,T*,C>;
};



template <class K, class T, class C>
class BinaryTreeNode<K*,T,C>:  public BinaryTreeNodeBase<K*,T,C> {

    public:
    BinaryTreeNode(K* key, T value):BinaryTreeNodeBase<K*,T,C>(key,value){
    }
    ~BinaryTreeNode(){
        delete BinaryTreeNodeBase<K*,T,C>::_key;
    }
    int CompareTo(K* other) {
       return BinaryTreeNodeBase<K*,T,C>::_comparator->compare(
           BinaryTreeNodeBase<K*,T,C>::_key,
           other);
    }

    // friend BinasryTreeNodeBase<K*,T,C>;
};


// #include "BinaryTreeNode.tpp"

#endif
