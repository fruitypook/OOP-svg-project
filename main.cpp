#include <fstream>

#include "circle.hpp"
#include "group.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "svgfile.hpp"
#include "utils.hpp"

int main() {
    std::cout << "hai!" << std::endl;

    Line* l = new Line({100, 10}, {70, 0}, {100, 0, 0});
    Rectangle* r = new Rectangle({200, 100}, 150, 40, {0, 100, 0}, {100, 0, 100});
    Circle* c = new Circle({50, 60}, 30, {100, 100, 0}, {0, 0, 100});
    SVGFile f("shapes.svg");
    f.addShape(l), f.addShape(r), f.addShape(c);
    f.serialize();
    f.deserialize();
    f.print();

    delete l;
    delete r;
    delete c;
}