#include <iostream>
#include "../Lab2/Sequence.h"
#include "Comparable.h"
#include "BinaryTree.h"

template<class T>
class AvlTree : public BinaryTree<T>
{
protected:
    class AvlNode : public BinaryTree<T>::BinaryNode
    {
    public:
        int height;

        AvlNode *& get_left() {
            return (AvlNode*&)(this->left);
        }
        AvlNode *& get_right() {
            return (AvlNode*&)this->right;
        }

        void set_left(AvlNode* left_node){
            this->left = left_node;
        }
        void set_right(AvlNode* right_node){
            this->right = right_node;
        }

        AvlNode(const T &element, AvlNode *left, AvlNode *right, int height)
            : BinaryTree<T>::BinaryNode(element, left, right), height{height} {};

        AvlNode(const T &element)
            : BinaryTree<T>::BinaryNode(element, nullptr, nullptr), height{1} {};

        AvlNode(const AvlNode *other)
            : BinaryTree<T>::BinaryNode(other), height{other->height} {}
        ~AvlNode() = default;
    };

    AvlNode *clone(const AvlNode *other)
    {
        if (other == nullptr)
            return nullptr;
        else
            return new AvlNode(other->element, clone(other->get_left()), clone(other->get_right()), other->height);
    }

    int height(AvlNode *head)
    {
        if (head == nullptr)
            return 0;
        return head->height;
    }
    AvlNode *right_rotate(AvlNode *head)
    {
        AvlNode *newhead = head->get_left();
        head->get_left() = newhead->get_right();
        newhead->set_right(head);
        head->height = 1 + std::max(height(head->get_left()), height(head->get_right()));
        newhead->height = 1 + std::max(height(newhead->get_left()), height(newhead->get_right()));
        return newhead;
    }

    AvlNode *left_rotate(AvlNode *head)
    {
        AvlNode *newhead = head->get_right();
        head->set_right(newhead->get_left());
        newhead->set_left(head);
        head->height = 1 + std::max(height(head->get_left()), height(head->get_right()));
        newhead->height = 1 + std::max(height(newhead->get_left()), height(newhead->get_right()));
        return newhead;
    }

    AvlNode * insert(AvlNode *& head,const T& value)
    {
        if (head == nullptr)
        {
            this->size += 1;
            AvlNode *temp = new AvlNode(value);
            return temp;
        }
        if (value < head->element)
            head->set_left(insert(head->get_left(), value));
        else if (value > head->element)
            head->set_right(insert(head->get_right(), value));

        head->height = 1 + std::max(height(head->get_left()), height(head->get_right()));
        int bal = height(head->get_left()) - height(head->get_right());
        if (bal > 1)
        {
            if (value < head->get_left()->element)
            {
                return right_rotate(head);
            }
            else
            {
                head->set_left(left_rotate(head->get_left()));
                return right_rotate(head);
            }
        }
        else if (bal < -1)
        {
            if (value > head->get_right()->element)
            {
                return left_rotate(head);
            }
            else
            {
                head->set_right(right_rotate(head->get_right()));
                return left_rotate(head);
            }
        }
        return head;
    }

    AvlNode *remove(AvlNode *head, const T& value)
    {
        if (head == nullptr)
            return nullptr;
        if (value < head->element)
        {
            head->set_left(remove(head->get_left(), value));
        }
        else if (value > head->element)
        {
            head->set_right(remove(head->get_right(), value));
        }
        else
        {
            AvlNode *r = head->get_right();
            if (head->get_right() == nullptr)
            {
                AvlNode *l = head->get_left();
                delete head;
                this->size--;
                head = l;
            }
            else if (head->get_left() == nullptr)
            {
                delete head;
                this->size--;
                head = r;
            }
            else
            {
                while (r->get_left() != nullptr)
                    r = r->get_left();
                head->element = r->element;
                head->set_right(remove(head->get_right(), r->element));
            }
        }
        if (head == nullptr)
            return head;
        head->height = 1 + std::max(height(head->get_left()), height(head->get_right()));

        int bal = height(head->get_left()) - height(head->get_right());
        if (bal > 1)
        {
            if (height(head->get_left()) >= height(head->get_right()))
            {
                return right_rotate(head);
            }
            else
            {
                head->set_left(left_rotate(head->get_left()));
                return right_rotate(head);
            }
        }
        else if (bal < -1)
        {
            if (height(head->get_right()) >= height(head->get_left()))
            {
                return left_rotate(head);
            }
            else
            {
                head->set_right(right_rotate(head->get_right()));
                return left_rotate(head);
            }
        }
        return head;
    }

public:
    AvlTree() : BinaryTree<T>()
    {
    }
    AvlTree(const AvlTree &other) : BinaryTree<T>(other)
    {
    }
    AvlTree(const T arr[], size_t size)
    {
        for (size_t i = 0; i < size; i++)
        {
            insert(arr[i]);
        }
    }
    
    ~AvlTree() = default;

    void insert(const T& value) override
    {
        this->root = insert((AvlNode *&)this->root, value);
    }
    
    void remove(const T &value) override
    {
        this->root = remove((AvlNode *&)this->root, value);
    }
};
