#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <iostream>

class Shape {
public:
    virtual void draw() = 0;
};

class Stroke : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a stroke" << std::endl;
    }
};

class Triangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a triangle" << std::endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a rectangle" << std::endl;
    }
};

class Pentagon : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a pentagon" << std::endl;
    }
};

class Hexagon : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a hexagon" << std::endl;
    }
};

class Heptagon : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a heptagon" << std::endl;
    }
};

class Octogon : public Shape {
public:
    void draw() override {
        std::cout << "Drawing an octogon" << std::endl;
    }
};

class Ellipsis : public Shape {
public:
    void draw() override {
        std::cout << "Drawing an ellipsis" << std::endl;
    }
};

class Circle : public Ellipsis {
public:
    void draw() override {
        std::cout << "Drawing a circle" << std::endl;
    }
};

// Ajoutez ici les autres classes de formes géométriques si nécessaire

#endif /* _SHAPE_H_ */
