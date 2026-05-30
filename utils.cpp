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
int hasSubstr(char* str, const char* substr) {
    if (!str || !substr) return -1;
    unsigned strlength = strlen(str), substrlength = strlen(substr);
    if (strlength < substrlength ||
        (strlength == substrlength && strcmp(str, substr) != 0))
        return -1;
    int idx = 0;
    while (idx + substrlength <= strlength) {
        if (strncmp(str + idx, substr, substrlength) == 0) return idx;
        ++idx;
    }
    return -1;
}
void skipAfterSubstr(char*& str, const char* substr) {
    int substrIdx = hasSubstr(str, substr);
    if (substrIdx == -1) return;
    str += (substrIdx + strlen(substr));
}
bool isCapital(const char c) { return 'A' <= c && c <= 'Z'; }
void toLowercase(char* str) {
    if (!str) return;
    while (*str != 0) {
        if (isCapital(*str)) *str = (*str) + ('a' - 'A');
        str++;
    }
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