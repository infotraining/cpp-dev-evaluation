#include "task_01_solution.hpp"

namespace Solution
{
    Circle::Circle(double radius)
        : radius_(radius)
    { }

    double Circle::area() const
    {
        constexpr double pi = 3.14159265358979323846;
        return pi * radius_ * radius_;
    }

    Rectangle::Rectangle(double width, double height)
        : width_(width)
        , height_(height)
    { }

    double Rectangle::area() const
    {
        return width_ * height_;
    }

    double total_area(const std::vector<std::unique_ptr<Shape>>& shapes)
    {
        double sum = 0.0;
        for (const auto& shape : shapes)
        {
            if (shape)
            {
                sum += shape->area();
            }
        }
        return sum;
    }
}