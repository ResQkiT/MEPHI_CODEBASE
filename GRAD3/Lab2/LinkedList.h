/*
 * Произошёл рефакторинг LinkedList. Во время 3 лабы и более тщательного изучения АТД,
 * возникло желание полностью попробовать реализовать все преимущества LinkedList в плане операций,
 * и ради этого была сделана самодельная реализация std::shared_ptr и std::weak_ptr и внедрена в LinkedList.
 * На left ноды используется weak_ptr для отсуствия циклических ссылок. В LinkedListIterator используется
 * shared_ptr для безопасного обхода списка.
 */

#pragma once
#include <stdexcept>
#include "SharedPtr.h" // вроде-бы рабочий аналог std::shared_ptr.
#include "WeakPtr.h" // вроде-бы рабочий аналог std::weak_ptr.

template <typename T>
class LinkedListIterator;

template<typename T>
class MutableSequence;

template<typename T>
class ImmutableSequence;

template<typename T>
class Node {
public:
    T data;
    WeakPtr<Node<T>> left;
    SharedPtr<Node<T>> right;

    explicit Node(const T &value) : data{value}, left{}, right{nullptr} {}
};


template<class T>
class LinkedList {
private:
    SharedPtr<Node<T>> first;
    SharedPtr<Node<T>> last;
    int size;

    void checkIndex(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
    }

    // Объявление дружбы с LinkedListIterator
    friend class LinkedListIterator<T>;

    // Внутренний метод для получения первого узла
    SharedPtr<Node<T>> getFirstNodeForIterator() const {
        return first;
    }

    void clear() {
        first.reset();  // Обнуляем SharedPtr, чтобы уменьшить счетчики ссылок
        last.reset();
        size = 0;
    }

public:
    LinkedList() : first{nullptr}, last{nullptr}, size{0} {}

    LinkedList(T *items, int size) : first{nullptr}, last{nullptr}, size{0} {
        for (int i = 0; i < size; ++i) {
            append(items[i]);
        }
    }

    LinkedList(const LinkedList<T>& list) : first{nullptr}, last{nullptr}, size{0} {
        SharedPtr<Node<T>> current = list.first;
        while (current) {
            append(current->data); // append увеличивает счетчики ссылок
            current = current->right;
        }
    }

    explicit LinkedList(const MutableSequence<T> *sequence) : first{nullptr}, last{nullptr}, size{0} {
        for (int i = 0; i < sequence->getLength(); ++i) {
            append(sequence->get(i));
        }
    }

    explicit LinkedList(const ImmutableSequence<T> *sequence) : first{nullptr}, last{nullptr}, size{0} {
        for (int i = 0; i < sequence->getLength(); ++i) {
            append(sequence->get(i));
        }
    }

    ~LinkedList() {
        // Деструктор не требуется, так как SharedPtr
        // автоматически освободит first и last,
        // а вместе с ними и все остальные узлы списка.
    }

    bool isEmpty() const {
        return size == 0;
    }

    T &getFirst() const {
        if (!first) {
            throw std::out_of_range("ListIsEmpty");
        }
        return first->data;
    }

    T &getLast() const {
        if (!last) {
            throw std::out_of_range("ListIsEmpty");
        }
        return last->data;
    }

    T &getByIndex(int index) const {
        checkIndex(index);
        SharedPtr<Node<T>> temp = first;
        for (int i = 0; i < index; ++i) {
            temp = temp->right;
        }
        return temp->data;
    }

    LinkedList<T> *getSubList(int startIndex, int endIndex) const {
        checkIndex(startIndex);
        checkIndex(endIndex);
        if (startIndex > endIndex) {
            throw std::invalid_argument("startIndex cannot be greater than endIndex");
        }
        auto* subList = new LinkedList<T>();
        SharedPtr<Node<T>> current = first;

        for (int i = 0; i < startIndex; ++i) {
            current = current->right;
        }

        for (int i = startIndex; i <= endIndex; ++i) {
            subList->append(current->data);
            current = current->right;
        }

        return subList;
    }

    int getLength() const {
        return size;
    }

    void append(const T &value) {
        auto newNode = MakeShared<Node<T>>(value);
        if (isEmpty()) {
            first = newNode;
            last = newNode;
        } else {
            last->right = newNode;
            newNode->left = WeakPtr<Node<T>>(last);  // !!!  Используем конструктор WeakPtr
            last = newNode;
        }
        size++;
    }

    void prepend(const T &value) {
        auto newNode = MakeShared<Node<T>>(value);
        if (!first) {
            first = newNode;
            last = newNode;
        } else {
            first->left = WeakPtr<Node<T>>(newNode);
            newNode->right = first;
            first = newNode;
        }
        size++;
    }

    void insertAt(int index, const T &value) {
        checkIndex(index);
        if (index == 0) {
            prepend(value);
        } else if (index == size) {
            append(value);
        } else {
            Node<T>* temp = first.get();
            for (int i = 0; i < index - 1; ++i) {
                temp = temp->right.get();
            }
            auto newNode = MakeShared<Node<T>>(value);
            newNode->right = temp->right;
            newNode->left = WeakPtr<Node<T>>(); // !!! Исправлено:  обнуляем WeakPtr
            if (temp->right.get()) {
                temp->right.get()->left = WeakPtr<Node<T>>(newNode);
            }
            temp->right = newNode;
            size++;
        }
    }

    void removeAt(int index) {
        checkIndex(index);
        if (index == 0) {
            // Удаление первого элемента
            first = first->right;
            if (first.get()) {
                first->left.reset();
            } else {
                last.reset();
            }
        } else if (index == size - 1) {
            // Удаление последнего элемента
            last = last->left;
            if (last.get()) {
                last->right.reset();
            } else {
                first.reset();
            }
        } else {
            Node<T>* current = first.get();
            for (int i = 0; i < index; ++i) {
                current = current->right.get();
            }

            // Обнуляем SharedPtr в удаляемом узле
            if (current->left) {
                current->left->right.reset();
            }
            if (current->right) {
                current->right->left.reset();
            }

            if (index == 0) {
                first = current->right;
            } else if (index == size - 1) {
                last = current->left;
            } else {
                current->left->right = current->right;
                current->right->left = current->left;
            }
            size--;
        }
    }

    LinkedList<T>* concatenate(const LinkedList<T>& other) {
        if (this->isEmpty()) {
            return new LinkedList<T>(other);
        }

        // Соединяем последний элемент первого списка с первым элементом второго списка
        if(!other.isEmpty()) {
            last->right = other.first;
            other.first->left = WeakPtr<Node<T>>(last);

            size += other.getLength();
        }

        return new LinkedList<T>(*this);
    }

    LinkedList<T>& operator=(const LinkedList<T>& list) {
        if (this != &list) {
            clear();

            Node<T>* temp = list.first.get();
            while (temp) {
                append(temp->data);
                temp = temp->right.get();
            }
        }
        return *this;
    }
};
