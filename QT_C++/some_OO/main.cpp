#include <iostream>

class A{
public:
    int pub = 0;
private:
    int priv = 0;
protected:
    int prot = 0;
};

class B : protected A{
public:
    void print(){
        std::cout << pub << prot;
    }

};

int main(){
    A a;
    B b;
    b.print();

    return 0;
}
