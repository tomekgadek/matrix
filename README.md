# matrix

W ramach projektu należy:

1. Ograniczenie statycznie alokowanego kodu tam, gdzie jest to wskazane (czyli na pewno, przekazwyanie wszelkich macierzy do funkcji, alokacja macierzy o odpowiednim wymiarze
zamiast marnowania miejsca na macierz o odpowiednio dużym rozmiarze etc.)
2. Dodanie funkcjonalności listy dwukierunkowej struktur (dodać pliki `mylist.c` i `mylist.h`) – funkcjonalnośc zostanie użyta to przechowywania zmiennych.

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

3. Dodanie prostych funkcjonalności związanych z operacjami macierzowymi: dodawanie macierzy, odejmowanie, mnożenie.Wyszukiwanie maksymalnego i minimalnego elementu. Wyznaczanie normy i śladu macierzy.
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
