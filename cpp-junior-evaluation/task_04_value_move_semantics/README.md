# Zadanie 4: Semantyka wartości i referencji

## Polecenie
1. Zaimplementuj strukturę `UserProfile` oraz funkcję `createProfile`:
   - `UserProfile` ma pola: `std::string username` oraz `std::vector<int> scores`.
   - Funkcja `UserProfile createProfile(std::string username, std::vector<int> scores)` powinna przenieść argumenty do zwracanej struktury za pomocą `std::move`, minimalizując liczbę kopii.
2. Zaimplementuj funkcję `int classifyValueCategory(int& x)` zwracającą `1` (dla lvalue) oraz `int classifyValueCategory(int&& x)` zwracającą `2` (dla rvalue).
3. Zaimplementuj funkcję `int forwardTest()`, która tworzy zmienną `int&& rref = 42;` i przekazuje ją do `classifyValueCategory(rref)` (powinno zwrócić `1`, ponieważ nazwana referencja rvalue jest lvalue!).

## Kryteria oceny (0-3 pkt)
- **0 pkt:** Błędne zrozumienie `lvalue`/`rvalue` lub brak kompilacji.
- **1 pkt:** Poprawne przeładowania, ale brak użycia `std::move` w `createProfile`.
- **2 pkt:** Poprawne `std::move`, drobne nieścisłości w kategoriach wartości.
- **3 pkt:** Pełne zrozumienie kategorii wartości i optymalizacji przekazywania parametrów.
