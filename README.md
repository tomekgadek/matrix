# matrix

W ramach projektu należy:

1. Ograniczenie statycznie alokowanego kodu tam, gdzie jest to wskazane (czyli na pewno, przekazwyanie wszelkich macierzy do funkcji, alokacja macierzy o odpowiednim wymiarze zamiast marnowania miejsca na macierz o odpowiednio dużym rozmiarze etc.)
2. Dodanie funkcjonalności listy dwukierunkowej struktur. Funkcjonalnośc zostanie użyta to przechowywania zmiennych.

    Propozycja struktury:

    ```c
    struct matrix {
        double **mtrx;
        unsigned rows;
        unsigned cols;
    };

    struct variable {
        char label[10];         // etykieta zmiennej
        struct matrix *mtrx;    // wskaźnik na zmienną
        struct variable *next;  // wskaźnik na następny element listy
        struct variable *prev;  // wskaźnik na poprzedni element listy
    };
    ```

    Proponuję skalary wczytywać do tablicy o wymiarach 1x1 (notabene tak, jak to robi matlab) – znacznie mniej pisania kodu. Jeżeli ktoś bardzo chce, może użyc do tego celu unii, która encapsuluje strukturę macierz jak i zwykłą zmienną skalar. Następnie, zaimplementować funkcje dodające element (na początek, na koniec, oraz na i-tej pozycji), usuwające element(ostatni, początkowy oraz ity) oraz wyszukujące elementy zapisane na liście. Podobnie ma się rzecz w przypadku struktury macierz, warto napisać funkcje, które alokują macierz dla pola `**mtrx`, zwalniają po użyciu, itp.

3. Dodanie prostych funkcjonalności związanych z operacjami macierzowymi: dodawanie macierzy, odejmowanie, mnożenie. Wyszukiwanie maksymalnego i minimalnego elementu. Wyznaczanie normy i śladu macierzy.
4. Dodać zapisywanie do i wczytywanie zmiennych z pliku.
5. Połączenie interfejsu z funkcjonalnościami w taki sposób, aby można było wykonywać proste operacje, wpisując odpowiednie polecenia w linii komend, jak poniżej:

### Przykłady proponowanych komend (funkcji)

```bash
a = losowa(3,3) // wygenerowanie macierzy losowej o rozmiarze 3x3 oraz zapisanie jej w zmiennej
```

Jeżeli zmienna nie istnieje, zostaje utworzona, w przeciwnym przypadku zostaje nadpisana.

```bash
b = odwroc(a) //odwrócenie (znanej już na tym etapie) macierzy a i zapisanie jej w zmiennej b
c = a*b // pomnożenie macierzy a i b, zapisanie wyniku w c
d=[2 3 4;5 6 7;8.0 2 2]; - dodanie nowej zmiennej d i wczytanie do niej tablicy.
e=d-a // kolejna operacja
```

### Uruchomienie projektu

Kompilacja
```bash
make
```

Uruchomienie
```bash
./macierze
```

Czyszczenie plików wynikowych
```bash
make clean
```

### Brakujące funkcjonalności

+ Dostęp do elementów macierzy: brak obsługi składni nazwa_m(x,y). Obecnie nie można pobrać ani wyświetlić konkretnej wartości komórki macierzy przez CLI.
+ Operatory złożone: brak obsługi operatorów +=, -= oraz *=. Obecnie obsługiwane są tylko proste przypisania typu C = A + B.
+ Syntaktyka losowa(nazwa_m): obecnie funkcja losowa działa tylko jako losowa(x,y) wewnątrz wyrażenia (np. A = losowa(3,3)). brak obsługi formy, w której podaje się nazwę istniejącej macierzy, aby wypełnić ją losowymi danymi.
+ Syntaktyka zerowa(nazwa_m): podobnie jak wyżej, obsługiwane jest tylko zerowa(x,y) jako generator nowej macierzy.
+ Działania na tej samej macierzy (np. a = a * a): choć parser technicznie to obsłuży, obecna implementacja w `cli.c`
 tworzy kopię macierzy przy prostym przypisaniu, ale niekoniecznie optymalnie zarządza pamięcią w przypadku operacji A = A * B (może dojść do wycieku lub błędu, jeśli nie zwolnimy starej macierzy A przed przypisaniem nowej).

Podsumowując, najważniejsze braki to:

+ Dostęp do elementu macierzy (np. A(x,y))
+ Operatory złożone (np. +=, -=, *=)
+ Syntaktyka losowa(nazwa_m)
+ Syntaktyka zerowa(nazwa_m)
+ Działania na tej samej macierzy (np. a = a * a)