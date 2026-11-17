# Task 11: Refactoring, Dependency Injection, and GMock

Refactor the order processor so inventory and notification services are injected through interfaces. Preserve the behavior that an order is notified only after inventory reservation succeeds.

The tests include an interaction-focused GMock mock and a simple stub with controlled behavior. Be prepared to explain when each test double is appropriate.

## Scoring (0-3 points)

* **0:** Behavior is incorrect or dependencies remain tightly coupled.
* **1:** Dependencies are injected, but tests do not isolate the service.
* **2:** Success and failure paths are tested with suitable test doubles.
* **3:** Clear responsibilities, interaction assertions where appropriate, and no notification after a failed reservation.
