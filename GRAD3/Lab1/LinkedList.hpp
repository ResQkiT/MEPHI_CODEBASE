#pragma once

#include "smart_pointers/SharedPtr.hpp"
#include "smart_pointers/UniquePtr.hpp"

template <typename T>
class LinkedList
{
private:
    class Node
    {
    public:
        T data;
        SharedPtr<Node> next;

        Node(const T &data) : data(data) {}
    };

    SharedPtr<Node> head;
    size_t length;

public:
    LinkedList() : length{0} {}

    LinkedList(const LinkedList<T> &list) : length{list.length}
    {
        if (!list.head)
        {
            return;
        }
        head = SharedPtr<Node>(new Node(list.head->data));
        SharedPtr<Node> currentNew = head;
        SharedPtr<Node> currentOld = list.head->next;

        while (currentOld)
        {
            currentNew->next = SharedPtr<Node>(new Node(currentOld->data));
            currentNew = currentNew->next;
            currentOld = currentOld->next;
        }
    }

    LinkedList(const T *items, size_t count) : LinkedList()
    {
        if (count == 0)
            return;

        length = count;
        head = SharedPtr<Node>(new Node(items[0]));
        SharedPtr<Node> currentNew = head;
        for (size_t i = 1; i < count; i++)
        {
            currentNew->next = SharedPtr<Node>(new Node(items[i]));
            currentNew = currentNew->next;
        }
    }

    LinkedList(LinkedList &&other) : head{std::move(other.head)}, length{other.length}
    {
        other.length = 0;
    }

    ~LinkedList() = default;

    size_t size() const
    {
        return length;
    }

    bool is_empty() const
    {
        return length == 0;
    }

    const T &front() const
    {
        if (length == 0)
        {
            throw std::out_of_range("IndexOutOfRange");
        }
        return head->data;
    }

    T &front()
    {
        if (length == 0)
        {
            throw std::out_of_range("IndexOutOfRange");
        }
        return head->data;
    }

    const T &back() const
    {
        if (length == 0)
        {
            throw std::out_of_range("IndexOutOfRange");
        }
        SharedPtr<Node> current = head;
        while (current && current->next)
        {
            current = current->next;
        }
        return current->data;
    }

    T &back()
    {
        if (length == 0)
        {
            throw std::out_of_range("IndexOutOfRange");
        }
        SharedPtr<Node> current = head;
        while (current && current->next)
        {
            current = current->next;
        }
        return current->data;
    }

    T &get(size_t index)
    {
        if (index >= length)
        {
            throw std::out_of_range("IndexOutOfRange");
        }
        SharedPtr<Node> current = head;
        for (size_t i = 0; i < index; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

    const T &get(size_t index) const
    {
        if (index >= length)
        {
            throw std::out_of_range("IndexOutOfRange");
        }
        SharedPtr<Node> current = head;
        for (size_t i = 0; i < index; ++i)
        {
            current = current->next;
        }
        return current->data;
    }
    UniquePtr<LinkedList<T>> get_sublist(size_t begin_index, size_t end_index) const
    {
        if (begin_index > end_index)
            throw new std::runtime_error("Invalid indexes");

        UniquePtr<LinkedList<T>> sublist(new LinkedList<T>());
        SharedPtr<Node> currentOld = head;

        for (size_t i = 0; i < begin_index; i++)
        {
            currentOld = currentOld->next;
        }

        sublist->head = SharedPtr<Node>(new Node(currentOld->data));
        SharedPtr<Node> currentNew = sublist->head;
        currentOld = currentOld->next;

        for (size_t i = begin_index + 1; i < end_index; ++i)
        {
            currentNew->next = SharedPtr<Node>(new Node(currentOld->data));
            currentNew = currentNew->next;
            currentOld = currentOld->next;
        }
        sublist->length = end_index - begin_index;
        return sublist;
    }

    void push_back(const T &item)
    {
        SharedPtr<Node> newNode(new Node(item));
        if (!head)
        {
            head = newNode;
        }
        else
        {
            SharedPtr<Node> current = head;
            while (current->next)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        length++;
    }

    void push_front(const T &item)
    {
        SharedPtr<Node> newNode(new Node(item));
        if (head)
        {
            newNode->next = head;
        }
        head = newNode;
        length++;
    }

    void insert_at(const T &item, size_t index)
    {
        if (index > length)
        {
            throw std::out_of_range("IndexOutOfRange");
        }
        if (index == 0)
        {
            push_front(item);
            return;
        }
        SharedPtr<Node> current = head;
        for (size_t i = 0; i < index - 1; ++i)
        {
            current = current->next;
        }
        SharedPtr<Node> newNode(new Node(item));
        newNode->next = current->next;
        current->next = newNode;
        length++;
    }

    T pop_front()
    {
        if (is_empty())
            throw std::out_of_range("List is empty");

        length--;
        T temp = T(head->data);
        SharedPtr<Node> newHead = head->next;
        head = newHead;

        return temp;
    }
};
