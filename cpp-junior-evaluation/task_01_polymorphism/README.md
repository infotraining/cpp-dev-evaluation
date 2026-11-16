# Zadanie 1: Polimorfizm i wirtualny destruktor

## Polecenie
Zaimplementuj hierarchię klas reprezentujących figury geometryczne:
1. Abstrakcyjna klasa bazowa `Shape` posiadająca:
   - wirtualny destruktor,
   - czysto wirtualną metodę `double area() const = 0;`.
2. Klasa pochodna `Circle` przyjmująca w konstruktorze `double radius` (pole: $\pi r^2$, użyj `3.14159265358979323846`).
3. Klasa pochodna `Rectangle` przyjmująca w konstruktorze `double width, double height` (pole: $w \cdot h$).
4. Funkcja `double totalArea(const std::vector<std::unique_ptr<Shape>>& shapes)`, która sumuje pola wszystkich figur w wektorze (ignorując ewentualne `nullptr`).

## Kryteria oceny (0-3 pkt)
- **0 pkt:** Brak kompilacji, brak wirtualnego destruktora lub wycieki pamięci.
- **1 pkt:** Działające klasy, ale brak `override` lub `const` przy `area()`.
- **2 pkt:** Poprawna implementacja i wirtualny destruktor.
- **3 pkt:** Idiomatyczny kod Modern C++ (`override`, `const`, bezpieczna obsługa `nullptr`).
