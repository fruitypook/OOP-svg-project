#include "utils.hpp"

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
    unsigned min = std::min(rangeEnd1, rangeEnd2),  //
        max = std::max(rangeEnd1, rangeEnd2);
    return min <= val && val <= max;
}
void skipWhitespace(char*& str) {
    while (*str <= ' ') ++str;
}
bool isNum(char c) { return '0' <= c && c <= '9'; }
unsigned readUnsigned(char*& str) {
    unsigned res = 0;
    while (isNum(*str)) {
        res *= 10;
        res += (*str - '0');
        ++str;
    }
    return res;
}
void skipUntilNumber(char*& str) {
    while (!isNum(*str)) ++str;
}

std::ostream& operator<<(std::ostream& os, const RGBColor col) {
    return os << "rgb(" << col.r << ',' << col.g << ',' << col.b << ')';
}

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