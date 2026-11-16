# Zadanie 4: Semantyka wartości i referencji

## Polecenie
1. Zaimplementuj strukturę `UserProfile` oraz funkcję `create_profile`:
   - `UserProfile` ma pola: `std::string username` oraz `std::vector<int> scores`.
   - Funkcja `UserProfile create_profile(std::string username, std::vector<int> scores)` powinna przenieść argumenty do zwracanej struktury za pomocą `std::move`, minimalizując liczbę kopii.
2. Zaimplementuj funkcję `int classify_value_category(int& x)` zwracającą `1` (dla lvalue) oraz `int classify_value_category(int&& x)` zwracającą `2` (dla rvalue).
3. Zaimplementuj funkcję `int forward_test()`, która tworzy zmienną `int&& rref = 42;` i przekazuje ją do `classify_value_category(rref)` (powinno zwrócić `1`, ponieważ nazwana referencja rvalue jest lvalue!).

## Kryteria oceny (0-3 pkt)
- **0 pkt:** Błędne zrozumienie `lvalue`/`rvalue` lub brak kompilacji.
- **1 pkt:** Poprawne przeładowania, ale brak użycia `std::move` w `create_profile`.
- **2 pkt:** Poprawne `std::move`, drobne nieścisłości w kategoriach wartości.
- **3 pkt:** Pełne zrozumienie kategorii wartości i optymalizacji przekazywania parametrów.
