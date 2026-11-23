#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>
using namespace std;
using namespace chrono;

template <class T>
class MyStack {
private:
    vector<T> data;
public:
    void push(T value) { data.push_back(value); }
    void pop() {
        if (!data.empty()) data.pop_back();
        else cout << "Stack is empty.\n";
    }
    bool empty() const { return data.empty(); }
    T top() const { return data.back(); }
};

template <class T>
class MyQueue {
private:
    vector<T> data;
    size_t frontIndex = 0;
public:
    void enqueue(T value) { data.push_back(value); }
    void dequeue() {
        if (frontIndex < data.size()) frontIndex++;
        else cout << "Queue is empty.\n";
    }
    bool empty() const { return frontIndex >= data.size(); }
    T front() const { return data[frontIndex]; }
};

int main() {
    int n, value;
    cout << "How many integer values do you want to enter? ";
    cin >> n;
    if (n <= 0) {
        cout << "Please enter a positive count.\n";
        return 0;
    }

    MyStack<int> customStack;
    MyQueue<int> customQueue;
    stack<int> stlStack;
    queue<int> stlQueue;

    cout << "Enter " << n << " integers:\n";
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        cin >> value;
        customStack.push(value);
        customQueue.enqueue(value);
        stlStack.push(value);
        stlQueue.push(value);
    }
    auto inserted = high_resolution_clock::now();

    cout << "\nCustom stack top: " << customStack.top() << '\n';
    cout << "Custom queue front: " << customQueue.front() << '\n';

    while (!customStack.empty()) customStack.pop();
    while (!customQueue.empty()) customQueue.dequeue();
    while (!stlStack.empty()) stlStack.pop();
    while (!stlQueue.empty()) stlQueue.pop();

    auto finished = high_resolution_clock::now();

    cout << "\nInput and insertion time: "
         << duration_cast<microseconds>(inserted - start).count()
         << " microseconds\n";
    cout << "Deletion time: "
         << duration_cast<microseconds>(finished - inserted).count()
         << " microseconds\n";
    cout << "Custom template stack, queue and STL containers tested.\n";
    return 0;
}
