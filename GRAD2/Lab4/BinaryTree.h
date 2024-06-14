#pragma once
#include <iostream>
#include "../Lab2/Sequence.h"
#include <string>
#include "Comparable.h"

template <class T>
class BinaryTree
{
public:

    class BinaryNode
    {
    public:
        T element;
        BinaryNode *left;
        BinaryNode *right;

        
        BinaryNode * get_left(){
            return left;
        }
        BinaryNode * get_right(){
            return right;
        }

        virtual void set_left(BinaryNode * left_node){
            this->left = left_node;
        }
        virtual void set_right(BinaryNode * right_node){
            this->right = right_node;
        }

        BinaryNode(const T &element, BinaryNode *left, BinaryNode *right)
            : element{element}, left{left}, right{right} {};

        BinaryNode(const T &element)
            : element{element}, left{nullptr}, right{nullptr} {};

        BinaryNode(const BinaryNode *other)
            : element{other->element}, left{other->leftNode}, right{other->rightNod} {}
    };

protected:
    size_t size = 0;
    BinaryNode *root = nullptr;

    BinaryNode *clone(const BinaryNode *other)
    {
        if (other == nullptr)
            return nullptr;
        else
            return new BinaryNode(other->element, clone(other->left), clone(other->right));
    }

    void insert(BinaryNode *& head, const T & value)
    {

        if (head == nullptr)
        {
            size++;
            head = new BinaryNode(value);
        }
        else if (value < head->element)
        {
            insert(head->left, value);
        }
        else if (value > head->element)
        {
            insert(head->right, value);
        }
        // не вставляем повторяющиеся данные
    }

    void remove(BinaryNode *& head, const T &value)
    {
        if (head == nullptr)
            return;
        else
        {
            if (value < head->element)
            {
                remove(head->left, value);
            }
            else if (value > head->element)
            {
                remove(head->right, value);
            }
            else if (head->left != nullptr && head->right != nullptr)
            {
                // свайп минимального элемента и текущего
                head->element = find_min(head->right)->element;
                remove(head->right, value);
            }
            else
            {
                BinaryNode *old_node = head;
                head = (nullptr != head->left) ? head->left : head->right;
                size--;
                delete old_node;
            }
        }
    }

    void make_empty(BinaryNode *&head)
    {
        if (head == nullptr)
            return;

        make_empty(head->left);
        make_empty(head->right);
        // на этом этапе оба потомка очищены, можно спокойно удалять
        size--;
        delete head;
        head = nullptr;
    }

    bool find(const T &value, BinaryNode *head) const
    {
        if (head == nullptr)
            return false;
        else if (value < head->element)
        {
            return find(value, head->left);
        }
        else if (value > head->element)
        {
            return find(value, head->right);
        }
        else
        { // value == head->element
            return true;
        }
    }
    BinaryNode *find_min(BinaryNode *head_node) const
    {
        if (nullptr != head_node)
        {
            while (nullptr != head_node->left)
            {
                head_node = head_node->left;
            }
        }

        return head_node;
    }
    BinaryNode *find_max(BinaryNode *head_node) const
    {
        if (nullptr != head_node)
        {
            while (nullptr != head_node->right)
            {
                head_node = head_node->right;
            }
        }
        return head_node;
    }
    void pre_order(BinaryNode *head_node, Sequence<T> &buffer) const
    {
        if (head_node == nullptr)
            return;
        std::cout << head_node->element << " ";
        buffer.append(head_node->element);
        pre_order(head_node->left, buffer);
        pre_order(head_node->right, buffer);
    }
    void in_order(BinaryNode *head_node, Sequence<T> &buffer) const
    {
        if (head_node == nullptr)
            return;
        in_order(head_node->left, buffer);
        std::cout << head_node->element << " ";
        buffer.append(head_node->element);
        in_order(head_node->right, buffer);
    }
    void post_order(BinaryNode *head_node, Sequence<T> &buffer) const
    {
        if (head_node == nullptr)
            return;

        post_order(head_node->left, buffer);
        post_order(head_node->right, buffer);
        std::cout << head_node->element << " ";
        buffer.append(head_node->element);
    }
    void custom_order(std::string &order, BinaryNode *head_node, Sequence<T> &buffer) const
    {
        if (head_node == nullptr)
            return;
        for (int i = 0; i < 3; i++)
        {
            switch (order.at(i))
            {
            case 'R':
                std::cout << head_node->element << " ";
                buffer.append(head_node->element);
                break;
            case 'l':
                custom_order(order, head_node->left, buffer);
                break;
            case 'r':
                custom_order(order, head_node->right, buffer);
                break;
            default:
                break;
            }
        }
    }

public:
    BinaryTree() : size{0}, root{nullptr} {}

    BinaryTree(const BinaryTree &other) : size{other.size}, root{clone(other.root)}
    {
    }
    BinaryTree(const T &value) : size{1}, root{nullptr}
    {
        root = new BinaryNode(value);
    }
    BinaryTree(T arr[], size_t size) : size{0}, root{nullptr}
    {
        for (size_t i = 0; i < size; i++)
        {
            insert(arr[i]);
        }
    }

    virtual ~BinaryTree()
    {
        make_empty(root);
    }

    virtual void insert(const T& value)
    {
        insert(root, value);
    }

    virtual void remove(const T &value)
    {
        remove(root, value);
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

    bool find(const T &value) const
    {
        return find(value, root);
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
        if (order.size() != 3 || !order.contains("R") || !order.contains("l") || !order.contains("r"))
            throw std::invalid_argument("Incorrect order");
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