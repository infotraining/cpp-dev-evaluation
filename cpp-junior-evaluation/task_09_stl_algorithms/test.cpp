#include <gtest/gtest.h>
#include <vector>

#ifdef USE_SOLUTION
#include "solution.hpp"
#else
#include "starter.hpp"
#endif

TEST(StlAlgorithmsTest, CalculatesGrossValueForInStockItems) {
    std::vector<Product> items = {
        {1, 100.0, true},
        {2, 50.0, false},
        {3, 200.0, true}
    };
    EXPECT_DOUBLE_EQ(totalInStockGrossValue(items, 0.23), 369.0);
}

TEST(StlAlgorithmsTest, SortsAndFindsProductWithLowerBound) {
    std::vector<Product> items = {
        {30, 10.0, true},
        {10, 20.0, true},
        {20, 30.0, false}
    };

    const Product* found = findProductById(items, 20);
    ASSERT_NE(found, nullptr);
    EXPECT_DOUBLE_EQ(found->price, 30.0);

    EXPECT_EQ(findProductById(items, 25), nullptr);
}
