#include "task_12_solution.hpp"

namespace Solution
{
WorkflowState Workflow::state() const
{
    return state_;
}

bool Workflow::start()
{
    if (state_ != WorkflowState::Idle)
    {
        return false;
    }
    state_ = WorkflowState::Running;
    return true;
}

bool Workflow::complete()
{
    if (state_ != WorkflowState::Running)
    {
        return false;
    }
    state_ = WorkflowState::Completed;
    return true;
}

bool Workflow::fail()
{
    if (state_ != WorkflowState::Running)
    {
        return false;
    }
    state_ = WorkflowState::Failed;
    return true;
}
}
