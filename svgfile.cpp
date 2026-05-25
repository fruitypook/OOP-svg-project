#include "svgfile.hpp"

#include <fstream>

SVGFile::SVGFile(const char* _fn) : Group(), filename(new char[strlen(_fn)]) {
    strcpy(filename, _fn);
}

SVGFile::SVGFile(const SVGFile& o) : Group(o), filename(new char[strlen(o.filename)]) {
    strcpy(filename, o.filename);
}
SVGFile& SVGFile::operator=(const SVGFile& o) {
    SVGFile copy(o);
    swap(copy);
    return *this;
}
void SVGFile::swap(SVGFile& o) {
    std::swap(o.filename, filename);
    std::swap(o.shapes, shapes);
    std::swap(o.size, size);
    std::swap(o.cap, cap);
}
SVGFile::~SVGFile() {
    for (Shape* s : *this) {
        delete s;
    }
}

void SVGFile::serialize(std::ostream&, unsigned) const {
    // <?xml version="1.0" standalone="no"?>
    // <!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN"
    //  "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
    // <svg>
    std::ofstream file(filename, std::ios::trunc);
    file << "<svg>" << std::endl;
    for (Shape* s : *this) s->serialize(file, 1);
    file << "</svg>" << std::endl;
}
void SVGFile::deserialize(std::istream&) {
    clear();
    std::ifstream file(filename);
    if (file.peek() == std::istream::traits_type::eof()) {
        std::cerr << "attempt to deserialize from an empty file!";
        return;
    }
    char typeBuffer[20];
    char* type = typeBuffer;
    skipWhitespace(type);
    file >> type;

    while (strcmp(type, "</svg>") != 0) {
        Shape* shape = shapeFactory(type);
        if (shape) {
            shape->deserialize(file);
            addShape(shape);
            delete shape;
        }

        file >> type;
        skipWhitespace(type);
    }
}
void SVGFile::print(const unsigned, const unsigned) const {
    if (size == 0) {
        std::cerr << "empty file printed!" << std::endl;
        return;
    }
    unsigned i = 1;
    for (Shape* s : *this) {
        std::cout << i << ".";
        s->print(1, i++);
    }
    // std::cout << std::endl;
}
