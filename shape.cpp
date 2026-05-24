#include "shape.hpp"

Shape::Shape(const Point& p, const RGBColor& _fillColor, const RGBColor& _strokeColor)
    : anchor(p), fillColor(_fillColor), strokeColor(_strokeColor) {}
Shape::Shape(const Shape&) = default;

void Shape::isWithin(const Shape& container) const {
    if (isOverlappedBy(container)) print();
}