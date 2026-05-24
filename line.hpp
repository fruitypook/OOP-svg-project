#pragma once

#include "shape.hpp"

// anchor is one end of line
class Line : public Shape {
   public:
    Line(const Point&, const Point&, const RGBColor& = {0, 0, 0});
    Line(const Line&);
    Line& operator=(const Line&);
    Line* clone() const override;

    double perimeter() const override;
    double area() const override;
    bool contains(const Point&) const override;
    bool isOverlappedBy(const Shape&) const override;
    void print() const override;
    void serialize(std::ostream& = std::cout) const override;
    void translate(const int, const int);

   private:
    Point end;
    struct LinePolynomial {
        int a, b, c;
    };
    LinePolynomial eq;
    int operator()(const Point&) const;
    void deriveLinePolynomialFromPoints(const Point&, const Point&, int&, int&, int&);
    void swap(Line&);
};
