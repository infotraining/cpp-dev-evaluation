# Task 7: Cancellable Worker Coordination

Implement a worker group that starts a fixed number of `std::jthread`s. Each worker accepts a `std::stop_token`, waits at a shared `std::latch` startup gate, and then runs the supplied work callback. Provide operations to request stop and join all workers; destruction must not leave joinable threads behind.

The callback must cooperate with cancellation. Tests should use synchronization primitives rather than sleep-based timing.

## Scoring (0-3 points)

* **0:** Threads are leaked, shutdown hangs, or the task does not compile.
* **1:** Workers start, but cancellation or joining is incomplete.
* **2:** Stop requests and joining behave correctly.
* **3:** Startup coordination is sound, shutdown is deterministic, and sanitizer validation is clean where supported.
