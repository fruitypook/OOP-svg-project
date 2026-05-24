#pragma once

#include "utils.hpp"

class Shape {
   public:
    Shape(const Point&, const RGBColor& = {0, 0, 0}, const RGBColor& = {0, 0, 0});
    Shape(const Shape&);
    virtual Shape* clone() const = 0;

    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual bool contains(const Point&) const = 0;
    virtual bool isOverlappedBy(const Shape&) const = 0;
    virtual void isWithin(const Shape&) const;
    virtual void print() const = 0;
    virtual void serialize(std::ostream&) const = 0;
    virtual void translate(const int, const int) = 0;

   protected:
    Shape() : anchor({0, 0}), fillColor({0, 0, 0}), strokeColor({0, 0, 0}) {}
    Point anchor;
    RGBColor fillColor, strokeColor;
};
