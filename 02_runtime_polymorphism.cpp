#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double length, breadth;
public:
    Rectangle(double l, double b) : length(l), breadth(b) {}
    double area() const override {
        return length * breadth;
    }
};

class Triangle : public Shape {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}
    double area() const override {
        return 0.5 * base * height;
    }
};

int main() {
    double radius, length, breadth, base, height;

    cout << "Enter circle radius: ";
    cin >> radius;
    cout << "Enter rectangle length and breadth: ";
    cin >> length >> breadth;
    cout << "Enter triangle base and height: ";
    cin >> base >> height;

    Circle circle(radius);
    Rectangle rectangle(length, breadth);
    Triangle triangle(base, height);

    Shape* ptr;

    ptr = &circle;
    cout << "Area of Circle: " << ptr->area() << '\n';

    ptr = &rectangle;
    cout << "Area of Rectangle: " << ptr->area() << '\n';

    ptr = &triangle;
    cout << "Area of Triangle: " << ptr->area() << '\n';

    return 0;
}
