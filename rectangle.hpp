#pragma once

#include "shape.hpp"

// anchor is bottom left corner (min x, max y)
class Rectangle : public Shape {
   public:
    Rectangle(const Point&, const Point&, const RGBColor&, const RGBColor&);
    Rectangle(const Point&, const unsigned, const unsigned, const RGBColor&,
              const RGBColor&);
    Rectangle(const Rectangle&);
    Rectangle& operator=(const Rectangle&);
    Rectangle* clone() const override;

    double perimeter() const override;
    double area() const override;
    bool contains(const Point&) const override;
    bool isOverlappedBy(const Shape&) const override;
    void print() const override;
    void serialize(std::ostream&) const override;
    void translate(const int, const int);

   private:
    unsigned width, height;
    void swap(Rectangle&);
};
