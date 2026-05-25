#define _USE_MATH_DEFINES
#include "circle.hpp"

Circle::Circle(const Point& p, const unsigned r, const RGBColor& fillCol,
               const RGBColor& strokeCol)
    : Shape(p, fillCol, strokeCol), radius(r) {
    if (radius == 0) std::cerr << "circle with radius 0 created!";
}
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
void Circle::print(const unsigned, const unsigned) const {
    std::cout << "circle: " << anchor.x << ' ' << anchor.y  //
              << ' ' << radius << ' '                       //
              << fillColor << ' ' << strokeColor << std::endl;
}
void Circle::serialize(std::ostream& os, unsigned nested) const {
    // ex.: <circle cx="5" cy="5" r="10" fill="blue" />
    for (int i = 0; i < nested * 2; ++i) os << ' ';
    os << "<circle cx=\"" << anchor.x << "\" cy=\"" << anchor.y  //
       << "\" r=\"" << radius                                    //
       << "\" fill=\"" << fillColor << "\" stroke=\"" << strokeColor << "\" />"
       << std::endl;
}
void Circle::deserialize(std::istream& is) {
    // ex.: cx="5" cy="5" r="10" fill="blue" />
    char buffer[DeserializationBufferSize];
    char* str = buffer;
    is.getline(str, DeserializationBufferSize);

    skipUntilNumber(str);
    anchor.x = readUnsigned(str);
    skipUntilNumber(str);
    anchor.y = readUnsigned(str);
    skipUntilNumber(str);
    radius = readUnsigned(str);

    skipUntilNumber(str);
    fillColor.r = readUnsigned(str);
    skipUntilNumber(str);
    fillColor.g = readUnsigned(str);
    skipUntilNumber(str);
    fillColor.b = readUnsigned(str);

    skipUntilNumber(str);
    strokeColor.r = readUnsigned(str);
    skipUntilNumber(str);
    strokeColor.g = readUnsigned(str);
    skipUntilNumber(str);
    strokeColor.b = readUnsigned(str);
}

void Circle::translate(const int dx, const int dy) { anchor.translate(dx, dy); }

void Circle::swap(Circle& o) {
    std::swap(o.anchor, anchor);
    std::swap(o.radius, radius);
    std::swap(o.strokeColor, strokeColor);
    std::swap(o.fillColor, fillColor);
}