#include "BinaryTree.h"
#include "BinaryTreeNode.h"
#include <type_traits>

/**
 *   IMPLEMENTATION BinaryTreeBase and derived BinaryTree classes
 *   
 */

template<class K, class T, class C>
BinaryTreeBase<K,T,C>::BinaryTreeBase() {
    _head = 0;
    _count = 0;
    _foundCwP = new findWithParentResult<K,T,C>;
    // _emptyEL = new BinaryTreeNode<K,T,C>(0,0);
}

template<class K, class T, class C>
BinaryTreeBase<K,T,C>::~BinaryTreeBase() {
    // clearByNode(_head);
    clear();
    delete _foundCwP;
    // delete _emptyEL;
}

template<class K, class T, class C>
void BinaryTreeBase<K,T,C>::clearByNode(BinaryTreeNode<K,T,C>* node) {
    if (node != 0)
    {
        clearByNode((BinaryTreeNode<K,T,C>*)node->getLeft());
        clearByNode((BinaryTreeNode<K,T,C>*)node->getRight());
        delete node;
    }
};

template<class K, class T, class C>
BinaryTreeNode<K,T,C>* BinaryTreeBase<K,T,C>::createNode(K key,T value) {
    return new BinaryTreeNode<K,T,C>(key, value);
}

template<class K, class T, class C>
void BinaryTreeBase<K,T,C>::add(K key, T value)
{
    // Случай 1: Если дерево пустое, просто создаем корневой узел.
    if (_head == 0) {
        _head = createNode(key, value);
    }
    // Случай 2: Дерево не пустое => 
    // ищем правильное место для вставки.
    else {
        addTo(_head, key, value);
    }
    _count++;
}
 
// Рекурсивная ставка.
template<class K, class T, class C>
void BinaryTreeBase<K,T,C>::addTo(BinaryTreeNode<K,T,C>* node, K key, T value)
{
    // Случай 1: Вставляемое значение меньше значения узла
    if (node->CompareTo(key) > 0)
    {
        if (node->Left == 0) { // Если нет левого поддерева, добавляем значение в левого ребенка,
            node->Left = createNode(key, value);
        }
        else { // в противном случае повторяем для левого поддерева.
            addTo((BinaryTreeNode<K,T,C>*)node->getLeft(), key, value);
        }
    }
    // Случай 2: Вставляемое значение больше или равно значению узла.
    else {
        
        if (node->Right == 0)  {// Если нет правого поддерева, добавляем значение в правого ребенка,
            node->Right = createNode(key, value);
        }
        else { // в противном случае повторяем для правого поддерева.
            addTo((BinaryTreeNode<K,T,C>*)node->getRight(), key, value);
        }
    }
}

// template<class K, class T, class C>
// T* BinaryTreeBase<K,T,C>::getByKey(K key) {
//     _foundCwP = findWithParent(key);
//     if ((_foundCwP != 0)  &&  (_foundCwP->current != 0)) {
//         T x= _foundCwP->current->getValue();

//             return &x;
//     }
//     return nullptr;
// }

template<class K, class T, class C>
bool BinaryTreeBase<K,T,C>::remove(K key) 
{
    // Находим удаляемый узел.
    _foundCwP = findWithParent(key);
    BinaryTreeNode<K,T,C>* current = (BinaryTreeNode<K,T,C>*)_foundCwP->current;
    BinaryTreeNode<K,T,C>* parent = (BinaryTreeNode<K,T,C>*)_foundCwP->parent;
    BinaryTreeNode<K,T,C>* removed = (BinaryTreeNode<K,T,C>*)_foundCwP->current;

    if (current == 0) {
        return false;
    }
    _count--;
    // Случай 1: Если нет детей справа, левый ребенок встает на место удаляемого.
    if (current->Right == 0) {
        if (parent == 0) {
            _head = (BinaryTreeNode<K,T,C>*)current->Left;
        }
        else {
            int result = parent->CompareTo(current->getKey());
            if (result > 0) {
                // Если значение родителя больше текущего,
                // левый ребенок текущего узла становится левым ребенком родителя.
                parent->Left = current->Left;
            }
            else if (result < 0) { 
                // Если значение родителя меньше текущего, 
                // левый ребенок текущего узла становится правым ребенком родителя. 
                parent->Right = current->Left; 
            } 
        } 
    } 
    // Случай 2: Если у правого ребенка нет детей слева 
    // то он занимает место удаляемого узла. 
    else if (current->Right->Left == 0) {
        current->Right->Left = current->Left;
        if (parent == 0) {
                _head = (BinaryTreeNode<K,T,C>*)current->getRight(); 
        } else  { 
            int result = parent->CompareTo(current->getKey());
            if (result > 0) {
                // Если значение родителя больше текущего,
                // правый ребенок текущего узла становится левым ребенком родителя.
                parent->Left = current->Right;
            }
            else if (result < 0) { 
                // Если значение родителя меньше текущего, 
                // правый ребенок текущего узла становится правым ребенком родителя. 
                parent->Right = current->Right; 
            } 
        } 
    } 

    // Случай 3: Если у правого ребенка есть дети слева, крайний левый ребенок 
    // из правого поддерева заменяет удаляемый узел. 
    else { 
        // Найдем крайний левый узел. 
        BinaryTreeNode<K,T,C>* leftmost = (BinaryTreeNode<K,T,C>*)(current->getRight())->getLeft(); 
        BinaryTreeNode<K,T,C>* leftmostParent = (BinaryTreeNode<K,T,C>*)current->getRight(); 

        while (leftmost->Left != 0) { 
            leftmostParent = leftmost; 
            leftmost = (BinaryTreeNode<K,T,C>*) leftmost->getLeft(); 
        }
        // Левое поддерево родителя становится правым поддеревом крайнего левого узла. 
        leftmostParent->Left = leftmost->Right; 
        // Левый и правый ребенок текущего узла становится левым и правым ребенком крайнего левого. 
        leftmost->Left = current->Left; 
        leftmost->Right = current->Right; 

        if (parent == 0) { 
            _head = leftmost; 
        } else { 
            int result = parent->CompareTo(current->getKey()); 
        
            if (result > 0) {
                // Если значение родителя больше текущего,
                // крайний левый узел становится левым ребенком родителя.
                parent->Left = leftmost;
            }
            else if (result < 0) {
                // Если значение родителя меньше текущего,
                // крайний левый узел становится правым ребенком родителя.
                parent->Right = leftmost;
            }
        }
    }            

    delete removed;
    return true;
}

template<class K, class T, class C>
bool BinaryTreeBase<K,T,C>::contains(K key)
{
    _foundCwP = findWithParent(key);
    return  _foundCwP->current != 0;
}

/**
 *  Находит и возвращает первый узел с заданным значением. Если значение
 *  не найдено, возвращает null. Также возвращает родителя найденного узла (или null)
 *  для использования в методе Remove.
 * @param key - ключ для поиска элемента дерева
 */
template<class K, class T, class C>
findWithParentResult<K,T,C>* BinaryTreeBase<K,T,C>::findWithParent(K key)
{
    // Попробуем найти значение в дереве.
    _foundCwP->current = _head;
    _foundCwP->parent = NULL;
 
    // До тех пор, пока не нашли...
    while (_foundCwP->current != 0)
    {
        int cmpRes = _foundCwP->current->CompareTo((K)key);
        if (cmpRes > 0)
        {
            // Если искомое значение меньше, идем налево.
            _foundCwP->parent  = _foundCwP->current;
            _foundCwP->current = (BinaryTreeNode<K,T,C>*)_foundCwP->current->getLeft();
        }
        else if (cmpRes < 0)
        {
            // Если искомое значение больше, идем направо.
            _foundCwP->parent = _foundCwP->current ;
            _foundCwP->current  = (BinaryTreeNode<K,T,C>*)_foundCwP->current->getRight();
        }
        else
        {  // Если равны, то останавливаемся
            break;
        }
    }
    return _foundCwP;
}

/**
 *   Возвращает количество элементов в дереве.
*/
template<class K, class T, class C>
int BinaryTreeBase<K,T,C>::size()
{
        return _count;
}

template<class K, class T, class C>
void BinaryTreeBase<K,T,C>::clear() {
    clearByNode(_head);
    if (_foundCwP->current != NULL ) _foundCwP->current = NULL;
    if (_foundCwP->parent != NULL )  _foundCwP->parent = NULL;
    _count = 0;
}


template<class K, class T, class C>
void BinaryTreeBase<K,T,C>::preOrderTraversal(BinaryTreeAction<K,T>* action) {
    preOrderTraversal(action, _head);
}

template<class K, class T, class C>
void BinaryTreeBase<K,T,C>::preOrderTraversal(BinaryTreeAction<K,T>* action, BinaryTreeNode<K,T,C>* node) {
    if (node != 0) {
        action->run(node->getKey(),node->getValue());
        preOrderTraversal(action, (BinaryTreeNode<K,T,C>*)node->Left);
        preOrderTraversal(action, (BinaryTreeNode<K,T,C>*)node->Right);
    }
}

template<class K, class T, class C>
void BinaryTreeBase<K,T,C>::postOrderTraversal(BinaryTreeAction<K,T>* action)
{
    postOrderTraversal(action, _head);
}
 
template<class K, class T, class C>
void BinaryTreeBase<K,T,C>::postOrderTraversal(BinaryTreeAction<K,T>* action, BinaryTreeNode<K,T,C>* node) {
    if (node != 0)
    {
        postOrderTraversal(action, (BinaryTreeNode<K,T,C>*)node->getLeft());
        postOrderTraversal(action, (BinaryTreeNode<K,T,C>*)node->getRight());
        action->run(node->getKey(), node->getValue());
    }
};


template<class K, class T, class C>
void BinaryTreeBase<K,T,C>::inOrderTraversal(BinaryTreeAction<K,T>* action)
{
    inOrderTraversal(action, _head);
};
 
template<class K, class T, class C>
void BinaryTreeBase<K,T,C>::inOrderTraversal(BinaryTreeAction<K,T>* action, BinaryTreeNode<K,T,C>* node) {
    if (node != 0)
    {
        inOrderTraversal(action, (BinaryTreeNode<K,T,C>*)node->getLeft());
        action->run(node->getKey(),node->getValue());
        inOrderTraversal(action, (BinaryTreeNode<K,T,C>*)node->getRight());
    }
};
