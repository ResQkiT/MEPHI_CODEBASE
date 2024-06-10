#pragma once
#include <iostream>
#include "BinaryNode.h"
#include "../Lab2/Sequence.h"
#include <string>
#include "Comparable.h"

template <class T> requires Comparable<T>
class BinaryTree
{
private:
    size_t size = 0;
    BinaryNode<T> * root = nullptr;

    BinaryNode<T> *clone(const BinaryNode<T> *other)
    {
        if (other == nullptr)
            return nullptr;
        else
            return new BinaryNode<T>(other->element, clone(other->left), clone(other->right));
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
            insert(value, target->left);
        }
        else if (value > target->element)
        {
            insert(value, target->right);
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
                remove(theElement, target->left);
            }
            else if (theElement > target->element)
            {
                remove(theElement, target->right);
            }
            else if (target->left != nullptr && target->right != nullptr)
            {
                // свайп минимального элемента и текущего
                target->element = find_min(target->right)->element;
                remove(target->element, target->right);
            }
            else
            { 
                BinaryNode<T> *old_node = target;
                target = (nullptr != target->left) ? target->left : target->right;
                size--;
                delete old_node;
            }
        }
    }

    void make_empty(BinaryNode<T> *&target)
    {
        if (target == nullptr)
            return;

        make_empty(target->left);
        make_empty(target->right);
        //на этом этапе оба потомка очищены, можно спокойно удалять
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
            return find(value, target->left);
        }
        else if (value > target->element)
        {
            return find(value, target->right);
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
            while (nullptr != target_node->left)
            {
                target_node = target_node->left;
            }
        }

        return target_node;
    }
    BinaryNode<T> *find_max(BinaryNode<T> *target_node) const
    {
        if (nullptr != target_node)
        {
            while (nullptr != target_node->right)
            {
                target_node = target_node->right;
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
        pre_order(target_node->left, buffer);
        pre_order(target_node->right, buffer);
    }
    void in_order(BinaryNode<T> *target_node, Sequence<T> &buffer) const
    {
        if (target_node == nullptr)
            return;
        in_order(target_node->left, buffer);
        std::cout << target_node->element << " ";
        buffer.append(target_node->element);
        in_order(target_node->right, buffer);
    }
    void post_order(BinaryNode<T> *target_node, Sequence<T> &buffer) const
    {
        if (target_node == nullptr)
            return;

        post_order(target_node->left, buffer);
        post_order(target_node->right, buffer);
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
                custom_order(order, target_node->left, buffer);
                break;
            case 'r':
                custom_order(order, target_node->right, buffer);
                break;
            default:
                break;
            }
        }
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
};