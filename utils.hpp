#pragma once
#include <cmath>
#include <iostream>

int greatestCommonDivisor(int n1, int n2) {
    int a = std::max(n1, n2), b = std::min(n1, n2);
    while (b != 0) {
        int k = b;
        b = a % b;
        a = k;
    }
    return a;
}
bool isBetween(const unsigned val, const unsigned rangeEnd1, const unsigned rangeEnd2) {
    unsigned left = std::min(rangeEnd1, rangeEnd2),  //
        right = std::max(rangeEnd1, rangeEnd2);
    return left <= val && val <= right;
}

// TODO: hex --> rgb conversion (for serialization)
// TODO: word <-> rgb conversion (for de-/serialization)
struct RGBColor {
    int r, g, b;
};
std::ostream& operator<<(std::ostream& os, const RGBColor col) {
    return os << "rgb(" << col.r << ',' << col.g << ',' << col.b << ')';
}

// {0,0} is top left corner
struct Point {
    unsigned x, y;
    void translate(const int, const int);
};
bool operator==(const Point& p1, const Point& p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}
bool operator!=(const Point& p1, const Point& p2) { return !(p1 == p2); }
void Point::translate(const int dx, const int dy) { x += dx, y += dy; }

double dist(const Point& p1, const Point& p2) {
    unsigned dx = std::abs((int)(p1.x - p2.x)),  //
        dy = std::abs((int)(p1.y - p2.y));
    return std::sqrt(dx * dx + dy * dy);
}
constexpr double eps = 1e-6;
