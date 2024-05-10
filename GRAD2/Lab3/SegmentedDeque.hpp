#pragma once
#include <iostream>
#include <deque>
#include <vector>
#include "Deque.hpp"
#include "../Lab2/Sequence.h"
#include "../Lab2/LinkedListSequence.h"

template <class T, template <class> class InnerContainer = LinkedListSequence>
    requires std::derived_from<InnerContainer<T>, Sequence<T>>
class SegmentedDeque {
private:
    Deque<InnerContainer<T>> buffer;
    size_t segment_size; 

public:
\
    SegmentedDeque(size_t segment_size) : buffer{Deque<InnerContainer<T>>()},segment_size{segment_size} 
    {
        buffer.push_back(InnerContainer<T>());
    }
    SegmentedDeque(T data[], size_t size, size_t segment_size) : buffer{Deque<InnerContainer<T>>()}, segment_size{segment_size}{
        buffer.push_back(InnerContainer<T>());
        for (size_t i = 0; i < size; i++)
        {
            push_back(data[i]);
        }
    }
    
    SegmentedDeque(const SegmentedDeque<T, InnerContainer> & other) : buffer{Deque<InnerContainer<T>>()}, segment_size{other.segment_size} {
        for (size_t i = 0; i < other.get_segment_size(); i++)
        {
            buffer.push_back(InnerContainer<T>(other.buffer[i]));
        }
    }

    void push_back(const T& value) {
        if (buffer.back().get_length() < segment_size) {
            buffer.back().append(value);
            std::cout << buffer.back().get_first() << std::endl;
        } else {
            std::cout <<"shit";
            InnerContainer<T> container;
            container.append(value);
            buffer.push_back(container);
            std::cout << buffer.back().get_last() << std::endl;
        }

    }

    void push_front(const T& value) {

        if (buffer.front().get_length() < segment_size) {
            buffer.front().prepend(value);
        } else {
            InnerContainer<T> container = InnerContainer<T>(new T[]{value} , 1);
            buffer.push_front(container);
        }
    }
    size_t get_segment_size(){
        return segment_size;
    }
    size_t number_of_segments(){
        return buffer.size();
    }
    T& back(){
        if (buffer.empty()) {
            throw std::out_of_range("SegmentedDeque is empty");
        }
        return buffer.front().get_last();
    }
    T& front(){
        if (buffer.empty()) {
            throw std::out_of_range("SegmentedDeque is empty");
        }
        return buffer.front().get_first();
    }
    T& get(size_t index){
        return buffer[index / segment_size].get(index%segment_size);
    }
    T& operator[](size_t index){
        return get(index);
    }
    size_t size(){
        if (number_of_segments() == 0)
        {
            return 0;
        }
        
        if(number_of_segments() == 1){
            return buffer.front().get_length();
        }else if(number_of_segments() == 2){
            return buffer.front().get_length() + buffer.back().get_length();
        }else{
            return (number_of_segments() - 2) * get_segment_size() + \
            buffer.front().get_length() + buffer.back().get_length();
        }
    }
    T pop_back() {
        if (buffer.empty()) {
            throw std::out_of_range("SegmentedDeque is empty");
        }

        T value = buffer.back().get_last();
        buffer.back().pop_back();
        if (buffer.back().is_empty()) {
            buffer.pop_back();
        }
        return value;
    }

    T pop_front() {
        if (buffer.empty()) {
            throw std::out_of_range("SegmentedDeque is empty");
        }

        T value = buffer.front().get_first();
        buffer.front().pop_front();
        if (buffer.front().is_empty()) {
            buffer.pop_front();
        }
        return value;
    }
};