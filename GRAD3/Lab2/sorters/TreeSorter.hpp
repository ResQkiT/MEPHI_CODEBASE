#pragma once

#include "ISorter.hpp"
#include "../../../GRAD2/Lab2/DynamicArray.h"
#include "../../../GRAD2/Lab2/DynamicArraySequence.h"
#include "../../../GRAD2/Lab4/BinaryTree.h"
#include <functional>

/*
    Сортировка деревом (Tree Sort)
    Принцип работы:
    1. Вставляем все элементы в бинарное дерево поиска
    2. Выполняем обход дерева в порядке возрастания (in-order traversal)
    3. Копируем отсортированные элементы обратно в массив
*/

template<class T> requires std::is_arithmetic<T>::value 
class TreeSorter : public ISorter<T> {
public:
    void sort(ISorter<T>::Iterator begin, ISorter<T>::Iterator end, ISorter<T>::Comparator comp = std::less<T>()) override {
        
        int magic_constant = comp(0, 1) ? 1 : -1;

        BinaryTree<T> tree;
    
        for (auto it = begin; it != end; ++it) {
            tree.insert(*it * magic_constant);
        }

        DynamicArraySequence<T> sortedArray;
        tree.in_order(sortedArray);

        for(auto it = sortedArray.begin(); it != sortedArray.end(); ++it) {
            *it *= magic_constant; 
        }

        std::copy(sortedArray.begin(), sortedArray.end(), begin);

    }
};