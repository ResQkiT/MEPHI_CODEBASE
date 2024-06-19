#pragma once
#include <iostream>
#include "../Lab2/Sequence.h"
#include <string>
#include "Comparable.h"
#include <vector>
#include <functional>

template <class T>
    requires Comparable<T>
class BinaryTree 
{
protected:
    class BinaryNode
    {
    public:
        T element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode *get_left()
        {
            return left;
        }
        BinaryNode *get_right()
        {
            return right;
        }

        void set_left(BinaryNode *left_node)
        {
            this->left = left_node;
        }
        void set_right(BinaryNode *right_node)
        {
            this->right = right_node;
        }

        BinaryNode(const T &element, BinaryNode *left, BinaryNode *right)
            : element{element}, left{left}, right{right} {};

        BinaryNode(const T &element)
            : element{element}, left{nullptr}, right{nullptr} {};

        BinaryNode(const BinaryNode *other)
            : element{other->element}, left{other->leftNode}, right{other->rightNod} {}

        virtual ~BinaryNode() = default;
    };

    size_t size = 0;
    BinaryNode *root = nullptr;

    BinaryNode *clone(const BinaryNode *other)
    {
        if (other == nullptr)
            return nullptr;
        else
            return new BinaryNode(other->element, clone(other->left), clone(other->right));
    }

    void insert(BinaryNode *&head, const T &value)
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

    void remove(BinaryNode *&head, const T &value)
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
        {
            return true;
        }
    }
    BinaryNode *find_min(BinaryNode *head) const
    {
        if (nullptr != head)
        {
            while (nullptr != head->left)
            {
                head = head->left;
            }
        }

        return head;
    }
    BinaryNode *find_max(BinaryNode *head) const
    {
        if (nullptr != head)
        {
            while (nullptr != head->right)
            {
                head = head->right;
            }
        }
        return head;
    }
    void pre_order(BinaryNode *head, Sequence<T> &buffer) const
    {
        if (head == nullptr)
            return;
        buffer.append(head->element);
        pre_order(head->left, buffer);
        pre_order(head->right, buffer);
    }
    void in_order(BinaryNode *head, Sequence<T> &buffer) const
    {
        if (head == nullptr)
            return;
        in_order(head->left, buffer);
        buffer.append(head->element);
        in_order(head->right, buffer);
    }
    void post_order(BinaryNode *head, Sequence<T> &buffer) const
    {
        if (head == nullptr)
            return;

        post_order(head->left, buffer);
        post_order(head->right, buffer);
        buffer.append(head->element);
    }
    void custom_order(std::string &order, BinaryNode *head, Sequence<T> &buffer) const
    {
        if (head == nullptr)
            return;
        for (int i = 0; i < 3; i++)
        {
            switch (order.at(i))
            {
            case 'R':
                buffer.append(head->element);
                break;
            case 'l':
                custom_order(order, head->left, buffer);
                break;
            case 'r':
                custom_order(order, head->right, buffer);
                break;
            default:
                break;
            }
        }
    }
    T reduce(BinaryNode *head, std::function<T(T, T)> &function)
    {
        if (head->left)
        {
            T value = function(head->element, reduce(head->left, function));
            if (head->right)
            {
                return function(value, reduce(head->right, function));
            }
            return value;
        }
        if (head->right)
        {
            return function(head->element, reduce(head->right, function));
        }
        return head->element; // Нет поддеревьев => возвращаем значение из узла
    }

    bool equal(const BinaryNode *a, const BinaryNode *b) const
    {
        if (a == nullptr && b == nullptr)
            return true;
        if (a == nullptr || b == nullptr)
            return false;
        if (a->element != b->element)
            return false;

        return equal(a->left, b->left) && equal(a->right, b->right);
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

    virtual void insert(const T &value)
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

    size_t get_size() const
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
    }

    void in_order(Sequence<T> &buffer) const
    {
        in_order(root, buffer);
    }

    void post_order(Sequence<T> &buffer) const
    {
        post_order(root, buffer);
    }
    //"R"-root "r"-right "l"-left
    void custom_order(std::string &order, Sequence<T> &buffer) const
    {
        if (order.size() != 3 || !order.contains("R") || !order.contains("l") || !order.contains("r"))
            throw std::invalid_argument("Incorrect order");
        custom_order(order, root, buffer);
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
    void map(std::function<T(T)> function)
    {
        BinaryTree<T> copy(*this);
        make_empty();
        for (T x : copy)
        {
            this->insert(function(x));
        }
    }

    void where(std::function<bool(T)> function) 
    {
        BinaryTree<T> copy(*this);
        make_empty();
        for (T x : copy)
        {
            if (function(x))
                this->insert(x);
        }
    }

    T reduce(std::function<T(T, T)> function)
    {
        return reduce(root, function);
    }

    bool equal(const BinaryTree &other) const
    {
        return equal(this->root, other.root);
    }

    class Iterator
    {
    private:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        // LNR - left node right
        void LNR(BinaryNode *node)
        {
            if (node == nullptr)
                return;
            if (node->left != nullptr)
                LNR(node->left);
            path.push_back(node); // Добавляем узел в путь
            if (node->right != nullptr)
                LNR(node->right);
        }
        std::vector<BinaryNode *> path;
        int index;
        BinaryNode *root;

    public:
        Iterator(BinaryNode *node, int index) : index(index), root(node)
        {
            LNR(node);
        }
        reference operator*() const
        {
            return path[index]->element;
        }
        pointer operator->()
        {
            return path[index]->element;
        }
        Iterator &operator++()
        {
            index++;
            if (index > path.size())
                index = path.size();
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        friend bool operator==(const Iterator &a, const Iterator &b)
        {
            return a.index == b.index && a.root == b.root;
        };
        friend bool operator!=(const Iterator &a, const Iterator &b)
        {
            return a.index != b.index || a.root != b.root;
        };
    };

    Iterator begin() const
    {
        return Iterator(root, 0);
    }
    Iterator end() const
    {
        return Iterator(root, get_size());
    }
};