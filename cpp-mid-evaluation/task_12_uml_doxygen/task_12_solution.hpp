/**
 * \file task_12_solution.hpp
 * \brief One-shot workflow state machine and its lifecycle states.
 */
#pragma once

/**
 * \mainpage Workflow API
 *
 * \section overview Overview
 * Solution::Workflow models a one-shot lifecycle. It is created
 * \ref Solution::WorkflowState::Idle "Idle", can be started once, and then ends in exactly one
 * terminal state (completed or failed).
 *
 * \section lifecycle Lifecycle
 * \dot
 * digraph workflow {
 *     rankdir=LR;
 *     node [shape=box, style=rounded];
 *     start [shape=point];
 *     Idle; Running; Completed; Failed;
 *     start -> Idle;
 *     Idle -> Running [label="start()"];
 *     Running -> Completed [label="complete()"];
 *     Running -> Failed [label="fail()"];
 * }
 * \enddot
 *
 * \section sequence Typical usage
 * \msc
 * Client, Workflow;
 * Client => Workflow [label="start()"];
 * Client << Workflow [label="true"];
 * Client => Workflow [label="complete()"];
 * Client << Workflow [label="true"];
 * Client => Workflow [label="fail()"];
 * Client << Workflow [label="false (terminal state)"];
 * \endmsc
 *
 * \see docs/design_solution.md for the Mermaid class and state diagrams.
 */

/** \brief Namespace of the reference solution. */
namespace Solution
{
    /**
     * \brief The lifecycle state of a workflow.
     *
     * Valid transitions: Idle -> Running, Running -> Completed, Running -> Failed.
     * Completed and Failed are terminal.
     */
    enum class WorkflowState {
        Idle,      ///< Created, not started yet (initial state).
        Running,   ///< Started and not finished yet.
        Completed, ///< Finished successfully (terminal).
        Failed     ///< Finished with a failure (terminal).
    };

    /**
     * \brief A one-shot workflow state machine.
     *
     * \details A workflow can start only once. A running workflow can complete or fail;
     * terminal states cannot be changed. Transition methods never throw: an invalid
     * transition is reported by returning \c false and leaves the state unchanged.
     *
     * \par Example
     * \code{.cpp}
     * Solution::Workflow w;
     * w.start();    // Idle -> Running
     * w.complete(); // Running -> Completed
     * w.fail();     // returns false, state stays Completed
     * \endcode
     *
     * \note Not thread-safe; synchronize externally when sharing an instance.
     */
    class Workflow
    {
    public:
        /**
         * \brief Returns the current state without changing it.
         * \return The current WorkflowState.
         */
        WorkflowState state() const;

        /**
         * \brief Starts the workflow.
         * \pre The workflow is expected to be in WorkflowState::Idle.
         * \post On success the state is WorkflowState::Running.
         * \retval true  The workflow was idle and is now running.
         * \retval false The workflow was not idle; the state is unchanged.
         */
        bool start();

        /**
         * \brief Completes a running workflow.
         * \post On success the state is WorkflowState::Completed (terminal).
         * \retval true  The workflow was running and is now completed.
         * \retval false The workflow was not running; the state is unchanged.
         */
        bool complete();

        /**
         * \brief Fails a running workflow.
         * \post On success the state is WorkflowState::Failed (terminal).
         * \retval true  The workflow was running and is now failed.
         * \retval false The workflow was not running; the state is unchanged.
         */
        bool fail();

    private:
        WorkflowState state_{WorkflowState::Idle}; ///< Current lifecycle state.
    };
} // namespace Solution
