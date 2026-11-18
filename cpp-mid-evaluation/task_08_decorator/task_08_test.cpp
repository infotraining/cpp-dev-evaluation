#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>

#ifdef USE_SOLUTION
#include "task_08_solution.hpp"
using namespace Solution;
#else
#include "task_08.hpp"
#endif

TEST(DecoratorTest, DecoratorsComposeAndDelegate)
{
    auto recorder = std::make_unique<RecordingSink>();
    auto* recorder_view = recorder.get();
    auto sink = std::make_unique<AuditSink>(
        std::make_unique<ValidatingSink>(std::move(recorder)));

    sink->send("hello");
    ASSERT_EQ(recorder_view->messages().size(), 1u);
    EXPECT_EQ(recorder_view->messages()[0], "hello");
    auto* audit = static_cast<AuditSink*>(sink.get());
    EXPECT_EQ(audit->audit_log(), (std::vector<std::string>{"hello"}));
}

TEST(DecoratorTest, ValidationRejectsEmptyMessages)
{
    auto sink = std::make_unique<ValidatingSink>(std::make_unique<RecordingSink>());
#ifdef USE_SOLUTION
    EXPECT_THROW(sink->send(""), std::invalid_argument);
#else
    sink->send("");
    SUCCEED();
#endif
}

TEST(DecoratorTest, DecoratorOrderControlsWhetherRejectedMessageIsAudited)
{
#ifdef USE_SOLUTION
    auto sink = std::make_unique<AuditSink>(
        std::make_unique<ValidatingSink>(
            std::make_unique<RecordingSink>()));
    auto* audit = static_cast<AuditSink*>(sink.get());
    EXPECT_THROW(sink->send(""), std::invalid_argument);
    EXPECT_EQ(audit->audit_log(), (std::vector<std::string>{""}));
#else
    GTEST_SKIP() << "Starter code has no decorator implementation yet.";
#endif
}

TEST(DecoratorTest, RejectsNullWrappedService)
{
#ifdef USE_SOLUTION
    EXPECT_THROW((ValidatingSink(nullptr)), std::invalid_argument);
#else
    GTEST_SKIP() << "Starter code has no validation yet.";
#endif
}
