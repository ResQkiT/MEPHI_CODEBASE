#include <iostream>

template <typename T>
class Node
{
public:
    T data;
    Node<T> *prev;
    Node<T> *next;

    Node(const T &value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class LinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;
    size_t size;

    void deleteList()
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
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    LinkedList(size_t size, T *data) : head{nullptr}, tail{nullptr}, size{0}
    {
        for (size_t i = 0; i < size; i++)
        {
            this->push_back(data[i]);
        }
    }
    LinkedList(const LinkedList<T> &other) : head(nullptr), tail(nullptr), size(0)
    {
        *this = other; // Use assignment operator to copy the list
    }

    ~LinkedList()
    {
        deleteList();
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    size_t getSize() const
    {
        return size;
    }

    void push_front(const T &value)
    {
        Node<T> *new_node = new Node<T>(value);

        if (isEmpty())
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

        if (isEmpty())
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
        if (isEmpty())
        {
            throw std::out_of_range("List is empty");
        }

        return head->data;
    }

    const T &front() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("List is empty");
        }

        return head->data;
    }

    T &back()
    {
        if (isEmpty())
        {
            throw std::out_of_range("List is empty");
        }

        return tail->data;
    }

    const T &back() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("List is empty");
        }

        return tail->data;
    }

    void pop_front()
    {
        if (isEmpty())
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
        if (isEmpty())
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

    void clear()
    {
        deleteList();
    }

    void print() const
    {
        if (isEmpty())
        {
            std::cout << "List is empty" << std::endl;
            return;
        }

        Node<T> *current = head;
        while (current)
        {
            std::cout << current->data << " ";
            current = current->next;
        }

        std::cout << std::endl;
    }

    LinkedList<T> &operator=(const LinkedList<T> &other)
    {
        if (this != &other)
        { 
            deleteList();
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
};
