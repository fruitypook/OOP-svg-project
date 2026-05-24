#pragma once

#include "shape.hpp"

// anchor is bottom left corner (min x, max y)
class Rectangle : public Shape {
   public:
    Rectangle(const Point& p1, const Point& p2, const RGBColor& fillCol = {0, 0, 0},
              const RGBColor& strokeCol = {0, 0, 0})
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
    Rectangle(const Point& p, const unsigned wid, const unsigned hei,
              const RGBColor& fillCol = {0, 0, 0}, const RGBColor& strokeCol = {0, 0, 0})
        : Shape(p, fillCol, strokeCol), width(wid), height(hei) {
        if (width == 0 || height == 0) {
            std::cerr << "rectangle with width or height 0 created!" << std::endl;
        }
    }
    Rectangle(const Rectangle& o) = default;
    Rectangle& operator=(const Rectangle& o) {
        Rectangle copy(o);
        swap(copy);
        return *this;
    }
    Rectangle* clone() const override { return new Rectangle(*this); }

    double perimeter() const override { return 2 * (width + height); }
    double area() const override { return width * height; }
    bool contains(const Point& p) const override {
        return isBetween(p.x, anchor.x, anchor.x + width) &&
               isBetween(p.y, anchor.y, (anchor.y < height ? 0 : anchor.y - height));
    }
    bool isOverlappedBy(const Shape& container) const override {
        Point bottomRight = {anchor.x + width, anchor.y},
              topLeft = {anchor.x, (anchor.y < height ? 0 : anchor.y - height)},
              topRight = {anchor.x + width, (anchor.y < height ? 0 : anchor.y - height)};

        return container.contains(anchor) && container.contains(bottomRight) &&
               container.contains(topLeft) && container.contains(topRight);
    }
    void print() const override {
        std::cout << "rectangle: "                                                 //
                  << anchor.x << ' ' << anchor.y << ' ' << width << ' ' << height  //
                  << ' ' << fillColor << ' ' << strokeColor << std::endl;
    }
    void serialize(std::ostream& os = std::cout) const override {
        // ex.:   <rect x="5" y="5" width="10" height="10" fill="green" />
        os << "<rect x=\"" << anchor.x << "\" y=\"" << anchor.y   //
           << "\" width=\"" << width << "\" height=\"" << height  //
           << "\" fill=\"rgb(" << fillColor.r << ',' << fillColor.g << ',' << fillColor.b
           << ')'  //
           << "\" stroke=\"rgb(" << strokeColor.r << ',' << strokeColor.g << ','
           << strokeColor.b << ")\" />" << std::endl;
    }
    void translate(const int dx, const int dy) { anchor.translate(dx, dy); }

   private:
    unsigned width, height;
    void swap(Rectangle& o) {
        std::swap(o.anchor, anchor);
        std::swap(o.strokeColor, strokeColor);
        std::swap(o.fillColor, fillColor);
        std::swap(o.width, width);
        std::swap(o.height, height);
    }
};
