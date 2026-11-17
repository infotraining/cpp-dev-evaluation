#pragma once

/**
 * The lifecycle state of a workflow.
 */
namespace Solution
{
    enum class WorkflowState {
        Idle,
        Running,
        Completed,
        Failed
    };

    /**
     * A one-shot workflow state machine.
     *
     * A workflow can start only once. A running workflow can complete or fail;
     * terminal states cannot be changed.
     */
    class Workflow
    {
    public:
        /** Returns the current state without changing it. */
        WorkflowState state() const;

        /** Starts an idle workflow; returns false if it is not idle. */
        bool start();

        /** Completes a running workflow; returns false in any other state. */
        bool complete();

        /** Fails a running workflow; returns false in any other state. */
        bool fail();

    private:
        WorkflowState state_{WorkflowState::Idle};
    };
} // namespace Solution
