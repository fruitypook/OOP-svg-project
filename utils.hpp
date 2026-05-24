#pragma once
#include <cmath>
#include <iostream>

constexpr double eps = 1e-6;

int greatestCommonDivisor(int, int);
bool isBetween(const unsigned, const unsigned, const unsigned);

// TODO: hex --> rgb conversion (for serialization)
// TODO: word <-> rgb conversion (for de-/serialization)
struct RGBColor {
    int r, g, b;
};
std::ostream& operator<<(std::ostream&, const RGBColor);

// {0,0} is top left corner
struct Point {
    unsigned x, y;
    void translate(const int, const int);
};
bool operator==(const Point&, const Point&);
bool operator!=(const Point&, const Point&);

double dist(const Point& p1, const Point& p2);
