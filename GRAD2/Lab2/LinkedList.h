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
class LinkedList
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
    explicit LinkedList() : head{nullptr}, tail{nullptr}, size{0} {}

    explicit LinkedList(T *data, size_t size) : head{nullptr}, tail{nullptr}, size{0}
    {
        for (size_t i = 0; i < size; i++)
        {
            this->push_back(data[i]);
        }
    }

    LinkedList(const LinkedList<T> &other) : head{nullptr}, tail{nullptr}, size{0}
    {
        *this = other;
    }
    LinkedList(LinkedList<T> && other): size{std::move(other.size)} , head{std::move(other.head)}, tail{std::move(other.tail)}{
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

    size_t get_size() const
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

    void push_back(const T &value)
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
        {
            throw std::out_of_range("List is empty");
        }

        return head->data;
    }

    const T &front() const
    {
        if (is_empty())
        {
            throw std::out_of_range("List is empty");
        }

        return head->data;
    }

    T &back()
    {
        if (is_empty())
        {
            throw std::out_of_range("List is empty");
        }

        return tail->data;
    }

    const T &back() const
    {
        if (is_empty())
        {
            throw std::out_of_range("List is empty");
        }

        return tail->data;
    }

    void pop_front()
    {
        if (is_empty())
        {
            throw std::out_of_range("List is empty");
        }

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
        {
            throw std::out_of_range("List is empty");
        }

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

    T & get(size_t index){
        auto it = begin();
        for (int i = 0; i < index; it++, i++);
        return *it;
    }

    void clear()
    {
        delete_list();
    }

    LinkedList<T> &operator=(const LinkedList<T> &other)
    {
        
        if (this != &other)
        { 
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
        }

        return *this;
    }

    LinkedList<T> & operator+=(LinkedList<T> & other){

        other.head->prev = tail;

        //забираем доступ
        tail->next =std::move(other.head);
        other.head = nullptr;

        tail = std::move(other.tail);
        other.tail = nullptr;
        size+= other.size;

        return *this;
    }

    class Iterator {
    private:
        Node<T>* curr;

    public:
        Iterator(Node<T>* head) : curr(head) {}

        Iterator& operator++() {
            if (curr != nullptr) {
                curr = curr->next;
            }
            return *this;
        }

        Iterator& operator++(int) {
            if (curr != nullptr) {
                curr = curr->next;
            }
            return *this;
        }

        Iterator& operator--() {
            if (curr != nullptr) {
                curr = curr->prev;
            }
            return *this;
        }
        Iterator& operator--(int) {
            if (curr != nullptr) {
                curr = curr->prev;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return curr != other.curr;
        }

        bool operator==(const Iterator& other) const {
            return curr == other.curr;
        }
        
        T& operator*() {
            return curr->data;
        }

        T* operator->() {
            return &curr->data;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        if (tail == nullptr) {
            return Iterator(nullptr);
        }

        return Iterator(tail->next); 
    }
};
