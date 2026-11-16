#pragma once
#include <memory>
#include <vector>

class Shape {
public:
    // TODO: Dodaj wirtualny destruktor i czysto wirtualną metodę area()
};

class Circle : public Shape {
public:
    explicit Circle(double radius);
    // TODO: Zaimplementuj area()
private:
    double radius_;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height);
    // TODO: Zaimplementuj area()
private:
    double width_;
    double height_;
};

double totalArea(const std::vector<std::unique_ptr<Shape>>& shapes);
