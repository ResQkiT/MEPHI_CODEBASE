#pragma once
#include <vector>
#include "AvlTree.h"
#include <iterator>

template <class T, template<class> class Container = AvlTree>
class Set
{
private:
    Container<T> tree;

public:
    Set() : tree{Container<T>()} {};

    Set(T arr[], size_t size) : tree(Container<T>(arr, size)) {}

    Set(const Set<T> &other) : tree{other.tree} {};

    size_t size() const
    {
        return tree.get_size();
    }

    void insert(const T &value)
    { 
        tree.insert(value); 
    }

    bool find(const T &value) const
    {
        return tree.find(value);
    }

    void remove(const T &value)
    {
        tree.remove(value);
    }

    Set<T> set_union(Set<T> & other)
    {
        Set<T> res;
        for (T x : tree)
            res.insert(x);
        for (T x : other)
            res.insert(x); 
        return res;
    }

    Set<T> set_intersection(Set<T> &other)
    {
        Set<T> res;
        for (T x : tree)  
            if (other.find(x)) 
                res.insert(x);
        return res;
    }
   
    Set<T> difference(Set<T> &other)
    {
        Set<T> res;
        for (T x : tree)   
            if (!other.find(x)) 
                res.insert(x);
        return res;
    }

    bool is_sub_set(const Set<T> &set) const
    {
        for (T x : tree)
        { 
            if (!set.find(x))
                return false; 
        }
        return true; 
    }

    bool equal(const Set<T> & set) const
    {
        return this->subSet(set) && set.subSet(*this);
    }

    class Iterator
    {
    private:
        typename BinaryTree<T>::Iterator iterator;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        
        Iterator(typename BinaryTree<T>::Iterator iterator) : iterator(iterator) {}
        reference operator*() const
        {
            return *iterator;
        }
        pointer operator->()
        {
            return iterator;
        }
        Iterator &operator++()
        {
            ++iterator;
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
            return a.iterator == b.iterator;
        };
        friend bool operator!=(const Iterator &a, const Iterator &b)
        {
            return a.iterator != b.iterator;
        };
    };
public:
    Iterator begin() const
    {
        return Iterator(tree.begin());
    }
    Iterator end() const
    {
        return Iterator(tree.end());
    }
};