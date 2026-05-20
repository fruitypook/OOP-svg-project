#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int greatestCommonDivisor(int n1, int n2) {
    int a = std::max(n1, n2), b = std::min(n1, n2);
    while (b != 0) {
        int k = b;
        b = a % b;
        a = k;
    }
    return a;
}

struct RGBColor {
    int r, g, b;
};

// TODO: hex --> rgb conversion (for serialization)
// TODO: word <-> rgb conversion (for de-/serialization)

// {0,0} is top left corner
struct Point {
    unsigned x, y;
};
bool operator==(const Point& p1, const Point& p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}
bool operator!=(const Point& p1, const Point& p2) { return !(p1 == p2); }

double dist(const Point& p1, const Point& p2) {
    int x1 = p1.x, y1 = p1.y,  //
        x2 = p2.x, y2 = p2.y;
    unsigned dx = std::abs(x1 - x2),  //
        dy = std::abs(y1 - y2);
    return std::sqrt(dx * dx + dy * dy);
}
constexpr double eps = 1e-6;

class Shape {
   public:
    Shape(const Point& p, const RGBColor& _fillColor = {0, 0, 0},
          const RGBColor& _borderColor = {0, 0, 0})
        : anchor(p), fillColor(_fillColor), borderColor(_borderColor) {}
    Shape(const Shape& o) = default;

    virtual double perimeter() const = 0;
    virtual double area() const = 0;

    virtual bool isWithin(const Point& p) const = 0;

    virtual void print() const = 0;
    virtual void serialize(std::ostream& os = std::cout) const = 0;

   protected:
    Point anchor;
    RGBColor fillColor, borderColor;
};

// anchor is one end of line
class Line : public Shape {
   public:
    Line(const Point& p1, const Point& p2) : Shape(p1), end(p2) {
        if (p1 == p2) {
            std::cerr << "line from one point created!";
            eq = {0, 0, 0};
        } else {
            deriveLinePolynomialFromPoints(p1, p2, eq.a, eq.b, eq.c);
        }
    }
    Line(const Line& o) = default;
    Line& operator=(const Line& o) {
        Line copy(o);
        swap(copy);
        return *this;
    }

    double perimeter() const override { return dist(anchor, end); }
    double area() const override { return 0; }
    bool isWithin(const Point& p) const override { return (*this)(p) == 0; }
    void print() const override {
        std::cout << "line: " << eq.a << "x";
        if (eq.b >= 0) std::cout << "+";
        std::cout << eq.b << "y";
        if (eq.c >= 0) std::cout << "+";
        std::cout << eq.c  //
                  << " color: " << borderColor.r << ',' << borderColor.g << ','
                  << borderColor.b << std::endl;
    }
    void serialize(std::ostream& os = std::cout) const override {
        // ex.: <line x1="0" y1="80" x2="100" y2="20" stroke="rgb(255,0,0)" />
        os << "<line x1=\"" << anchor.x << "\" y1=\"" << anchor.y << "\" x2=\""
           << end.x << "\" y2=\"" << end.y << "\" stroke=\"rgb(" << borderColor.r
           << ',' << borderColor.g << ',' << borderColor.b << ")\" />";
    }

   private:
    Point end;
    struct LinePolynomial {
        int a, b, c;
    };
    LinePolynomial eq;
    int operator()(const Point& p) const { return eq.a * p.x + eq.b * p.y + eq.c; }
    void deriveLinePolynomialFromPoints(const Point& p1, const Point& p2,  //
                                        int& a, int& b, int& c) {
        // line is colinear to vector (p2.x - p1.x ; p2.y - p1.y)
        // colinear vector has coordinates (B;-A)
        eq.a = p1.y - p2.y;
        eq.b = p2.x - p1.x;
        // C is such that A * p1.x + B * p1.y + C = 0
        eq.c = -(eq.a * p1.x + eq.b * p1.y);
        // now to remove common factors if possible:
        // (ex.: 2x + 4y + 6 = 0 --> x + 2y + 3 = 0)
        int gcd = greatestCommonDivisor(greatestCommonDivisor(eq.a, eq.b), eq.c);
        eq.a /= gcd;
        eq.b /= gcd;
        eq.c /= gcd;
        // for aesthetics, make sure coeff at x is positive
        if (eq.a < 0) {
            eq.a *= -1;
            eq.b *= -1;
            eq.c *= -1;
        }
    }
    void swap(Line& o) {
        std::swap(o.anchor, anchor);
        std::swap(o.end, end);
        std::swap(o.eq.a, eq.a);
        std::swap(o.eq.b, eq.b);
        std::swap(o.eq.c, eq.c);
    }
};

// anchor is one end of diagonal
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
    std::cout << "hai!" << std::endl;
    // std::cout << dist({0, 0}, {4, 4}) << std::endl;
    // std::cout << greatestCommonDivisor(16, 16) << std::endl;
    Line l({1, 2}, {5, 4});
    l.print();
    l.serialize();
}