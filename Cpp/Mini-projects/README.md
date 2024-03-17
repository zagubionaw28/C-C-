[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/AFObrxuW)
# Lab 03: Funkcje

| Termin oddania | Punkty     |
|----------------|:-----------|
|    15.03.2024 23:00 |   4        |

--- 
Przekroczenie terminu o **n** zajęć wiąże się z karą:
- punkty uzyskanie za realizację zadania są dzielone przez **2<sup>n</sup>**.

--- 
## Zadanie 1 [1 pkt]
Liczba Armstronga to liczba, która jest sumą swoich cyfr podniesionych do potęgi, która jest liczbą cyfr tej liczby.

Przykłady:

- `9` jest liczbą Armstronga, ponieważ: `9 = 9^1 = 9`
- `10` nie jest liczbą Armstronga, ponieważ: `10 != 1^2 + 0^2 = 1`
- `153` jest liczbą Armstronga, ponieważ: `153 = 1^3 + 5^3 + 3^3 = 1 + 125 + 27 = 153`
- `154` nie jest liczbą Armstronga, ponieważ: `154 != 1^3 + 5^3 + 4^3 = 1 + 125 + 64 = 190`

Napisz funkcję, która jako parametr przyjmuje liczbę całkowitą i oddaje `1`, jeżeli liczba jest liczbą Armstronga oraz `0` w przeciwnym przypadku.

## Zadanie 2 [1 pkt]
Napisz funkcję, która sprawdza, czy zadana jako parametr liczba całkowita jest sześcianem pewnej liczby
całkowitej. Wynikiem działania funkcji ma być jeden, jeśli liczba jest sześcianem oraz zero w przeciwnym wypadku.
Przetestuj funkcję na wybranych przykładach.

## Zadanie 2 [2 pkt]
Napisz iteracyjną i rekurencyjną wersję funkcji obliczającej:
- [dwumian Newtona](https://pl.wikipedia.org/wiki/Symbol_Newtona)
- największy wspólny dzielnik ([algorytm Euklidesa](https://pl.wikipedia.org/wiki/Algorytm_Euklidesa))

Opierając się na programie z wykładu zmierz czas działania algorytmów i określ granice stosowalności w zależności od wartości parametrów.
