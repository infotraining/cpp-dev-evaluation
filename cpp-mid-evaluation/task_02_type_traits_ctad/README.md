# Task 2: Type Traits and CTAD

Implement a `ValueBox<T>` that stores a value and a `format_value` function for arithmetic and text values. Provide a custom `is_supported_value` trait, use `if constexpr` for type-specific formatting, and add a deduction guide so a string literal creates a `ValueBox<std::string>`.

Unsupported types should be rejected at compile time. Keep that contract clear in the public API.

## Scoring (0-3 points)

* **0:** Does not compile or incorrectly handles supported types.
* **1:** Formatting works for one category but type deduction or compile-time dispatch is missing.
* **2:** Custom trait and CTAD work for the supported types.
* **3:** Correct cv/ref-aware trait behavior, string-literal deduction, and clear compile-time rejection of unsupported types.
