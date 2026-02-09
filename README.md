# matrix

Kalkulator macierzowy w stylu MATLAB-a, zaimplementowany w języku C z polskojęzycznym interfejsem CLI. Użytkownicy mogą tworzyć, modyfikować i wykonywać operacje na macierzach za pomocą interaktywnej linii poleceń.

## Kompilacja i uruchomienie

```bash
# Kompilacja projektu
make

# Uruchomienie aplikacji
./macierze

# Czyszczenie plików wynikowych
make clean
```

## Architektura

### Struktura modułów

- **cli/** - Interfejs linii poleceń i parser wyrażeń. Zarządza pętlą REPL, parsuje dane wejściowe użytkownika i przekazuje je do odpowiednich funkcji obsługi. Zawiera ewaluator wyrażeń (`eval_expression`), który obsługuje literały, wywołania funkcji i operacje binarne.

- **matrix/** - Podstawowa struktura danych macierzy i operacje na niej. Zapewnia dynamiczną alokację pamięci dla macierzy, operacje arytmetyczne (dodawanie, odejmowanie, mnożenie), obliczanie wyznacznika (rozwinięcie Laplace'a), odwracanie macierzy oraz operacje I/O na plikach.

- **variables/** - Lista dwukierunkowa do przechowywania zmiennych. Zmienne mapują etykiety tekstowe na wskaźniki do macierzy. Obsługuje automatyczne zastępowanie przy ponownym przypisaniu istniejących zmiennych.

- **gui/** - Proste wyświetlanie menu (baner startowy i podpowiedź pomocy).

- **help/** - Wczytuje i wyświetla tekst pomocy z plików.

- **data/** - Katalog do trwałego przechowywania macierzy (pliki zapisywane/wczytywane przez polecenia `zapisz`/`wczytaj`).

### Główne struktury danych

```c
struct matrix {
    double **mtrx;   // dynamiczna tablica 2D wartości
    unsigned rows;   // liczba wierszy
    unsigned cols;   // liczba kolumn
};

struct variable {
    char label[10];         // nazwa zmiennej
    struct matrix *mtrx;    // wskaźnik na macierz
    struct variable *next;  // lista dwukierunkowa
    struct variable *prev;
};
```

### Polecenia CLI

- `a = losowa(3,3)` - Utworzenie losowej macierzy
- `b = losowa(a)` - Utworzenie losowej macierzy o wymiarach takich jak `a`
- `a = zerowa(3,3)` - Utworzenie macierzy zerowej
- `b = zerowa(a)` - Utworzenie macierzy zerowej o wymiarach takich jak `a`
- `b = odwroc(a)` - Odwrócenie macierzy
- `c = a + b`, `c = a - b`, `c = a * b` - Operacje arytmetyczne
- `d = [1 2 3; 4 5 6]` - Literał macierzy (średnik oddziela wiersze)
- `a(1,2)` - Dostęp do elementu w wierszu 1, kolumnie 2 (indeksowanie od 1)
- `wyzn(a)` - Obliczenie wyznacznika
- `zapisz(a)` - Zapis macierzy do pliku `data/a`
- `wczytaj(a)` - Wczytanie macierzy z pliku `data/a`
- `pomoc` - Wyświetlenie pomocy
- `exit` - Wyjście z programu

## Znane ograniczenia

Następujące funkcje udokumentowane w `demo/pomoc.txt` NIE są jeszcze zaimplementowane:

- Operatory złożone: `+=`, `-=`, `*=`

## Konwencje kodu

- Własność pamięci: Funkcje zwracające `Matrix*` przekazują własność do wywołującego (wywołujący musi wywołać `free_matrix`)
- Przechowywanie zmiennych: `add_variable` przejmuje własność wskaźnika do macierzy i zwolni istniejące macierze przy nadpisywaniu
- Obsługa błędów: Funkcje zwracają `NULL` w przypadku niepowodzenia; wyznacznik zwraca `NAN` dla macierzy niekwadratowych
