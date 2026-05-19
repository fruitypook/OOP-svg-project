#include <cassert>
#include <iostream>

// {0,0} is top left corner
struct Point {
    unsigned x, y;
};
bool operator==(const Point& p1, const Point& p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}
bool operator!=(const Point& p1, const Point& p2) { return !(p1 == p2); }

class Shape {
   public:
    Shape(const Point& p) : anchor(p) {}

   protected:
    Point anchor;
};

// anchor is other end of line
class Line : public Shape {
   public:
    Line(const Point& p1, const Point& p2) : Shape(p1), end(p2) {
        assert(p1 != p2);
    }

   private:
    Point end;
};

// anchor is other end of diagonal
class Rectangle : public Shape {
   public:
   private:
    Point end;
};

// anchor is centre
class Circle : public Shape {
   public:
   private:
    unsigned radius;
};

int main() {
    std::cout << "hai!";
    //
}