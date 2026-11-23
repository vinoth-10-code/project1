#include <iostream>
#include <cstring>
#include <utility>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

class String {
private:
    char* data;
public:
    String(const char* text = "") {
        data = new char[strlen(text) + 1];
        strcpy(data, text);
    }

    String(const String& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    String(String&& other) noexcept : data(other.data) {
        other.data = nullptr;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            char* temp = new char[strlen(other.data) + 1];
            strcpy(temp, other.data);
            delete[] data;
            data = temp;
        }
        return *this;
    }

    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    void display() const {
        cout << (data ? data : "(empty)") << '\n';
    }

    ~String() {
        delete[] data;
    }
};

template <typename T>
T createString(T&& value) {
    return T(std::forward<T>(value));
}

int main() {
    string input;
    cout << "Enter a string to store: ";
    getline(cin, input);

    String original(input.c_str());

    auto startCopy = high_resolution_clock::now();
    String copied = original;
    auto endCopy = high_resolution_clock::now();

    auto startMove = high_resolution_clock::now();
    String temporary(input.c_str());
    String moved = std::move(temporary);
    auto endMove = high_resolution_clock::now();

    String forwarded = createString(String("Perfect forwarding demonstration"));

    cout << "\nOriginal string: ";
    original.display();
    cout << "Copied string: ";
    copied.display();
    cout << "Moved string: ";
    moved.display();
    cout << "Perfect forwarding result: ";
    forwarded.display();

    cout << "\nCopy operation time: "
         << duration_cast<nanoseconds>(endCopy - startCopy).count()
         << " nanoseconds\n";
    cout << "Move operation time: "
         << duration_cast<nanoseconds>(endMove - startMove).count()
         << " nanoseconds\n";
    return 0;
}
