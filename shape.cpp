#include "shape.hpp"

Shape::Shape(const Point& p, const RGBColor& _fillColor = {0, 0, 0},
             const RGBColor& _strokeColor = {0, 0, 0})
    : anchor(p), fillColor(_fillColor), strokeColor(_strokeColor) {}

void Shape::isWithin(const Shape& container) const {
    if (isOverlappedBy(container)) print();
}