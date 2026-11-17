#include <gtest/gtest.h>
#include <memory>

#ifdef USE_SOLUTION
#include "task_02_solution.hpp"
using namespace Solution;
#else
#include "task_02.hpp"
#endif

TEST(SmartPointersTest, PacketBufferTransferOwnership) {
    PacketBuffer buf(64);
    EXPECT_EQ(buf.size(), 64u);

    auto rawPtr = buf.release_buffer();
    EXPECT_NE(rawPtr, nullptr);
    EXPECT_EQ(buf.size(), 0u);
}

TEST(SmartPointersTest, WeakPtrBreaksCycle) {
    std::weak_ptr<NodeA> observerA;
    std::shared_ptr<NodeB> b = std::make_shared<NodeB>();

    {
        auto a = std::make_shared<NodeA>();
        observerA = a;
        a->next = b;
        b->prev = a;
        EXPECT_TRUE(b->has_valid_prev());
    }

    EXPECT_TRUE(observerA.expired());
    EXPECT_FALSE(b->has_valid_prev());
}
