#include <gtest/gtest.h>
#include <memory>
#include <vector>

#ifdef USE_SOLUTION
#include "solution.hpp"
#else
#include "starter.hpp"
#endif

TEST(PolymorphismTest, CalculatesTotalAreaCorrectly) {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(4.0, 5.0)); // 20.0
    shapes.push_back(std::make_unique<Circle>(1.0));         // ~3.14159
    shapes.push_back(nullptr);                               // Ignored

    EXPECT_NEAR(totalArea(shapes), 23.14159265, 1e-5);
}

TEST(PolymorphismTest, EmptyVectorReturnsZero) {
    std::vector<std::unique_ptr<Shape>> shapes;
    EXPECT_DOUBLE_EQ(totalArea(shapes), 0.0);
}
