#include <iostream>
#include "../../GRAD2/Lab2/DynamicArray.h"
#include <algorithm>
#include "sorters/BubbleSorter.hpp"
#include "sorters/InsertionSorter.hpp"
#include "sorters/CountingSorter.hpp"
#include "sorters/MergeSorter.hpp"
#include "sorters/QuickSorter.hpp"

using namespace std;   


int main() {
    DynamicArray<int > array({10 , 9, 8, 7, 6, 5, 5, 5, 4, 3, 2, 1, -99});
    QuickSorter<int> sorter;

    sorter.sort(array.begin(), array.end(), sorter.REVERSE);
    
    for (auto b: array){
        cout << b << " ";
    }

    return 0;
}
