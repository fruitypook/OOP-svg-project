#pragma once

#include "utils.hpp"

class Shape {
   public:
    Shape(const Point& p, const RGBColor& _fillColor = {0, 0, 0},
          const RGBColor& _strokeColor = {0, 0, 0})
        : anchor(p), fillColor(_fillColor), strokeColor(_strokeColor) {}
    Shape(const Shape& o) = default;
    virtual Shape* clone() const = 0;

    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual bool contains(const Point& p) const = 0;
    virtual bool isOverlappedBy(const Shape& container) const = 0;
    virtual void isWithin(const Shape& container) const {
        if (isOverlappedBy(container)) print();
    }
    virtual void print() const = 0;
    virtual void serialize(std::ostream& os = std::cout) const = 0;
    virtual void translate(const int dx, const int dy) = 0;

   protected:
    Shape() : anchor({0, 0}), fillColor({0, 0, 0}), strokeColor({0, 0, 0}) {}
    Point anchor;
    RGBColor fillColor, strokeColor;
};
