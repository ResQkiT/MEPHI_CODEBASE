

#include <iostream>
#include <memory>
using namespace std;    


class A{
public:
    A() = default;
    virtual void foo() {
        cout << "A::foo" << endl;
    }
};
class B : public A{
public:
    B() = default;
    void foo() override {
        cout << "B::foo" << endl;
    }
};
int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    a->foo();
    std::shared_ptr<B> b = std::make_shared<B>();
    a = b;
    a->foo();
    b->foo();

    return 0;
}