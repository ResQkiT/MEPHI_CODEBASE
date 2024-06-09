#pragma once
#include <iostream>
#include "BinaryNode.h"
#include "../Lab2/Sequence.h"
#include <string>

template <class T>
concept Comparable = requires(T a, T b) {
    a < b;
    a > b;
};





template <class T> requires Comparable<T>
class BinaryTree
{
private:
    size_t size;
    BinaryNode<T> *root;

    BinaryNode<T> *clone(const BinaryNode<T> *other)
    {
        if (other == nullptr)
            return nullptr;
        else
            return new BinaryNode<T>(other->element, clone(other->left_node), clone(other->right_node));
    }

    void insert(const T &value, BinaryNode<T> *&target)
    {

        if (target == nullptr)
        {
            size++;
            target = new BinaryNode<T>(value);
        }
        else if (value < target->element)
        {
            insert(value, target->left_node);
        }
        else if (value > target->element)
        {
            insert(value, target->right_node);
        }
        // не вставляем повторяющиеся данные
    }

    void remove(const T &theElement, BinaryNode<T> *&target)
    {
        if (target == nullptr)
            return;
        else
        {
            if (theElement < target->element)
            {
                remove(theElement, target->left_node);
            }
            else if (theElement > target->element)
            {
                remove(theElement, target->right_node);
            }
            else if (target->left_node != nullptr && target->right_node != nullptr)
            {
                // свайп минимального элемента и текущего
                target->element = find_min(target->right_node)->element;
                remove(target->element, target->right_node);
            }
            else
            { // наподумать
                BinaryNode<T> *old_node = target;
                target = (nullptr != target->left_node) ? target->left_node : target->right_node;
                size--;
                delete old_node;
            }
        }
    }

    void make_empty(BinaryNode<T> *&target)
    {
        if (target == nullptr)
            return;

        make_empty(target->left_node);
        make_empty(target->right_node);
        size--;
        delete target;
        target = nullptr;
    }

    bool find(const T &value, BinaryNode<T> *target) const
    {
        if (target == nullptr)
            return false;
        else if (value < target->element)
        {
            return find(value, target->left_node);
        }
        else if (value > target->element)
        {
            return find(value, target->right_node);
        }
        else
        { // value == target->element
            return true;
        }
    }
    BinaryNode<T> *find_min(BinaryNode<T> *target_node) const
    {
        if (nullptr != target_node)
        {
            while (nullptr != target_node->left_node)
            {
                target_node = target_node->left_node;
            }
        }

        return target_node;
    }
    BinaryNode<T> *find_max(BinaryNode<T> *target_node) const
    {
        if (nullptr != target_node)
        {
            while (nullptr != target_node->right_node)
            {
                target_node = target_node->right_node;
            }
        }
        return target_node;
    }
    void pre_order(BinaryNode<T> *target_node, Sequence<T> &buffer) const
    {
        if (target_node == nullptr)
            return;
        std::cout << target_node->element << " ";
        buffer.append(target_node->element);
        pre_order(target_node->left_node, buffer);
        pre_order(target_node->right_node, buffer);
    }
    void in_order(BinaryNode<T> *target_node, Sequence<T> &buffer) const
    {
        if (target_node == nullptr)
            return;
        in_order(target_node->left_node, buffer);
        std::cout << target_node->element << " ";
        buffer.append(target_node->element);
        in_order(target_node->right_node, buffer);
    }
    void post_order(BinaryNode<T> *target_node, Sequence<T> &buffer) const
    {
        if (target_node == nullptr)
            return;

        post_order(target_node->left_node, buffer);
        post_order(target_node->right_node, buffer);
        std::cout << target_node->element << " ";
        buffer.append(target_node->element);
    }
    void custom_order(std::string &order, BinaryNode<T> *target_node, Sequence<T> &buffer) const
    {
        if (order.size() != 3 || !order.contains("R") || !order.contains("l") || !order.contains("r"))
            throw std::invalid_argument("Incorrect order");
        if (target_node == nullptr)
            return;
        for (int i = 0; i < 3; i++)
        {
            switch (order.at(i))
            {
            case 'R':
                std::cout << target_node->element << " ";
                buffer.append(target_node->element);
                break;
            case 'l':
                custom_order(order, target_node->left_node, buffer);
                break;
            case 'r':
                custom_order(order, target_node->right_node, buffer);
                break;
            default:
                break;
            }
        }
    }

    int get_children_count(BinaryNode<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return std::max(get_children_count(node->left_node), get_children_count(node->right_node)) + 1;
    }

    BinaryNode<T> *rotate_right(BinaryNode<T> *prev_root)
    {
        BinaryNode<T> *new_root = prev_root->left_node;
        prev_root->right_node = new_root->right_node;
        new_root->right_node = prev_root;
        return new_root;
    }

    BinaryNode<T> *rotate_left(BinaryNode<T> *prev_root)
    {
        BinaryNode<T> *new_root = prev_root->right_node;
        prev_root->right_node = new_root->left_node;
        new_root->left_node= prev_root;
        return new_root;
    }

    int get_balance(BinaryNode<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return get_children_count(node->left_node) - get_children_count(node->right_node);
    }
protected:
    BinaryNode<T> * get_root(){
        return this->root;
    }
public:
    BinaryTree() : size{0}, root{nullptr} {}

    BinaryTree(const BinaryTree &other) : size{other.size}, root{nullptr}
    {
        this->root = clone(other.root);
    }
    BinaryTree(const T &theElement) : size{1}, root{nullptr}
    {
        root = new BinaryNode<T>(theElement);
    }
    BinaryTree(T arr[], size_t size) : size{0}, root{nullptr}
    {
        for (size_t i = 0; i < size; i++)
        {
            insert(arr[i]);
        }
    }

    ~BinaryTree()
    {
        make_empty(root);
    }

    void insert(const T &theElement)
    {
        insert(theElement, root);
    }

    void remove(const T &theElement)
    {
        remove(theElement, root);
    }

    void make_empty()
    {
        make_empty(root);
    }
    bool is_empty() const
    {
        return root == nullptr;
    }

    size_t get_size()
    {
        return size;
    }

    bool find(const T &theElement) const
    {
        return find(theElement, root);
    }

    void pre_order(Sequence<T> &buffer) const
    {
        pre_order(root, buffer);
        std::cout << '\n';
    }

    void in_order(Sequence<T> &buffer) const
    {
        in_order(root, buffer);
        std::cout << '\n';
    }

    void post_order(Sequence<T> &buffer) const
    {
        post_order(root, buffer);
        std::cout << '\n';
    }
    //"R"-root "r"-right "l"-left
    void custom_order(std::string &order, Sequence<T> &buffer) const
    {
        custom_order(order, root, buffer);
        std::cout << '\n';
    }
    void merge(const BinaryTree<T> &other)
    {
        BinaryTree<T> copy(other);
        while (!copy.is_empty())
        {
            T temp = copy.find_min(copy.root)->element;
            copy.remove(temp);
            this->insert(temp);
        }
    }
    void balance()
    {
        int balance = get_balance(root);

        if (balance > 1)
        {
            if (get_balance(root->left_node) < 0)
            {
                root->left_node = rotate_left(root->left_node);
            }
            this->root = rotate_right(root);
        }

        if (balance < -1)
        {
            if (get_balance(root->right_node) > 0)
            {
                root->right_node = rotate_right(root->right_node);
            }
            this->root = rotate_left(root);
        }
    }
};