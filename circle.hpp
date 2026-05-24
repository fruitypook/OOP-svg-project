#pragma once

#define _USE_MATH_DEFINES

#include "shape.hpp"

// anchor is centre
class Circle : public Shape {
   public:
    Circle(const Point&, const unsigned, const RGBColor& = {0, 0, 0},
           const RGBColor& = {0, 0, 0});
    Circle(const Circle&);
    Circle& operator=(const Circle&);
    Circle* clone() const override;

    double perimeter() const override;
    double area() const override;
    bool contains(const Point&) const override;
    bool isOverlappedBy(const Shape&) const override;
    void print() const override;
    void serialize(std::ostream& = std::cout) const override;
    void translate(const int, const int);

   private:
    unsigned radius;
    void swap(Circle&);
};
