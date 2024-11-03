#include <iostream>
#include <algorithm>
#include <string.h>

#include "../../GRAD2/Lab2/DynamicArray.h"
#include "sorters/BubbleSorter.hpp"
#include "sorters/InsertionSorter.hpp"
#include "sorters/CountingSorter.hpp"
#include "sorters/MergeSorter.hpp"
#include "sorters/QuickSorter.hpp"
#include "tests.h"

using namespace std;   

struct Person
{
    string name;
    int age;
    friend std::ostream &operator<<(std::ostream &os, const Person &p);
};

std::ostream &operator<<(std::ostream &os, const Person &p)
{
    os << p.name << " " << p.age << '\n';
    return os;
}

int main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "-t") == 0) { // сравнение строк
        run_tests(std::cout);
        return 0;
    } 
    
    //TODO: некоторые сортировки не работают с Person, исправьте это
    DynamicArray<Person> array({Person("Vasya", 20), Person("Petya", 30), Person("Kolya", 25), Person("Vanya", 15), Person("Dima", 40)});
    QuickSorter<Person> sorter;

    sorter.sort(array.begin(), array.end(), [](Person a, Person b) { return a.age - b.age; });
    
    for (auto b: array){
        cout << b << " ";
    }

    return 0;
}
