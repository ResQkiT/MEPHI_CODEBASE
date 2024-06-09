#pragma once
#include "BinaryTree.h"

template<class T> 
class BinaryNode{
public:
    T element;
    BinaryNode<T> * left;
    BinaryNode<T> * right;

    BinaryNode(const T &element, BinaryNode<T> *left, BinaryNode<T> *right)
            : element{element}, left{left}, right{right} {};

    BinaryNode(const T &element)
            : element{element}, left{nullptr}, right{nullptr} {};

    BinaryNode(const BinaryNode *other)
        : element{other->element}, left{other->leftNode}, right{other->rightNod} {}
};
