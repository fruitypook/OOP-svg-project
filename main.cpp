#include <iostream>

struct Point {
    int x, y;
};

class Shape {};
class Line : public Shape {};
class Rectangle : public Shape {};
class Circle : public Shape {};

int main() { std::cout << "hai!"; }