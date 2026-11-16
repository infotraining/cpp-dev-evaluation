# Zadanie 8: Kontenery STL i bezpieczeństwo iteratorów

## Polecenie
1. Zaimplementuj funkcję `void removeEvenNumbers(std::vector<int>& vec)`, która bezpiecznie usuwa wszystkie liczby parzyste z wektora (unikając unieważnienia iteratorów – użyj idiomu *erase-remove* lub pętli z `it = vec.erase(it)`).
2. Zaimplementuj funkcję `std::unordered_map<std::string, int> countWordFrequencies(const std::vector<std::string>& words)`, która zlicza liczbę wystąpień każdego słowa.

## Kryteria oceny (0-3 pkt)
- **0 pkt:** Błąd unieważnienia iteratorów (UB przy iteracji i usuwaniu z wektora).
- **1 pkt:** Poprawne zliczanie słów, ale nieoptymalne lub błędne usuwanie z wektora.
- **2 pkt:** Poprawne oba zadania przy użyciu pętli.
- **3 pkt:** Idiomatyczne użycie `std::remove_if` + `erase` oraz `operator[]` w `std::unordered_map`.
