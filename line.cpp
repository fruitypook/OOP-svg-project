#include "line.hpp"

Line::Line(const Point& p1, const Point& p2, const RGBColor& strokeCol)
    : Shape(p1, strokeCol, strokeCol), end(p2) {
    if (p1 == p2) {
        std::cerr << "line from one point created!" << std::endl;
        // line parallel to x axis : y = p1.y
        eq = {0, 1, (int)p1.y * (-1)};
        return;
    }
    deriveLinePolynomialFromPoints(p1, p2, eq.a, eq.b, eq.c);
}
Line::Line(const Line& o) = default;
Line& Line::operator=(const Line& o) {
    Line copy(o);
    swap(copy);
    return *this;
}
Line* Line::clone() const { return new Line(*this); }

double Line::perimeter() const { return dist(anchor, end); }
double Line::area() const { return 0; }
bool Line::contains(const Point& p) const {
    return (*this)(p) == 0 &&  //
           isBetween(p.x, anchor.x, end.x) && isBetween(p.y, anchor.y, end.y);
}
bool Line::isOverlappedBy(const Shape& container) const {
    // both ends of a line being inside another shape means the entire line is
    // inside as this doesn't support concave shapes.
    return container.contains(anchor) && container.contains(end);
}
void Line::print() const {
    std::cout << "line: "                                                     //
              << anchor.x << ' ' << anchor.y << ' ' << end.x << ' ' << end.y  //
              << ' ' << strokeColor << std::endl;
}
void Line::serialize(std::ostream& os, unsigned nested) const {
    // ex.: <line x1="0" y1="80" x2="100" y2="20" stroke="rgb(255,0,0)" />
    for (int i = 0; i < nested * 2; ++i) os << ' ';
    os << "<line x1=\"" << anchor.x << "\" y1=\"" << anchor.y  //
       << "\" x2=\"" << end.x << "\" y2=\"" << end.y           //
       << "\" stroke=\"rgb(" << strokeColor.r << ',' << strokeColor.g << ','
       << strokeColor.b << ")\" />" << std::endl;
}
void Line::translate(const int dx, const int dy) {
    anchor.translate(dx, dy);
    end.translate(dx, dy);
    deriveLinePolynomialFromPoints(anchor, end, eq.a, eq.b, eq.c);
}

int Line::operator()(const Point& p) const { return eq.a * p.x + eq.b * p.y + eq.c; }
void Line::deriveLinePolynomialFromPoints(const Point& p1, const Point& p2,  //
                                          int& a, int& b, int& c) {
    // line is colinear to vector (p2.x - p1.x ; p2.y - p1.y)
    // colinear vector has coordinates (B;-A)
    eq.a = (int)p1.y - (int)p2.y;
    eq.b = (int)p2.x - (int)p1.x;
    // C is such that A * p1.x + B * p1.y + C = 0
    eq.c = -(eq.a * p1.x + eq.b * p1.y);
    // now to remove common factors if possible:
    // (ex.: 2x + 4y + 6 = 0 --> x + 2y + 3 = 0)
    int gcd = greatestCommonDivisor(greatestCommonDivisor(eq.a, eq.b), eq.c);
    eq.a /= gcd;
    eq.b /= gcd;
    eq.c /= gcd;
    // for aesthetics, make sure coeff at x is positive
    if (eq.a < 0) {
        eq.a *= -1;
        eq.b *= -1;
        eq.c *= -1;
    }
}
void Line::swap(Line& o) {
    std::swap(o.anchor, anchor);
    std::swap(o.end, end);
    std::swap(o.strokeColor, strokeColor);
    std::swap(o.fillColor, fillColor);
    std::swap(o.eq, eq);
}
