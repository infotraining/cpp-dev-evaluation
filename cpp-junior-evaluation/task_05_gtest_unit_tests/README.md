# Zadanie 5: Pisanie testów jednostkowych (Google Test)

## Polecenie
Dana jest gotowa klasa `BankAccount` w pliku nagłówkowym. Twoim zadaniem jest napisanie zestawu testów jednostkowych w pliku `starter.cpp` (który w tym zadaniu jest plikiem z testami kandydata!):
1. Utwórz klasę Fixture `BankAccountTest : public ::testing::Test` inicjalizującą konto z saldem `100.0`.
2. Napisz minimum 4 testy `TEST_F`:
   - `DepositIncreasesBalance`: wpłata `50.0` daje saldo `150.0`.
   - `DepositNegativeThrows`: wpłata `-10.0` lub `0.0` rzuca `std::invalid_argument`.
   - `WithdrawValidAmount`: wypłata `40.0` daje saldo `60.0`.
   - `WithdrawOverBalanceThrows`: wypłata `150.0` rzuca `std::runtime_error`, a saldo pozostaje `100.0`.

## Kryteria oceny (0-3 pkt)
- **0 pkt:** Testy nie kompilują się lub nie sprawdzają wyjątków.
- **1 pkt:** Zwykłe makra `TEST` bez `TEST_F` lub brak sprawdzenia wszystkich ścieżek błędów.
- **2 pkt:** Poprawne `TEST_F`, ale użycie `EXPECT_EQ` zamiast `EXPECT_DOUBLE_EQ` dla liczb zmiennoprzecinkowych.
- **3 pkt:** Kompletny zestaw `TEST_F`, `EXPECT_DOUBLE_EQ`, `EXPECT_THROW` oraz weryfikacja spójności stanu po wyjątku.
