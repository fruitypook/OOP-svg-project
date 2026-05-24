#include "group.hpp"

Group::Group() : shapes(nullptr), size(0), cap(0) {}
Group::Group(const Group& o) : shapes(new Shape*[o.cap]), size(o.size), cap(o.cap) {
    for (size_t i = 0; i < size; ++i) shapes[i] = o.shapes[i]->clone();
}
Group* Group::clone() const { return new Group(*this); }
Group::~Group() {
    for (Shape* s : *this) delete s;
}

Group::Iterator::Iterator(size_t _curr, Shape** _arr) : curr(_curr), arr(_arr) {}
Group::Iterator& Group::Iterator::operator++() {
    curr++;
    return *this;
}
Shape* Group::Iterator::operator*() { return arr[curr]; }
bool Group::Iterator::operator!=(const Iterator& o) const {
    return curr != o.curr || arr != o.arr;
}

Group::Iterator Group::begin() const { return Group::Iterator(0, shapes); }
Group::Iterator Group::end() const { return Group::Iterator(size, shapes); }

double Group::perimeter() const {
    double res = 0;
    for (Shape* s : *this) res += s->perimeter();
    return res;
}
double Group::area() const {
    double res = 0;
    for (Shape* s : *this) res += s->area();
    return res;
}
bool Group::contains(const Point& p) const {
    for (Shape* s : *this)
        if (s->contains(p)) return true;
    return false;
}
bool Group::isOverlappedBy(const Shape& container) const {
    for (Shape* s : *this) {
        if (!(s->isOverlappedBy(container))) return false;
    }
    return true;
}
void Group::isWithin(const Shape& container) const {
    for (Shape* s : *this) s->isWithin(container);
}
void Group::print() const {
    std::cout << "Group: " << std::endl;
    if (size == 0) {
        std::cerr << "empty group printed!" << std::endl;
        return;
    }
    unsigned i = 1;
    for (Shape* s : *this) {
        std::cout << i++ << ". ";
        s->print();
    }
    std::cout << std::endl;
}
void Group::serialize(std::ostream& os, unsigned nested) const {
    for (int i = 0; i < nested * 2; ++i) os << ' ';
    os << "<g>" << std::endl;
    for (Shape* s : *this) s->serialize(os, nested + 1);
    for (int i = 0; i < nested * 2; ++i) os << ' ';
    os << "</g>" << std::endl;
}
void Group::translate(const int dx, const int dy) {
    for (Shape* s : *this) s->translate(dx, dy);
}
Group& Group::addShape(const Shape* s) {
    if (size == cap) resize();
    shapes[size++] = s->clone();
    return *this;
}
void Group::erase() {
    delete[] shapes;
    shapes = nullptr;
    size = cap = 0;
}

void Group::resize() {
    size_t newCap = (cap == 0 ? 1 : cap * 2);
    Shape** newArr = new Shape*[newCap];
    for (size_t i = 0; i < size; ++i) {
        newArr[i] = shapes[i];
        shapes[i] = nullptr;
    }
    delete shapes;
    shapes = newArr;
    cap = newCap;
}
