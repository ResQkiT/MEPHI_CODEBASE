#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility> 

#include "../../GRAD2/Lab2/DynamicArray.h"

template <typename T>
class PriorityQueue {
private:
    struct Element {
        T value;
        int priority;

        Element() = default;
        
        Element(T v, int p) : value(std::move(v)), priority(p) {}

        bool operator>(const Element& other) const {
            return priority > other.priority; 
        }
    };
    DynamicArray<Element> data;

public:

    void sift_up(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (data[index] > data[parent]) {
                std::swap(data[index], data[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void sift_down(size_t index) {
        size_t size = data.get_size();
        while (true) {
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;
            size_t largest = index;

            if (left < size && data[left] > data[largest]) {
                largest = left;
            }
            if (right < size && data[right] > data[largest]) {
                largest = right;
            }
            if (largest != index) {
                std::swap(data[index], data[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    void push(const T& value, int priority) {
        data.push_back({value, priority}); 
        sift_up(data.get_size() - 1); 
    }

    void pop() {
        if (data.empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        std::swap(data[0], data[data.get_size() - 1]);
        data.pop_back();
        sift_down(0); 
    }

    const T& top() const {
        if (data.empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        return data[0].value; 
    }

    T pop_min() {
        if (data.empty()) {
            throw std::runtime_error("Priority queue is empty");
        }

        size_t min_index = 0;
        for (size_t i = 1; i < data.get_size(); ++i) {
            if (data[i].priority < data[min_index].priority) {
                min_index = i;
            }
        }

        T min_value = data[min_index].value;

        std::swap(data[min_index], data[data.get_size() - 1]);
        data.pop_back();

        if (min_index < data.get_size()) {
            sift_down(min_index);
        }

        return min_value;
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.get_size();
    }
};