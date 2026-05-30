#pragma once

#include <cmath>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

constexpr double eps = 1e-6;
constexpr int DeserializationBufferSize = 128;

int greatestCommonDivisor(int, int);
bool isBetween(const unsigned, const unsigned, const unsigned);
void skipWhitespace(char*&);
unsigned readUnsigned(char*&);
int readInt(char*&);
void skipUntilNumber(char*&);
int hasSubstr(char*, const char*);
void skipAfterSubstr(char*&, const char*);
bool isCapital(const char);
void toLowercase(char*);

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

void printHelpMsg();