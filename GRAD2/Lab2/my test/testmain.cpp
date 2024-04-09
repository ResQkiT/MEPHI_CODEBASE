#include <iostream>
#include "MyPair.h"
#include "ExtendedPairTypeA.h"
#include "ExtendedPairTypeB.h"
#include "IPair.h"
#include <vector>
int main(){
    std::cout << "Program started" << std::endl;
    ExtendedPairTypeA<int> p1(5, 5);
    ExtendedPairTypeA<double> p2(12.3, -132.9);
    ExtendedPairTypeB<float> p3(21.3, 7.7);
    ExtendedPairTypeB<long long> p4(1e4, -1e5);
    std::vector<IPair> all;
    all.push_back(p1);
    all.push_back(p2);
    all.push_back(p3);
    all.push_back(p4);
    for(auto b : all){
        b.printWork();
    }

    return 0;
}