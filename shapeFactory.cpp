#include "circle.hpp"
#include "group.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "shape.hpp"

Shape* shapeFactory(const char* type) {
    Shape* shape = nullptr;
    if (strcmp(type, "<line") == 0) {
        shape = new Line({0, 1}, {2, 3});  // dummy values
    } else if (strcmp(type, "<circle") == 0) {
        shape = new Circle({0, 0}, 1);  // dummy values
    } else if (strcmp(type, "<rect") == 0) {
        shape = new Rectangle({0, 0}, 1, 1);  // dummy values
    } else if (strcmp(type, "<g>") == 0) {
        shape = new Group();
    } else if (strcmp(type, "<svg>") == 0) {
        // ignore
    } else {
        std::cerr << "unrecognized type: " << type << std::endl;
    }
    return shape;
}