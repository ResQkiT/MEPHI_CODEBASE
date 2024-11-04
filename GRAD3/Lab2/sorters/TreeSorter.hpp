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

template<class T>
class TreeSorter : public ISorter<T> {
private:


public:
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<bool(const T&, const T&)> comp = std::less<T>()) override {
        
        //ужасный костыль, но без него надо перелопачевать все дерево из 4 лабораторки прошлого семестра
        int magic_constant = comp(0, 1) ? 1 : -1; //если компаратор сравнивает по возрастанию, то magic_constant = 1, иначе -1

        BinaryTree<T> tree;
    
        for (auto it = begin; it != end; ++it) {
            tree.insert(*it * magic_constant); //вставляем элемент в дерево, умноженный на magic_constant
        }

        DynamicArraySequence<T> sortedArray;
        tree.in_order(sortedArray);

        for(auto it = sortedArray.begin(); it != sortedArray.end(); ++it) {
            *it *= magic_constant; //возвращаем элементы в исходное состояние
        }

        std::copy(sortedArray.begin(), sortedArray.end(), begin);

    }
};