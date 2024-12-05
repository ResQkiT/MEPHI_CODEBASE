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

        bool operator<(const Element& other) const {
            return priority < other.priority; 
        }
    };
    
    DynamicArray<Element> data;

public:

    void sift_up(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (data[index] < data[parent]) {
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
            size_t smallest = index;

            if (left < size && data[left] < data[smallest]) {
                smallest = left;
            }
            if (right < size && data[right] < data[smallest]) {
                smallest = right;
            }
            if (smallest != index) {
                std::swap(data[index], data[smallest]);
                index = smallest;
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

    void update_priority(const T& value, int new_priority) {
        for (size_t i = 0; i < data.get_size(); ++i) {
            if (data[i].value == value) {
                int old_priority = data[i].priority;
                data[i].priority = new_priority;

                if (new_priority < old_priority) {
                    sift_up(i);
                } else {
                    sift_down(i);
                }
                return;
            }
        }
        throw std::runtime_error("Element not found in the priority queue");
    }

    bool contains(const T& value){
        for(const auto& object : data){
            if(object.value == value) return true;
        }
        return false;
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.get_size();
    }

    void print_queue(){
        std::cout << "queue: ";
        for(const auto& object : data){
            std::cout << object.priority << " ";
        }
        std::cout << std::endl;
    }
};
