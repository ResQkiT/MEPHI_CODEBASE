#pragma once
#include "BinaryTree.h"

template<class T>
class Set{
private:
    BinaryTree<T> tree;

public:
    Set() : tree{BinaryTree<T>()} {}
    Set(T arr[], size_t size) : tree{BinaryTree<T>(arr, size)}{}
    
};