#pragma once
#include "BinaryTree.h"

template<class T> 
class BinaryNode{
private:
    T element;
    BinaryNode<T> * left_node;
    BinaryNode<T> * right_node;
protected:
    BinaryNode<T> * _get_left(){
        return left_node;
    }
    BinaryNode<T> * _get_right(){
        return right_node;
    }
    void set_left(const T*& left_ptr){
        left_node =
        left_node = left_node;
    }
    T& _element(){
        return element;
    }
public:
    BinaryNode(const T &element, BinaryNode<T> *left, BinaryNode<T> *right)
            : element{element}, left_node{left}, right_node{right} {};

    BinaryNode(const T &element)
            : element{element}, left_node{nullptr}, right_node{nullptr} {};

    BinaryNode(const BinaryNode *other)
        : element{other->element}, left_node{other->leftNode}, right_node{other->rightNod} {}
    virtual ~BinaryNode() = 0;
    T& value() { return _element(); }
    BinaryNode<T> * get_left() {return _left();}
    BinaryNode<T> * get_right() {return _right();}
    void set_left(const T*& left_ptr){ }
};
