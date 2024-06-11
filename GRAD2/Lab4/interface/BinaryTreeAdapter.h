#pragma once
#include "../BinaryTree.h"
#include <string>
#include "AbstractAdapter.h"
#include "../../Lab2/DynamicArraySequence.h"

using namespace std;

template <class T>
class BinaryTreeAdapter : public AbstractAdapter<T>
{
private:
    BinaryTree<T> container;
    string type = "avl tree";
public:
    BinaryTreeAdapter() : container{BinaryTree<T>()} {}
    BinaryTreeAdapter(const BinaryTreeAdapter<T> & other) : container{other.container}{
        type = other.type;
    }
    ~BinaryTreeAdapter() = default;

    void create_working_atd(T list[], size_t size) override
    {
        for (size_t i = 0; i < size; i++)
        {
            container.insert(list[i]);
        }
    }

    void pre_order_output() override
    {
        cout << "Printing elements in 'pre'-order" << endl;
        DynamicArraySequence<T> order;
        cout << order << "\n";
        container.pre_order(order);
    }
    void in_order_output() override
    {
        cout << "Printing elements in 'in'-order" << endl;
        DynamicArraySequence<T> order;
        cout << order << "\n";
        container.in_order(order);
    }
    void post_order_output() override
    {
        cout << "Printing elements in 'post'- order" << endl;
        DynamicArraySequence<T> order;
        cout << order << "\n";
        container.post_order(order);
    }
    void insert(const T &value) override
    {
        container.insert(value);
    }
    void remove(const T &value) override
    {
        container.remove(value);
    }
    void find(const T &value) override
    {
        if (container.find(value))
        {
            cout << "Element was successfully found" << endl;
        }
        else
            cout << "Oops...element noy in avl tree" << endl;
    }
    std::string &get_type() override
    {
        return type;
    }
    BinaryTreeAdapter<T> * clone() override
    {
        BinaryTreeAdapter<T> * clone = new BinaryTreeAdapter<T>(*this);
        return clone;
    }
};