#define _USE_MATH_DEFINES
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
bool isBetween(const unsigned val, const unsigned rangeEnd1,
               const unsigned rangeEnd2) {
    unsigned left = std::min(rangeEnd1, rangeEnd2),  //
        right = std::max(rangeEnd1, rangeEnd2);
    return left <= val && val >= right;
}

// TODO: hex --> rgb conversion (for serialization)
// TODO: word <-> rgb conversion (for de-/serialization)
struct RGBColor {
    int r, g, b;
};
std::ostream& operator<<(std::ostream& os, const RGBColor col) {
    return os << "rgb(" << col.r << ',' << col.g << ',' << col.b << ')';
}

// {0,0} is top left corner
struct Point {
    unsigned x, y;
    void translate(const int, const int);
};
bool operator==(const Point& p1, const Point& p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}
bool operator!=(const Point& p1, const Point& p2) { return !(p1 == p2); }
void Point::translate(const int dx, const int dy) { x += dx, y += dy; }

double dist(const Point& p1, const Point& p2) {
    unsigned dx = std::abs((int)(p1.x - p2.x)),  //
        dy = std::abs((int)(p1.y - p2.y));
    return std::sqrt(dx * dx + dy * dy);
}
constexpr double eps = 1e-6;

class Shape {
   public:
    Shape(const Point& p, const RGBColor& _fillColor = {0, 0, 0},
          const RGBColor& _strokeColor = {0, 0, 0})
        : anchor(p), fillColor(_fillColor), strokeColor(_strokeColor) {}
    Shape(const Shape& o) = default;

    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual bool contains(const Point& p) const = 0;
    // TODO: this method for later :)
    // virtual bool isWithin(const Point& p) const = 0;
    virtual void print() const = 0;
    virtual void serialize(std::ostream& os = std::cout) const = 0;
    virtual void translate(const int dx, const int dy) = 0;

   protected:
    Shape() : anchor({0, 0}), fillColor({0, 0, 0}), strokeColor({0, 0, 0}) {}
    Point anchor;
    RGBColor fillColor, strokeColor;
};

// anchor is one end of line
class Line : public Shape {
   public:
    Line(const Point& p1, const Point& p2, const RGBColor& strokeCol = {0, 0, 0})
        : Shape(p1, strokeCol), end(p2) {
        if (p1 == p2) {
            std::cerr << "line from one point created!" << std::endl;
            // line parallel to x axis : y = p1.y
            eq = {0, 1, (int)p1.y * (-1)};
            return;
        }
        deriveLinePolynomialFromPoints(p1, p2, eq.a, eq.b, eq.c);
    }
    Line(const Line& o) = default;
    Line& operator=(const Line& o) {
        Line copy(o);
        swap(copy);
        return *this;
    }

    double perimeter() const override { return dist(anchor, end); }
    double area() const override { return 0; }
    bool contains(const Point& p) const override {
        return (*this)(p) == 0 &&  //
               isBetween(p.x, anchor.x, end.x) && isBetween(p.y, anchor.y, end.y);
    }
    void print() const override {
        std::cout << "line: "                                                     //
                  << anchor.x << ' ' << anchor.y << ' ' << end.x << ' ' << end.y  //
                  << ' ' << strokeColor << std::endl;
    }
    void serialize(std::ostream& os = std::cout) const override {
        // ex.: <line x1="0" y1="80" x2="100" y2="20" stroke="rgb(255,0,0)" />
        os << "<line x1=\"" << anchor.x << "\" y1=\"" << anchor.y  //
           << "\" x2=\"" << end.x << "\" y2=\"" << end.y           //
           << "\" stroke=\"rgb(" << strokeColor.r << ',' << strokeColor.g << ','
           << strokeColor.b << ")\" />" << std::endl;
    }
    void translate(const int dx, const int dy) {
        anchor.translate(dx, dy);
        end.translate(dx, dy);
        deriveLinePolynomialFromPoints(anchor, end, eq.a, eq.b, eq.c);
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
        std::swap(o.strokeColor, strokeColor);
        std::swap(o.fillColor, fillColor);
        std::swap(o.eq, eq);
    }
};

// anchor is bottom left corner (min x, max y)
class Rectangle : public Shape {
   public:
    Rectangle(const Point& p1, const Point& p2, const RGBColor& fillCol = {0, 0, 0},
              const RGBColor& strokeCol = {0, 0, 0})
        : Shape(p1, fillCol, strokeCol) {
        if (p1 == p2) {
            std::cerr << "rectangle from one point created!" << std::endl;
            anchor = p1;
            width = 0, height = 0;
            return;
        }
        anchor.x = std::min(p1.x, p2.x);
        anchor.y = std::max(p1.y, p2.y);
        width = std::abs((int)(p1.x - p2.x));
        height = std::abs((int)(p1.y - p2.y));
    }
    Rectangle(const Point& p, const unsigned wid, const unsigned hei,
              const RGBColor& fillCol = {0, 0, 0},
              const RGBColor& strokeCol = {0, 0, 0})
        : Shape(p, fillCol, strokeCol), width(wid), height(hei) {
        if (width == 0 || height == 0) {
            std::cerr << "rectangle with width or height 0 created!" << std::endl;
        }
    }
    Rectangle(const Rectangle& o) = default;
    Rectangle& operator=(const Rectangle& o) {
        Rectangle copy(o);
        swap(copy);
        return *this;
    }

    double perimeter() const override { return 2 * (width + height); }
    double area() const override { return width * height; }
    bool contains(const Point& p) const override {
        return isBetween(p.x, anchor.x, anchor.x + width) &&
               isBetween(p.y, anchor.y, anchor.y - height);
    }
    void print() const override {
        std::cout << "rectangle: "                                                 //
                  << anchor.x << ' ' << anchor.y << ' ' << width << ' ' << height  //
                  << ' ' << fillColor << ' ' << strokeColor << std::endl;
    }
    void serialize(std::ostream& os = std::cout) const override {
        // ex.:   <rect x="5" y="5" width="10" height="10" fill="green" />
        os << "<rect x=\"" << anchor.x << "\" y=\"" << anchor.y   //
           << "\" width=\"" << width << "\" height=\"" << height  //
           << "\" fill=\"rgb(" << fillColor.r << ',' << fillColor.g << ','
           << fillColor.b << ')'  //
           << "\" stroke=\"rgb(" << strokeColor.r << ',' << strokeColor.g << ','
           << strokeColor.b << ")\" />" << std::endl;
    }
    void translate(const int dx, const int dy) { anchor.translate(dx, dy); }

   private:
    unsigned width, height;
    void swap(Rectangle& o) {
        std::swap(o.anchor, anchor);
        std::swap(o.strokeColor, strokeColor);
        std::swap(o.fillColor, fillColor);
        std::swap(o.width, width);
        std::swap(o.height, height);
    }
};

// anchor is centre
class Circle : public Shape {
   public:
    Circle(const Point& p, const unsigned r, const RGBColor& fillCol = {0, 0, 0},
           const RGBColor& strokeCol = {0, 0, 0})
        : Shape(p, fillCol, strokeCol), radius(r) {}
    Circle(const Circle& o) = default;
    Circle& operator=(const Circle& o) {
        Circle copy(o);
        swap(copy);
        return *this;
    }

    double perimeter() const override { return 2 * M_PI * radius; }
    double area() const override { return M_PI * M_PI * radius; }
    bool contains(const Point& p) const override {
        return dist(p, anchor) - radius <= eps;
    }
    void print() const override {
        std::cout << "circle: " << anchor.x << ' ' << anchor.y  //
                  << ' ' << radius << ' '                       //
                  << fillColor << strokeColor << std::endl;
    }
    void serialize(std::ostream& os = std::cout) const override {
        // ex.: <circle cx="5" cy="5" r="10" fill="blue" />
        os << "<circle cx=\"" << anchor.x << "\" cy=\"" << anchor.y  //
           << "\" r=\"" << radius                                    //
           << "\" fill=\"" << fillColor << "\" stroke=\"" << strokeColor << "\" />"
           << std::endl;
    }
    void translate(const int dx, const int dy) { anchor.translate(dx, dy); }

   private:
    unsigned radius;
    void swap(Circle& o) {
        std::swap(o.anchor, anchor);
        std::swap(o.radius, radius);
        std::swap(o.strokeColor, strokeColor);
        std::swap(o.fillColor, fillColor);
    }
};

class Group : public Shape {
   public:
    Group() : shapes(nullptr), size(0), cap(0) {}
    Group(const Group& o) : shapes(new Shape*[o.cap]), size(o.size), cap(o.cap) {}

    // TODO: these methods
    double perimeter() const override {}
    double area() const override {}
    bool contains(const Point& p) const override {}
    void print() const override {}
    void serialize(std::ostream& os = std::cout) const override {}
    void translate(const int dx, const int dy) override {}
    Group& addShape(const Shape* s) {}
    void erase(size_t idx) {}

    // TODO: iterator!!!

   private:
    Shape** shapes;
    size_t size, cap;
    void resize() {
        size_t newCap = (cap == 0 ? 1 : cap * 2);
        // TODO: move semantics!
    }
};

int main() {
    std::cout << "hai!" << std::endl;
    // std::cout << dist({0, 0}, {4, 4}) << std::endl;
    // std::cout << greatestCommonDivisor(16, 16) << std::endl;
    Line* l = new Line({1, 2}, {5, 4});
    l->print();
    l->serialize();

    Rectangle* r = new Rectangle({2, 1}, 10, 5);
    r->print();
    r->serialize();

    Circle* c = new Circle({3, 5}, 6);
    c->print();
    c->serialize();

    l->translate(10, 10);
    l->print();
    r->translate(10, 10);
    r->print();
    c->translate(10, 10);
    c->print();

    delete l;
    delete r;
    delete c;
}