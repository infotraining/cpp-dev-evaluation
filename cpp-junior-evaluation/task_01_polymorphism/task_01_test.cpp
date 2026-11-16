#include <gtest/gtest.h>
#include <memory>
#include <vector>

#ifdef USE_SOLUTION
#include "task_01_solution.hpp"
#else
#include "task_01_starter.hpp"
#endif

TEST(PolymorphismTest, CalculatesTotalAreaCorrectly) {
    // Create a vector of shapes
    // Add Rectangle(4.0, 5.0) to the vector
    // Add Circle(1.0) to the vector
    
    EXPECT_NEAR(total_area(/*shapes*/), 23.14159265, 1e-5);
}

TEST(PolymorphismTest, EmptyVectorReturnsZero) {
    // Create an empty vector of shapes

    EXPECT_DOUBLE_EQ(total_area(/* TODO: pass the vector of shapes */ ), 0.0);
}
