# Zadanie 2: Smart Pointers (`std::unique_ptr` i `std::weak_ptr`)

## Polecenie
1. Zaimplementuj klasę `PacketBuffer`, która alokuje tablicę `uint8_t` o podanym rozmiarze (`size`) przy użyciu `std::make_unique<uint8_t[]>(size)` i wypełnia ją zerami.
   - Metoda `size_t size() const` zwraca rozmiar bufora.
   - Metoda `std::unique_ptr<uint8_t[]> releaseBuffer()` przekazuje własność bufora na zewnątrz (za pomocą `std::move`), zerując jednocześnie wewnętrzny rozmiar do `0`.
2. Rozwiąż problem cyklicznej referencji między klasami `NodeA` i `NodeB`:
   - `NodeA` posiada `std::shared_ptr<NodeB> next`.
   - `NodeB` powinien posiadać `std::weak_ptr<NodeA> prev` (zamiast `shared_ptr`), aby uniknąć wycieku pamięci.
   - Metoda `bool NodeB::hasValidPrev() const` zwraca `true`, jeśli obiekt `NodeA` nadal istnieje.

## Kryteria oceny (0-3 pkt)
- **0 pkt:** Wyciek pamięci lub błąd kompilacji przy kopiowaniu `unique_ptr`.
- **1 pkt:** Poprawne użycie `unique_ptr`, ale brak rozwiązania cyklu `weak_ptr`.
- **2 pkt:** Poprawne oba elementy, brak zerowania rozmiaru po `releaseBuffer()`.
- **3 pkt:** Pełna, bezpieczna implementacja z użyciem `std::move` i `.expired()` / `.lock()`.
