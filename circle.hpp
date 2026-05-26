#pragma once

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
    void print(const unsigned = 0, const std::vector<unsigned>& = {}) const override;
    void serialize(std::ostream& = std::cout, unsigned = 0) const override;
    void deserialize(std::istream& = std::cin) override;
    void translate(const int, const int);

   private:
    unsigned radius;
    void swap(Circle&);
};
