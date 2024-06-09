#pragma once
#include "BinaryTree.h"
#include "AvlNode.h"

const int leftheavy = -1;
const int balanced = 0;
const int rightheavy = 1;

template<class T>
class AvlTree
{
private:
    AvlNode<T> * root = nullptr;
    size_t size = 0;

    void single_rotate_left(AvlNode<T> *&target)
    {
        AvlNode<T> *rc;
        rc = target->right;
        target->balance_factor = balanced;
        rc->balance_factor = balanced;
        target->right = rc->left;
        rc->left = target;

        target = rc;
    }
    void single_rotate_right(AvlNode<T> *&target)
    {
        AvlNode<T> *lc;
        lc = target->left;
        target->balance_factor = balanced;
        lc->balance_factor = balanced;
        target->left = lc->right;
        lc->right = target;
        target = lc;
    }
    void double_rotate_left(AvlNode<T> *&target)
    {
        AvlNode<T> *np = target->right ,*lc = np->left;
        if(lc->balance_factor = leftheavy){
            target->balance_factor = balanced;
            np->balance_factor = leftheavy;
        }
        else{
            target->balance_factor = leftheavy;
            np->balance_factor = balanced;
        }
        lc->balance_factor = balanced;

        np->left = lc->right;
        lc->right = np;
        target->right = lc->left;
        lc->left = target;
        target = lc;
    }
    void double_rotate_right(AvlNode<T> *&target)
    {
        AvlNode<T> *lc = target->left, *np = lc->right;

        if(np->balance_factor == rightheavy){
            target->balance_factor = balanced;
            lc->balance_factor = rightheavy;
        }
        else{
            target->balance_factor = rightheavy;
            lc->balance_factor = balanced;
        }
        np->balance_factor = balanced;
        lc->right = np->left;
        np->left = lc;
        target->left = np->right;
        np->right = target;
        target = np;
    }

    void update_left_tree(AvlNode<T> *&target, int &revise_balance_factor)
    {
        AvlNode<T> *lc = target->left;
        if (lc->balance_factor == leftheavy)
        {
            single_rotate_right(target);
            revise_balance_factor = 0;
        }
        else if (lc->balance_factor == rightheavy)
        {
            double_rotate_right(target);
            revise_balance_factor = 0;
        }
    }
    void update_right_tree(AvlNode<T> *&target, int & revise_balance_factor)
    {
        AvlNode<T> * rc = target->left;
        if(rc->balance_factor == rightheavy){
            single_rotate_left(target);
            revise_balance_factor = 0;
        }
        else if (rc->balance_factor == leftheavy){
            double_rotate_left(target);
            revise_balance_factor = 0;
        }
    }

    void avl_insert(AvlNode<T> *& tree, AvlNode<T> *& new_node, int &revise_balance_factor)
    {
        int rebalanceCurrNode;
        if (tree == nullptr)
        {
            tree = new_node;
            tree->balance_factor = balanced;
            revise_balance_factor = 1;
        }
        else if (new_node->element < tree->element)
        {
            avl_insert(tree->left, new_node, rebalanceCurrNode);
            if (rebalanceCurrNode)
            {
                if (tree->balance_factor == leftheavy)
                    update_left_tree(tree, revise_balance_factor);

                else if (tree->balance_factor == balanced)
                {
                    tree->balance_factor = leftheavy;
                    revise_balance_factor = 1;
                }
                else
                {
                    tree->balance_factor = balanced;
                    revise_balance_factor = 0;
                }
            }
            else
                revise_balance_factor = 0;
        }
        else if (new_node->element < tree->element)
        {
            avl_insert(tree->right, new_node, rebalanceCurrNode);
            if (rebalanceCurrNode)
            {
                if (tree->balance_factor == rightheavy)
                    update_right_tree(tree, revise_balance_factor);

                else if (tree->balance_factor == balanced)
                {
                    tree->balance_factor = rightheavy;
                    revise_balance_factor = 1;
                }
                else
                {
                    tree->balance_factor = balanced;
                    revise_balance_factor = 0;
                }
            }
            else
                revise_balance_factor = 0;
        }
    }

public:
    void insert(const T &item)
    {
        AvlNode<T> *tree_root =this->root;
        AvlNode<T> *new_node = new AvlNode<T>(item, nullptr, nullptr, 0);
        int revise_factor = 0;
        avl_insert(tree_root, new_node, revise_factor);
        this->root = tree_root;
        this->size++;
    }
    AvlTree(){
        this->root = nullptr;
    }
    AvlTree(T arr[], size_t size){
        for (size_t i = 0; i < size; i++)
        {
            insert(arr[i]);
        }
    }
    ~AvlTree() = default;
    // AvlNode(const AvlTree<T> & other){}
};