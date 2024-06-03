#pragma once
#include <iostream>

template<class T>
concept Comparable = requires(T a, T b){
    a < b;
    a > b;
};

template <class T> requires Comparable<T>
class BinaryTree 
{
private:
    struct BinaryNode
    {
        T element;
        BinaryNode *leftNode;
        BinaryNode *rightNode;

        BinaryNode(const T &element, BinaryNode *left, BinaryNode *right)
            : element{element}, leftNode{left}, rightNode{right} {};

        BinaryNode(const T &element)
            : element{element}, leftNode{nullptr}, rightNode{nullptr} {};

        BinaryNode(const BinaryNode *target_node)
            : element{target_node->element}, leftNode{target_node->leftNode}, rightNode{target_node->rightNod}{}
    };

    size_t size;
    BinaryNode *root;

    BinaryNode *clone(const BinaryNode *other)
    {
        if (other == nullptr)
            return nullptr;
        else
            return new BinaryNode(other->element, clone(other->leftNode), clone(other->rightNode));
    }

    void insert(const T &value, BinaryNode *&target)
    {

        if (target == nullptr)
        {
            size++;
            target = new BinaryNode(value);
        }
        else if (value < target->element)
        {
            insert(value, target->leftNode);
        }
        else if (value > target->element)
        {
            insert(value, target->rightNode);
        }
        // не вставляем повторяющиеся данные
    }

    void remove(const T &theElement, BinaryNode *&target)
    {
        if (target == nullptr)
            return;
        else
        {
            if (theElement < target->element)
            {
                remove(theElement, target->leftNode);
            }
            else if (theElement > target->element)
            {
                remove(theElement, target->rightNode);
            }
            else if (target->leftNode != nullptr && target->rightNode != nullptr)
            {
                // свайп минимального элемента и текущего
                target->element = find_min(target->rightNode)->element;
                remove(target->element, target->rightNode);
            }
            else
            { // наподумать
                BinaryNode *old_node = target;
                target = (nullptr != target->leftNode) ? target->leftNode : target->rightNode;
                size--;
                delete old_node;
            }
        }
    }

    void make_empty(BinaryNode *&target)
    {
        if (target != nullptr)
        {
            make_empty(target->leftNode);
            make_empty(target->rightNode);
            size--;
            delete target;
        }
        target = nullptr;
    }

    bool find(const T &value, BinaryNode *target) const
    {
        if (target == nullptr)
            return false;
        else if (value < target->element)
        {
            return find(value, target->leftNode);
        }
        else if (value > target->element)
        {
            return find(value, target->rightNode);
        }
        else
        { // value == target->element
            return true;
        }
    }
    BinaryNode *find_min(BinaryNode *target_node) const
    {
        if (nullptr != target_node)
        {
            while (nullptr != target_node->leftNode)
            {
                target_node = target_node->leftNode;
            }
        }

        return target_node;
    }
    BinaryNode *find_max(BinaryNode *target_node) const
    {
        if (nullptr != target_node)
        {
            while (nullptr != target_node->rightNode)
            {
                target_node = target_node->rightNode;
            }
        }
        return target_node;
    }
    void pre_order(BinaryNode *target_node) const
    {
        if(target_node != nullptr){
            std::cout << target_node->element << " ";
            pre_order(target_node->leftNode);
            pre_order(target_node->rightNode);
        }
    }
    void in_order(BinaryNode *target_node) const
    {
        if(target_node != nullptr){
            in_order(target_node->leftNode);
            std::cout << target_node->element << " ";
            in_order(target_node->rightNode);
        }
    }
    void post_order(BinaryNode *target_node) const
    {
        if(target_node != nullptr){
            post_order(target_node->leftNode);
            post_order(target_node->rightNode);
            std::cout << target_node->element << " ";
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
        root = new BinaryNode(theElement);
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
    bool is_empty() const{
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

    void pre_order() const
    {
        pre_order(root);
        std::cout << '\n';
    }

    void in_order() const
    {
        in_order(root);
        std::cout << '\n';
    }

    void post_order() const
    {
        post_order(root);
        std::cout << '\n';
    }
    void merge(const BinaryTree<T> & other){
        BinaryTree<T> copy(other);
        while (!copy.is_empty())
        {
            T temp = copy.find_min(copy.root)->element;
            copy.remove(temp);
            this->insert(temp);
        }
    }
};