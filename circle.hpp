#pragma once

#define _USE_MATH_DEFINES

#include "shape.hpp"

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
    Circle* clone() const override { return new Circle(*this); }

    double perimeter() const override { return 2 * M_PI * radius; }
    double area() const override { return M_PI * M_PI * radius; }
    bool contains(const Point& p) const override {
        return dist(p, anchor) - radius <= eps;
    }
    bool isOverlappedBy(const Shape& container) const override {
        // checking four corners of the circle
        Point right = {anchor.x + radius, anchor.y},
              top = {anchor.x, (anchor.y < radius ? 0 : anchor.y - radius)},
              left = {anchor.x < radius ? 0 : anchor.x - radius, anchor.y},
              bottom = {anchor.x, anchor.y + radius};
        return container.contains(right) && container.contains(top) &&
               container.contains(left) && container.contains(bottom);
    }
    void print() const override {
        std::cout << "circle: " << anchor.x << ' ' << anchor.y  //
                  << ' ' << radius << ' '                       //
                  << fillColor << ' ' << strokeColor << std::endl;
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
