#pragma once

template<class T>
class AvlNode {
public:
    int balance_factor;
    AvlNode<T> * left;
    AvlNode<T> * right;
    T element;
public:
    AvlNode(const T &element, AvlNode<T> *left, AvlNode<T> *right, int balance_factor)
            : element{element}, left{left}, right{right}, balance_factor{balance_factor} {};

    AvlNode(const T &element)
            : element{element}, left{nullptr}, right{nullptr}, balance_factor{0} {};

    AvlNode(const AvlNode<T> *other)
        : element{other->element}, left{other->leftNode}, right{other->rightNod}, balance_factor{other->balance_factor} {}
};