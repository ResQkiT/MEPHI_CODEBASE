#pragma once
#include <stddef.h>
#include <string>

template <class T>
class AbstractAdapter
{
public:
    virtual ~AbstractAdapter() = default;
    virtual void create_working_atd(T list[], size_t size) = 0;
    virtual void pre_order_output() = 0;
    virtual void in_order_output() = 0;
    virtual void post_order_output() = 0;
    virtual void insert(const T &value) = 0;
    virtual void remove(const T &value) = 0;
    virtual void find(const T& value) = 0;
    virtual std::string &get_type() = 0;
    virtual AbstractAdapter<T> *clone() = 0;
};