#include "rectangle.hpp"

Rectangle::Rectangle(const Point& p1, const Point& p2,  //
                     const RGBColor& fillCol, const RGBColor& strokeCol)
    : Shape(p1, fillCol, strokeCol) {
    if (p1 == p2) {
        std::cerr << "rectangle from one point created!" << std::endl;
        anchor = p1;
        width = 0, height = 0;
        return;
    }
    anchor.x = std::min(p1.x, p2.x);
    anchor.y = std::max(p1.y, p2.y);
    width = std::abs((int)p1.x - (int)p2.x);
    height = std::abs((int)p1.y - (int)p2.y);
}
Rectangle::Rectangle(const Point& p, const unsigned wid, const unsigned hei,
                     const RGBColor& fillCol, const RGBColor& strokeCol)
    : Shape(p, fillCol, strokeCol), width(wid), height(hei) {
    if (width == 0 || height == 0) {
        std::cerr << "rectangle with width or height 0 created!" << std::endl;
    }
}
Rectangle::Rectangle(const Rectangle& o) = default;
Rectangle& Rectangle::operator=(const Rectangle& o) {
    Rectangle copy(o);
    swap(copy);
    return *this;
}
Rectangle* Rectangle::clone() const { return new Rectangle(*this); }

double Rectangle::perimeter() const { return 2 * (width + height); }
double Rectangle::area() const { return width * height; }
bool Rectangle::contains(const Point& p) const {
    return isBetween(p.x, anchor.x, anchor.x + width) &&
           isBetween(p.y, anchor.y, (anchor.y < height ? 0 : anchor.y - height));
}
bool Rectangle::isOverlappedBy(const Shape& container) const {
    Point bottomRight = {anchor.x + width, anchor.y},
          topLeft = {anchor.x, (anchor.y < height ? 0 : anchor.y - height)},
          topRight = {anchor.x + width, (anchor.y < height ? 0 : anchor.y - height)};

    return container.contains(anchor) && container.contains(bottomRight) &&
           container.contains(topLeft) && container.contains(topRight);
}
void Rectangle::print(const unsigned, const std::vector<unsigned>&) const {
    std::cout << "rectangle: "                                                 //
              << anchor.x << ' ' << anchor.y << ' ' << width << ' ' << height  //
              << ' ' << fillColor << ' ' << strokeColor << std::endl;
}
void Rectangle::serialize(std::ostream& os, unsigned nested) const {
    // ex.:   <rect x="5" y="5" width="10" height="10" fill="green" />
    for (int i = 0; i < nested * 2; ++i) os << ' ';
    os << "<rect x=\"" << anchor.x << "\" y=\"" << anchor.y                      //
       << "\" width=\"" << width << "\" height=\"" << height                     //
       << "\" fill=\"" << fillColor << "\" stroke=\"" << strokeColor << "\" />"  //
       << std::endl;
}
void Rectangle::deserialize(std::istream& is) {
    // x="5" y="5" width="10" height="10" fill="rgb(0,100,0)" stroke="rgb(100,0,100)" />
    char buffer[DeserializationBufferSize];
    char* str = buffer;
    is.getline(str, DeserializationBufferSize);

    skipAfterSubstr(str, "x=\"");
    anchor.x = readUnsigned(str);
    skipAfterSubstr(str, "y=\"");
    anchor.y = readUnsigned(str);

    skipAfterSubstr(str, "width=\"");
    width = readUnsigned(str);
    skipAfterSubstr(str, "height=\"");
    height = readUnsigned(str);

    skipAfterSubstr(str, "fill=\"(rgb");
    fillColor.r = readUnsigned(str);
    skipUntilNumber(str);
    fillColor.g = readUnsigned(str);
    skipUntilNumber(str);
    fillColor.b = readUnsigned(str);

    skipAfterSubstr(str, "stroke=\"(rgb");
    strokeColor.r = readUnsigned(str);
    skipUntilNumber(str);
    strokeColor.g = readUnsigned(str);
    skipUntilNumber(str);
    strokeColor.b = readUnsigned(str);
}
void Rectangle::translate(const int dx, const int dy) { anchor.translate(dx, dy); }

void Rectangle::swap(Rectangle& o) {
    std::swap(o.anchor, anchor);
    std::swap(o.strokeColor, strokeColor);
    std::swap(o.fillColor, fillColor);
    std::swap(o.width, width);
    std::swap(o.height, height);
}
