#include <iostream>
#include "AvlNode.h"
#include "../Lab2/Sequence.h"
#include "Comparable.h"

template <class T> requires Comparable<T>
class AvlTree
{
private:

    AvlNode<T> *root = nullptr;
    size_t size = 0;

    AvlNode<T> *clone(const AvlNode<T> *other)
    {
        if (other == nullptr)
            return nullptr;
        else
            return new AvlNode<T>(other->element, clone(other->left), clone(other->right), other->height);
    }


    int height(AvlNode<T> *head)
    {
        if (head == nullptr)
            return 0;
        return head->height;
    }
    AvlNode<T> *right_rotate(AvlNode<T> *head)
    {
        AvlNode<T> *newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1 + std::max(height(head->left), height(head->right));
        newhead->height = 1 + std::max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    AvlNode<T> *left_rotate(AvlNode<T> *head)
    {
        AvlNode<T> *newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1 + std::max(height(head->left), height(head->right));
        newhead->height = 1 + std::max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    AvlNode<T> *insert(AvlNode<T> *head, T value)
    {
        if (head == nullptr)
        {
            size += 1;
            AvlNode<T> *temp = new AvlNode<T>(value);
            return temp;
        }
        if (value < head->element)
            head->left = insert(head->left, value);
        else if (value > head->element)
            head->right = insert(head->right, value);

        head->height = 1 + std::max(height(head->left), height(head->right));
        int bal = height(head->left) - height(head->right);
        if (bal > 1)
        {
            if (value < head->left->element)
            {
                return right_rotate(head);
            }
            else
            {
                head->left = left_rotate(head->left);
                return right_rotate(head);
            }
        }
        else if (bal < -1)
        {
            if (value > head->right->element)
            {
                return left_rotate(head);
            }
            else
            {
                head->right = right_rotate(head->right);
                return left_rotate(head);
            }
        }
        return head;
    }

    AvlNode<T> *remove(AvlNode<T> *head, T value)
    {
        if (head == nullptr)
            return nullptr;
        if (value < head->element)
        {
            head->left = remove(head->left, value);
        }
        else if (value > head->element)
        {
            head->right = remove(head->right, value);
        }
        else
        {
            AvlNode<T> *r = head->right;
            if (head->right == nullptr)
            {
                AvlNode<T> *l = head->left;
                delete head;
                size--;
                head = l;
            }
            else if (head->left == nullptr)
            {
                delete head;
                size--;
                head = r;
            }
            else
            {
                while (r->left != nullptr)
                    r = r->left;
                head->element = r->element;
                head->right = remove(head->right, r->element);
            }
        }
        if (head == nullptr)
            return head;
        head->height = 1 + std::max(height(head->left), height(head->right));

        int bal = height(head->left) - height(head->right);
        if (bal > 1)
        {
            if (height(head->left) >= height(head->right))
            {
                return right_rotate(head);
            }
            else
            {
                head->left = left_rotate(head->left);
                return right_rotate(head);
            }
        }
        else if (bal < -1)
        {
            if (height(head->right) >= height(head->left))
            {
                return left_rotate(head);
            }
            else
            {
                head->right = right_rotate(head->right);
                return left_rotate(head);
            }
        }
        return head;
    }

    void make_empty(AvlNode<T> *&target)
    {
        if (target == nullptr)
            return;
        make_empty(target->left);
        make_empty(target->right);
        // на этом этапе оба потомка очищены, можно спокойно удалять
        delete target;
        size--;
        target = nullptr;
    }
    
    AvlNode<T> *find(AvlNode<T> *head, T value)
    {
        if (head == nullptr)
            return nullptr;
        T key = head->element;
        if (key == value)
            return head;
        if (key > value)
            return find(head->left, value);
        if (key < value)
            return find(head->right, value);
    }

    void pre_order(AvlNode<T> *target_node, Sequence<T> &buffer) const
    {
        if (target_node == nullptr)
            return;
        std::cout << target_node->element << " ";
        buffer.append(target_node->element);
        pre_order(target_node->left, buffer);
        pre_order(target_node->right, buffer);
    }
    void in_order(AvlNode<T> *target_node, Sequence<T> &buffer) const
    {
        if (target_node == nullptr)
            return;
        in_order(target_node->left, buffer);
        std::cout << target_node->element << " ";
        buffer.append(target_node->element);
        in_order(target_node->right, buffer);
    }
    void post_order(AvlNode<T> *target_node, Sequence<T> &buffer) const
    {
        if (target_node == nullptr)
            return;

        post_order(target_node->left, buffer);
        post_order(target_node->right, buffer);
        std::cout << target_node->element << " ";
        buffer.append(target_node->element);
    }
    void custom_order(std::string &order, AvlNode<T> *target_node, Sequence<T> &buffer) const
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
    AvlTree() : size{0}, root{nullptr}
    {
    }
    AvlTree(const AvlTree &other) : size{other.size}, root{clone(other.root)}
    {
    }
    AvlTree(const T arr[], size_t size)
    {
        for (size_t i = 0; i < size; i++)
        {
            insert(arr[i]);
        }
    }
    ~AvlTree()
    {
        size = 0;
        make_empty(root);
    }
    size_t get_size()
    {
        return size;
    }
    void insert(T value)
    {
        root = insert(root, value);
    }
    void remove(T value)
    {
        root = remove(root, value);
    }
    void make_empty(){
        make_empty(root);
    }
    AvlNode<T> *find(T value)
    {
        return find(root, value);
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
};
