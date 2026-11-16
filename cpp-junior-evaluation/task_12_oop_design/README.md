# Zadanie 12: Object-Oriented Programming (Enkapsulacja i Kompozycja)

## Polecenie
1. **Enkapsulacja i niezmienniki:** Zaimplementuj klasę `SimpleDate(int day, int month, int year)`:
   - Waliduj poprawność daty w konstruktorze oraz metodzie `set_month(int month)`: `year >= 1900`, `1 <= month <= 12`, `1 <= day <= 31`. W razie błędu rzuć `std::invalid_argument`, nie zmieniając stanu obiektu.
2. **Kompozycja ponad dziedziczenie:** Zaimplementuj interfejs `ILogger` (`virtual void log(const std::string& msg) = 0;`) oraz klasę `NotificationService`, która przyjmuje `ILogger&` przez konstruktor (Dependency Injection) i w metodzie `send_alert(const std::string& user)` wywołuje `logger_.log("Alert sent to: " + user)`.

## Kryteria oceny (0-3 pkt)
- **0 pkt:** Publiczne pola bez walidacji lub użycie dziedziczenia zamiast kompozycji.
- **1 pkt:** Walidacja tylko w konstruktorze, brak walidacji w `set_month()`.
- **2 pkt:** Poprawna enkapsulacja i wstrzykiwanie zależności przez interfejs.
- **3 pkt:** Pełna ochrona niezmienników (silna gwarancja wyjątków) oraz czysta kompozycja.
