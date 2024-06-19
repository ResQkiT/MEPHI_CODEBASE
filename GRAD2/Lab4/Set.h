#pragma once
#include <vector>
#include "AvlTree.h"
#include <iterator>
#include <string>
#include <sstream>


template <class T, template <class> class Container = AvlTree>
class Set
{
private:
    Container<T> tree;

public:
    Set() : tree{Container<T>()} {};

    Set(T arr[], size_t size) : tree(Container<T>(arr, size)) {}

    Set(const Set<T, Container> &other) : tree{other.tree} {};

    Set(const std::string &str) : tree{Container<T>()}
    {
        std::stringstream iss(str);
        T temp;
        while (iss >> temp)
            tree.insert(temp);
    }

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

    void clear()
    {
        this->tree.make_empty();
    }

    void remove(const T &value)
    {
        tree.remove(value);
    }

    std::string to_string() const
    {
        std::vector<T> elements;
        std::stringstream iss;
        for (T var : *this)
        {
            iss << var << " ";
        }
        return iss.str();
    }

    Set<T, Container> &set_union(Set<T, Container> &other)
    {
        for (T x : other)
        {
            this->insert(x);
        }

        return *this;
    }

    Set<T, Container> &set_intersection(Set<T, Container> &other)
    {
        Set<T, Container> copy(*this);
        this->clear();

        for (T x : copy)
            if (other.find(x))
                this->insert(x);

        return *this;
    }

    Set<T, Container> &set_difference(Set<T, Container> &other)
    {
        Set<T, Container> copy(*this);
        this->clear();

        for (T x : copy)
            if (!other.find(x))
                this->insert(x);

        return *this;
    }

    bool is_sub_set(const Set<T, Container> &set) const
    {
        for (T x : tree)
        {
            if (!set.find(x))
                return false;
        }
        return true;
    }

    bool equal(const Set<T, Container> &set) const
    {
        return this->subSet(set) && set.subSet(*this);
    }

    Set<T, Container>& map(std::function<T(T)> function) {
        this->tree.map(function);
        return *this;
    }

    Set<T, Container>& where(std::function<bool(T)> function) {
        this->tree.where(function);
        return *this;
    }

    T reduce(std::function<T(T, T)> function) {
        return tree.reduce(function);
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