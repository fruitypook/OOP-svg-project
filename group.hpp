#pragma once

#include "shape.hpp"

class Group : public Shape {
   public:
    Group() : shapes(nullptr), size(0), cap(0) {}
    Group(const Group& o) : shapes(new Shape*[o.cap]), size(o.size), cap(o.cap) {
        for (size_t i = 0; i < size; ++i) shapes[i] = o.shapes[i]->clone();
    }
    Group* clone() const override { return new Group(*this); }
    ~Group() {
        for (Shape* s : *this) delete s;
    }

    class Iterator {
       public:
        // Iterator() : curr(nullptr) {}
        Iterator(size_t _curr, Shape** _arr) : curr(_curr), arr(_arr) {}

        Iterator& operator++() {
            curr++;
            return *this;
        }
        Shape* operator*() { return arr[curr]; }
        // const Shape& operator*() const { return arr[curr]; }
        bool operator!=(const Iterator& o) const {
            return curr != o.curr || arr != o.arr;
        }
        // bool operator==(const Iterator& o) const { return !(*this != o); }

       private:
        size_t curr;
        Shape** arr;
    };
    Iterator begin() const { return Iterator(0, shapes); }
    Iterator end() const { return Iterator(size, shapes); }

    double perimeter() const override {
        double res = 0;
        for (Shape* s : *this) res += s->perimeter();
        return res;
    }
    double area() const override {
        double res = 0;
        for (Shape* s : *this) res += s->area();
        return res;
    }
    bool contains(const Point& p) const override {
        for (Shape* s : *this)
            if (s->contains(p)) return true;
        return false;
    }
    bool isOverlappedBy(const Shape& container) const override {
        for (Shape* s : *this) {
            if (!(s->isOverlappedBy(container))) return false;
        }
        return true;
    }
    void isWithin(const Shape& container) const override {
        for (Shape* s : *this) s->isWithin(container);
    }
    void print() const override {
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
    void serialize(std::ostream& os = std::cout) const override {
        os << "<g>" << std::endl;
        for (Shape* s : *this) {
            for (int i = 0; i < 2; ++i) std::cout << ' ';
            s->serialize(os);
        }
        os << "</g>" << std::endl;
    }
    void translate(const int dx, const int dy) override {
        for (Shape* s : *this) s->translate(dx, dy);
    }
    Group& addShape(const Shape* s) {
        if (size == cap) resize();
        shapes[size++] = s->clone();
        return *this;
    }
    void erase() {
        delete[] shapes;
        shapes = nullptr;
        size = cap = 0;
    }

   private:
    Shape** shapes;
    size_t size, cap;
    void resize() {
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
};
