#pragma once
#include "BinaryNode.h"

template<class T>
class AvlNode : public BinaryNode<T>{
private:
    int balance_factor;
public:
    AvlNode(const T &element, AvlNode<T> *left, AvlNode<T> *right, int balance)
        : BinaryNode<T>(element, left, right), balance_factor{balance}{}

    AvlNode(const T& element)
        : BinaryNode<T>(element, nullptr, nullptr), balance_factor{0} {}

    AvlNode(const AvlNode *other)
        : BinaryNode<T>(other->element, other->left, other->right), balance_factor{other->balance_factor}{}
    
    AvlNode<T> * left() override {
        return (AvlNode<T> *) BinaryNode<T>::_left();
    }
    AvlNode<T> * right() override {
        return (AvlNode<T> *) BinaryNode<T>::_right();
    }
    int get_balanced_factor(){
        return balance_factor;
    }
};