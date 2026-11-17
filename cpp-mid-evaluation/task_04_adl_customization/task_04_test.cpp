#include <gtest/gtest.h>

#ifdef USE_SOLUTION
#include "task_04_solution.hpp"
#else
#include "task_04.hpp"
#endif

TEST(AdlCustomizationTest, UsesStreamableFallback)
{
    EXPECT_EQ(mid::format(42), "42");
}

TEST(AdlCustomizationTest, FindsCustomizationInTypeNamespace)
{
    EXPECT_EQ(mid::format(geometry::Point{3, 8}), "(3, 8)");
}
