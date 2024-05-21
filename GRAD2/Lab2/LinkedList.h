#pragma once
#include <iostream>

template <typename T>
class Node
{
public:
    T data;
    Node<T> *prev;
    Node<T> *next;

    Node(const T &value) : data{value}, prev{nullptr}, next{nullptr} {}
};

template <typename T>
class LinkedList : public IConcatenable<T>
{

private:
    Node<T> *head;
    Node<T> *tail;
    size_t size;

    void delete_list()
    {
        Node<T> *current = head;
        while (current)
        {
            Node<T> *next = current->next;
            delete current;
            current = next;
        }

        head = tail = nullptr;
        size = 0;
    }

public:
    LinkedList() : head{nullptr}, tail{nullptr}, size{0} {}

    LinkedList(T *data, size_t size) : head{nullptr}, tail{nullptr}, size{0}
    {
        if (size < 0)
            throw std::invalid_argument("Cannot create LinkedList with negative size");
        if (data == nullptr)
            throw std::invalid_argument("LinkedList Constructor must take not null arguments");
        for (size_t i = 0; i < size; i++)
        {
            this->push_back(data[i]);
        }
    }

    LinkedList(const LinkedList<T> &other) : head{nullptr}, tail{nullptr}, size{0}
    {
        *this = other;
    }
    LinkedList(LinkedList<T> &&other) : size{std::move(other.size)}, head{std::move(other.head)}, tail{std::move(other.tail)}
    {
        other.size = 0;
        other.head = nullptr;
        other.tail = nullptr;
    }

    ~LinkedList()
    {
        delete_list();
    }

    bool is_empty() const
    {
        return head == nullptr;
    }

    size_t get_size() const override
    {
        return size;
    }

    void push_front(const T &value)
    {
        Node<T> *new_node = new Node<T>(value);

        if (is_empty())
        {
            head = tail = new_node;
        }
        else
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }

        size++;
    }

    void push_back(const T &value) override
    {
        Node<T> *new_node = new Node<T>(value);

        if (is_empty())
        {
            push_front(value);
            return;
        }

        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
        size++;
    }

    T &front()
    {
        if (is_empty())
            throw std::out_of_range("List is empty");

        return head->data;
    }

    const T &front() const
    {
        if (is_empty())
            throw std::out_of_range("List is empty");

        return head->data;
    }

    T &back()
    {
        if (is_empty())
            throw std::out_of_range("List is empty");

        return tail->data;
    }

    const T &back() const
    {
        if (is_empty())
            throw std::out_of_range("List is empty");

        return tail->data;
    }

    void pop_front()
    {
        if (is_empty())
            throw std::out_of_range("List is empty");

        Node<T> *temp = head;
        if (size == 1)
        {
            head = tail = nullptr;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
        size--;
    }

    void pop_back()
    {
        if (is_empty())
            throw std::out_of_range("List is empty");

        Node<T> *temp = tail;
        if (size == 1)
        {
            pop_front();
            return;
        }

        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        size--;
    }

    T &get(size_t index) override
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Out of range");
        if (is_empty())
            throw std::out_of_range("List is empty");
        auto it = begin();
        for (int i = 0; i < index; it++){
            i++;
        }
        return *it;
    }
    void clear()
    {
        delete_list();
    }

    LinkedList<T> &operator=(const LinkedList<T> &other)
    {
        if(this == &other){
            return *this;
        }

        delete_list();
        head = other.head;
        tail = other.tail;
        size = other.size;

        if (head)
        {
            Node<T> *otherCurr = other.head;
            Node<T> *newCurr = new Node<T>(otherCurr->data);
            head = newCurr;

            Node<T> *prev = nullptr;
            while (otherCurr->next)
            {
                otherCurr = otherCurr->next;
                newCurr->next = new Node<T>(otherCurr->data);
                newCurr = newCurr->next;
                prev = newCurr;
            }
            tail = prev;
            Node<T> *curr = head;
            while (curr)
            {
                if (curr->next)
                {
                    curr->next->prev = curr;
                }
                curr = curr->next;
            }
        }

        return *this;
    }
    LinkedList<T> &operator+=(LinkedList<T> &other)
    {
        return *concat(&other);
    }

    LinkedList<T> &move_to_end(LinkedList<T> &other)
    {
        other.head->prev = tail;

        tail->next = std::move(other.head);
        other.head = nullptr;

        tail = std::move(other.tail);
        other.tail = nullptr;
        size += other.size;
        other.size = 0;

        return *this;
    }
    class Iterator
    {
    private:
        Node<T> *cur;

    public:
        Iterator(Node<T> *head) : cur(head) {}

        Iterator &operator++()
        {
            if (cur != nullptr)
            {
                cur = cur->next;
            }
            return *this;
        }

        Iterator &operator++(int)
        {
            if (cur != nullptr)
            {
                cur = cur->next;
            }
            return *this;
        }

        Iterator &operator--()
        {
            if (cur != nullptr)
            {
                cur = cur->prev;
            }
            return *this;
        }
        Iterator &operator--(int)
        {
            if (cur != nullptr)
            {
                cur = cur->prev;
            }
            return *this;
        }

        bool operator!=(const Iterator &other) const
        {
            return cur != other.cur;
        }

        bool operator==(const Iterator &other) const
        {
            return cur == other.cur;
        }

        T &operator*()
        {
            if (cur != nullptr)
                return cur->data;
            else
                throw std::runtime_error("Iterator refer to null");
        }

        T *operator->()
        {
            return &cur->data;
        }
    };

    Iterator begin()
    {
        return Iterator(head);
    }

    Iterator end()
    {
        if (tail == nullptr)
        {
            return Iterator(nullptr);
        }

        return Iterator(tail->next);
    }
};
