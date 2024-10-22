#pragma once

#include "smart_pointers/SharedPtr.hpp"

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        T data;
        SharedPtr<Node> next;

        Node(const T& data) : data(data) {}
    };

    SharedPtr<Node> head;
    size_t length;

public:
    LinkedList() :  length{0} {}

    LinkedList(const LinkedList<T>& list) : LinkedList() {
        SharedPtr<Node> current = list.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }

    LinkedList(const T* items, size_t count)  : length{0} {
        for (size_t i = 0; i < count; ++i) {
            push_back(items[i]);
        }
    }

    LinkedList(LinkedList&& other) : head{std::move(other.head)}, length{other.length} {
        other.length = 0;
    }

    ~LinkedList() = default;

    size_t size() const {
        return length;
    }

    bool is_empty() const {
        return length == 0;
    }

    const T& front() const {
        if (length == 0) {
            throw std::out_of_range("IndexOutOfRange");
        }
        return head->data;
    }

    T& front() {
        if (length == 0) {
            throw std::out_of_range("IndexOutOfRange");
        }
        return head->data;
    }

    const T& back() const {
        if (length == 0) {
            throw std::out_of_range("IndexOutOfRange");
        }
        SharedPtr<Node> current = head;
        while (current && current->next) {
            current = current->next;
        }
        return current->data;
    }

    T& back() {
        if (length == 0) {
            throw std::out_of_range("IndexOutOfRange");
        }
        SharedPtr<Node> current = head;
        while (current && current->next) {
            current = current->next;
        }
        return current->data;
    }

    T& get(size_t index){
        if (index < 0 || index >= length) {
            throw std::out_of_range("IndexOutOfRange");
        }
        SharedPtr<Node> current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    
    const T& get(size_t index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("IndexOutOfRange");
        }
        SharedPtr<Node> current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    SharedPtr<LinkedList<T>> get_sublist(size_t begin_index, size_t end_index) const {
        if (begin_index < 0 || begin_index >= length || end_index < 0 || end_index >= length) {
            throw std::out_of_range("IndexOutOfRange");
        }
        SharedPtr<LinkedList<T>> sublist(new LinkedList<T>());
        SharedPtr<Node> current = head;
        for (size_t i = 0; i < end_index; ++i) {
            if (i >= begin_index) {
                sublist->push_back(current->data);
            }
            current = current->next;
        }
        return sublist;
    }

    void push_back(const T& item) {
        SharedPtr<Node> newNode(new Node(item));
        if (!head) {
            head = newNode;
        } else {
            SharedPtr<Node> current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        length++;
    }

    void push_front(const T& item) {
        SharedPtr<Node> newNode(new Node(item));
        if (head) {
            newNode->next = head;
        }
        head = newNode;
        length++;
    }

    void insert_at(const T& item, size_t index) {
        if (index < 0 || index > length) {
            throw std::out_of_range("IndexOutOfRange");
        }
        if (index == 0) {
            push_front(item);
            return;
        }
        SharedPtr<Node> current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        SharedPtr<Node> newNode(new Node(item));
        newNode->next = current->next;
        current->next = newNode;
        length++;
    }

    T pop_front(){
        if(is_empty()) throw std::out_of_range("List is empty");

        T temp = T(head->data);

        SharedPtr<Node> newHead = head->next;
        head = newHead;

        return temp;
    }

};
