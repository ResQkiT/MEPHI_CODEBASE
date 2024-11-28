#include <iostream>
#include <string>
#include "HashMap.hpp"

int main(){
    HashMap<std::string, int> map;
    map.add_or_edit("Hello", 3);
    map.add_or_edit("Hello1", 3);
    map.add_or_edit("Hello2", 3);
    map.add_or_edit("Hello3", 3);
    map.add_or_edit("Hello4", 3);
    map.add_or_edit("Hello25", 3);
    map.add_or_edit("Hello36", 3);
    map.add_or_edit("Hello17", 3);
    map.add_or_edit("Hello28", 3);
    map.add_or_edit("Hello83", 3);
    std::cout << map["Hello"];
}