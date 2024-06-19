#pragma once
#include <string>
#include "../BinaryTree.h"
#include "../AvlTree.h"
#include "AbstractAdapter.h"
#include "../../Lab2/DynamicArraySequence.h"

using namespace std;

template <class T, template<class> class Container>
class TreeAdapter : public AbstractAdapter<T>
{
private:
    Container<T> container;
    string type = "binary/avl tree";

public:
    TreeAdapter() : container{Container<T>()} {}
    TreeAdapter(const TreeAdapter<T, Container> & other) : container{other.container}{
        type = other.type;
    }
    ~TreeAdapter() = default;

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
        container.pre_order(order);
        cout << order << "\n";
    }
    void in_order_output() override
    {
        cout << "Printing elements in 'in'-order" << endl;
        DynamicArraySequence<T> order;
        container.in_order(order);
        cout << order << "\n";
    }
    void post_order_output() override
    {
        cout << "Printing elements in 'post'- order" << endl;
        DynamicArraySequence<T> order;
        container.post_order(order);
        cout << order << "\n";
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
    TreeAdapter<T, Container> * clone() override
    {
        TreeAdapter<T, Container> * clone = new TreeAdapter<T, Container>(*this);
        return clone;
    }
};