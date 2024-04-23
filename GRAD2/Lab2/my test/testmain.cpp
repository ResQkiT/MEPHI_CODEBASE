#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
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

void foo(int a) {
   

}
int main(){
    A a(5);    
    try
    {
        foo(2);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return 0;
}