#include <iostream>
#include <vector>
class B{
public:
    int t;
    B(){
        std::cout << "default b constructor called" << std::endl;
    }
    B(int n){
        std::cout << "B constructor called" << std::endl;
    }
};
class A{
    public:
    B b;
    A(int t) : b{B(t)}{

    }
};
int main(){
    A a(5);    


    return 0;
}