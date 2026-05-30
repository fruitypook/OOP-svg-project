#pragma once

#include "shape.hpp"

class Group : public Shape {
   public:
    Group();
    Group(const Group&);
    Group* clone() const override;
    Group(Group&&);
    ~Group() override;

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
    void print(const unsigned = 0, const std::vector<unsigned>& = {}) const override;
    void serialize(std::ostream& = std::cout, unsigned = 0) const override;
    void deserialize(std::istream& = std::cin) override;
    void translate(const int, const int) override;
    Group& addShape(const Shape*);
    void clear();

   protected:
    Shape** shapes;
    size_t size, cap;
    void resize();
};
