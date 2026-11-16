#include <gtest/gtest.h>
#include <memory>
#include <vector>

#ifdef USE_SOLUTION
#include "task_01_solution.hpp"
#else
#include "task_01_starter.hpp"
#endif

TEST(PolymorphismTest, CalculatesTotalAreaCorrectly) {
    using namespace Solution;

    // Create a vector of shapes
    std::vector<std::unique_ptr<Shape>> shapes;
    // Add Rectangle(4.0, 5.0) to the vector
    shapes.push_back(std::make_unique<Rectangle>(4.0, 5.0));
    // Add Circle(1.0) to the vector
    shapes.push_back(std::make_unique<Circle>(1.0));
    
    EXPECT_NEAR(total_area(shapes), 23.14159265, 1e-5);
}

TEST(PolymorphismTest, EmptyVectorReturnsZero) {
    using namespace Solution;
    // Create an empty vector of shapes
    std::vector<std::unique_ptr<Shape>> shapes;

    EXPECT_DOUBLE_EQ(total_area(shapes), 0.0);
}
