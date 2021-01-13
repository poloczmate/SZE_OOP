#include <iostream>

class BaseClass{
public:
    virtual void print() = 0;
    virtual ~BaseClass() {}
};

class DerivedClass : BaseClass{
public:
    void print() override { 
        std::cout << "abc" << std::endl;
    }
};

int main(){
    BaseClass* bc = new DerivedClass;
    bc->print();
    delete bc;
    
    


    return 0;
}