#pragma once

#include "shape.hpp"

class Group : public Shape {
   public:
    Group();
    Group(const Group&);
    Group* clone() const override;
    ~Group();

    class Iterator {
       public:
        Iterator(size_t, Shape**);

        Iterator& operator++();
        Shape* operator*();
        bool operator!=(const Iterator&) const;

       private:
        size_t curr;
        Shape** arr;
    };
    Iterator begin() const;
    Iterator end() const;

    double perimeter() const override;
    double area() const override;
    bool contains(const Point&) const override;
    bool isOverlappedBy(const Shape&) const override;
    void isWithin(const Shape&) const override;
    void print() const override;
    void serialize(std::ostream&) const override;
    void translate(const int, const int) override;
    Group& addShape(const Shape*);
    void erase();

   private:
    Shape** shapes;
    size_t size, cap;
    void resize();
};
