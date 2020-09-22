#ifndef _BINARY_TREE_ACTION_H__
#define _BINARY_TREE_ACTION_H__
#include "BinaryTreeNode.h"

template <class T*>
class BinaryTreeAction {
    virtual void run(T) = 0;
};

#endif