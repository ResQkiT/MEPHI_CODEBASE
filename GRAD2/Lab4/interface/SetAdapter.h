#pragma once
#include <string>
#include "AbstractAdapter.h"
#include "../Set.h"

using namespace std;

template <class T>
class SetAdapter : public AbstractAdapter<T>
{
private:
    Set<T> container;
    string type = "set";

public:
    SetAdapter() : container{Set<T>()} {}
    SetAdapter(const SetAdapter<T> &other) : container{other.container}
    {
        type = other.type;
    }
    ~SetAdapter() = default;

    void create_working_atd(T list[], size_t size) override
    {
        for (size_t i = 0; i < size; i++)
        {
            container.insert(list[i]);
        }
    }
    void print_container() {
        for(auto var : container)
        {
            cout << var<< " ";
        }
        cout << endl;
    }
    void pre_order_output() override
    {
        cout << "Operation pre_order_output is not defined for set\n";
        print_container();
    }
    void in_order_output() override
    {
        cout << "Operation in_order_output is not defined for set\n";
        print_container();
    }
    void post_order_output() override
    {
        cout << "Operation post_order_output is not defined for set\n";
        print_container();
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
    SetAdapter<T> *clone() override
    {
        SetAdapter<T> *clone = new SetAdapter<T>(*this);
        return clone;
    }
};