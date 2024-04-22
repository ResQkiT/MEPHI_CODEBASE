#include <iostream>
#include <vector>
class A{
    public:

    virtual A *  getInstance(){
        std::cout << "called A instance" << std::endl;
        return this;
    }

    virtual void call() = 0;
};
class B : public A{
    public:
    B * getInstance() override{
        std::cout << "called B instance" << std::endl;
        return (B*)this;
    }
    void call(){
        std::cout << "class B called" << std::endl;
    }
};
int main(){
    A * a;
    B b;
    a = &b;
    a->getInstance()->call();


    return 0;
}