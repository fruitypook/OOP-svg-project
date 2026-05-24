#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "circle.hpp"
#include "group.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "utils.hpp"

int main() {
    std::cout << "hai!" << std::endl;
    // std::cout << dist({0, 0}, {4, 4}) << std::endl;
    // std::cout << greatestCommonDivisor(16, 16) << std::endl;
    // Line* l = new Line({10, 20}, {55, 43});
    // l->print();
    // l->serialize();

    // Rectangle* r = new Rectangle({200, 100}, 100, 60);
    // r->print();
    // r->serialize();

    // Circle* c = new Circle({3, 5}, 6);
    // c->print();
    // c->serialize();

    // l->translate(10, 10), l->print();
    // r->translate(10, 10), r->print();
    // c->translate(10, 10), c->print();

    // Group* g = new Group;
    // g->addShape(l);
    // g->addShape(r);
    // g->print();

    // Group* g2 = new Group;
    // g2->addShape(c);
    // g2->addShape(g);
    // g2->print();
    // std::cout << g->perimeter() << ' ' << g->area() << std::endl;
    // std::cout << g->contains({4, 6}) << g->contains({40, 6}) << std::endl;
    // g->serialize();
    // g->translate(10, 10);
    // g->erase();
    // g->print();

    // g2->isWithin(Rectangle({0, 1000}, 1000, 1000));

    Group* g = new Group();

    Line* l = new Line({100, 0}, {70, 0}, {100, 0, 0});
    g->addShape(l);

    Rectangle* r = new Rectangle({200, 100}, 150, 40, {0, 100, 0}, {100, 0, 100});
    g->addShape(r);

    Circle* c = new Circle({50, 50}, 30, {100, 100, 0}, {0, 0, 100});
    g->addShape(c);

    std::ofstream file("shapes.svg");
    // <?xml version="1.0" standalone="no"?>
    // <!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN"
    //  "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
    // <svg>
    file << "<?xml version=\"1.0\" standalone=\"no\"?>" << "\n"              //
         << "<!DOCTYPE svg PUBLIC \"-// W3C//DTD SVG 1.1//EN\""              //
         << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << "\n"  //
         << "<svg>" << "\n";
    g->serialize(file, 1);
    file << "</svg>";

    // delete l;
    // delete r;
    // delete c;
    // delete g;
    // delete g2;
}