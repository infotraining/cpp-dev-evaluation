#pragma once
#include <memory>
#include <vector>

namespace Solution
{
    class Shape
    {
    public:
        virtual ~Shape() = default;
        virtual double area() const = 0;
    };

    class Circle : public Shape
    {
    public:
        explicit Circle(double radius);
        double area() const override;

    private:
        double radius_;
    };

    class Rectangle : public Shape
    {
    public:
        Rectangle(double width, double height);
        double area() const override;

    private:
        double width_;
        double height_;
    };

    double total_area(const std::vector<std::unique_ptr<Shape>>& shapes);

} // namespace Solution