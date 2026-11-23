#include <iostream>
#include <memory>
using namespace std;

class Resource {
public:
    Resource() { cout << "Resource acquired.\n"; }
    ~Resource() { cout << "Resource released.\n"; }
    void use() { cout << "Resource is being used.\n"; }
};

class MySmartPointer {
private:
    Resource* ptr;
public:
    explicit MySmartPointer(Resource* p) : ptr(p) {}
    ~MySmartPointer() {
        delete ptr;
        cout << "Manual smart pointer destroyed.\n";
    }
    Resource* operator->() { return ptr; }

    MySmartPointer(const MySmartPointer&) = delete;
    MySmartPointer& operator=(const MySmartPointer&) = delete;
};

int main() {
    cout << "----- Manual RAII Smart Pointer -----\n";
    {
        MySmartPointer smartPtr(new Resource());
        smartPtr->use();
    }

    cout << "\n----- unique_ptr -----\n";
    {
        unique_ptr<Resource> uniquePtr = make_unique<Resource>();
        uniquePtr->use();
    }

    cout << "\n----- shared_ptr -----\n";
    {
        shared_ptr<Resource> sharedPtr1 = make_shared<Resource>();
        shared_ptr<Resource> sharedPtr2 = sharedPtr1;
        sharedPtr1->use();
        cout << "Shared pointer count: " << sharedPtr1.use_count() << '\n';
    }

    cout << "\nProgram completed.\n";
    return 0;
}
