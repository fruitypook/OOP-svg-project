#include "circle.hpp"

Circle::Circle(const Point& p, const unsigned r, const RGBColor& fillCol = {0, 0, 0},
               const RGBColor& strokeCol = {0, 0, 0})
    : Shape(p, fillCol, strokeCol), radius(r) {}
Circle::Circle(const Circle& o) = default;
Circle& Circle::operator=(const Circle& o) {
    Circle copy(o);
    swap(copy);
    return *this;
}
Circle* Circle::clone() const { return new Circle(*this); }

double Circle::perimeter() const { return 2 * M_PI * radius; }
double Circle::area() const { return M_PI * M_PI * radius; }
bool Circle::contains(const Point& p) const { return dist(p, anchor) - radius <= eps; }
bool Circle::isOverlappedBy(const Shape& container) const {
    // checking four corners of the circle
    Point right = {anchor.x + radius, anchor.y},
          top = {anchor.x, (anchor.y < radius ? 0 : anchor.y - radius)},
          left = {anchor.x < radius ? 0 : anchor.x - radius, anchor.y},
          bottom = {anchor.x, anchor.y + radius};
    return container.contains(right) && container.contains(top) &&
           container.contains(left) && container.contains(bottom);
}
void Circle::print() const {
    std::cout << "circle: " << anchor.x << ' ' << anchor.y  //
              << ' ' << radius << ' '                       //
              << fillColor << ' ' << strokeColor << std::endl;
}
void Circle::serialize(std::ostream& os = std::cout) const {
    // ex.: <circle cx="5" cy="5" r="10" fill="blue" />
    os << "<circle cx=\"" << anchor.x << "\" cy=\"" << anchor.y  //
       << "\" r=\"" << radius                                    //
       << "\" fill=\"" << fillColor << "\" stroke=\"" << strokeColor << "\" />"
       << std::endl;
}
void Circle::translate(const int dx, const int dy) { anchor.translate(dx, dy); }

void Circle::swap(Circle& o) {
    std::swap(o.anchor, anchor);
    std::swap(o.radius, radius);
    std::swap(o.strokeColor, strokeColor);
    std::swap(o.fillColor, fillColor);
}