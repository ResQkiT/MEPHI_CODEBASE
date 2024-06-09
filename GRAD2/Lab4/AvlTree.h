#pragma once
#include "BinaryTree.h"
#include "AvlNode.h"

template<class T>
class AvlTree : public BinaryTree<T> {
private:
    /*
    void single_rotate_left(AvlNode<T>* &target){

    }
    void single_rotate_right(AvlNode<T>* &target){
        
    }
    void double_rotate_left(AvlNode<T>* &target){
        
    }
    void double_rotate_right(AvlNode<T>* &target){
        
    }
    void update_left_tree(AvlNode<T> * &target){

    }

    void avl_insert(AvlNode<T> *& tree, AvlNode<T> *& new_node, int &revise_balance_factor){

    }
    void avl_delete(AvlNode<T> *& tree, AvlNode<T> *& new_node, int &revise_balance_factor){

    }
    AvlNode<T> * get_new_avl_node(const T& item, AvlNode<T> * left_ptr, AvlNode<T> * right_ptr){
        return nullptr;

    }
    */
public:
    AvlTree(){
    }
    //AvlNode(const AvlTree<T> & other){} 
    void insert(const T& item) override {
        AvlNode<T> * root = BinaryTree<T>::get_root();
        AvlNode<T> * new_node = new AvlNode<T>(item, nullptr, nullptr); 
    }

};