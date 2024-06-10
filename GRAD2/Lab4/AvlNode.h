#pragma once

template<class T>
class AvlNode {
public:
    T element;
    AvlNode<T> * left;
    AvlNode<T> * right;
    int height;
public:
    AvlNode(const T &element, AvlNode<T> *left, AvlNode<T> *right, int height)
            : element{element}, left{left}, right{right}, height{height} {};

    AvlNode(const T &element)
            : element{element}, left{nullptr}, right{nullptr}, height{1} {};

    AvlNode(const AvlNode<T> *other)
        : element{other->element}, left{other->leftNode}, right{other->rightNod}, height{other->height} {}
};