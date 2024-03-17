package main

import (
    "fmt"
    "math/rand"
    "time"
)
// JEŚLI JEST FAŁSZ ZOSTAJEMY PRZY SWOIM PUDEŁKU, JEŚLI PRAWDA BIERZEMY DRUGIE PUDEŁKO

// Funkcja do generowania losowej wartości typu bool
func randBool() bool {
    return rand.Intn(2) == 0 // Zwraca prawdę (true), jeśli liczba jest równa 0, w przeciwnym razie fałsz (false)
}

func randInt(min, max int) int {
    // Sprawdzenie, czy wartości min i max są poprawne
    if min >= max {
        panic("min musi być mniejsze niż max")
    }

    // Generowanie losowej liczby całkowitej z zakresu [min, max]
    return rand.Intn(max-min+1) + min
}

// Funkcja do losowania liczby różnej od danej liczby
func randomDifferentNumber(exclude int, exclude2 int, n int, array *[]int, toDelete int) {
	for toDelete > 0 {
		for i, value := range *array {
			if toDelete > 0 {
				if i != exclude && i != exclude2 && value != -1 {
					(*array)[i] = -1 // Zmiana wartości w tablicy za pomocą wskaźnika
					toDelete--
					// fmt.Println("xxxxxxxxxxxxxx", *array, value, i)
				}
			}
		}
	}
}



// Funkcja do losowania liczby różnej od danej liczby
func randomDifferentNumber2(exclude int, n int, array []int) int {
    // Wylosowanie liczby
	randomNum := 0
    czyJuż := 0

	for i, value := range array {
		if czyJuż == 0 && exclude != i && value != -1 {
			randomNum = i
			czyJuż = 1
		}
	}

    

    // Zwrócenie wylosowanej liczby
    return randomNum
}

func main() {

	rand.Seed(time.Now().UnixNano())

    // Wywołanie funkcji do generowania losowej liczby całkowitej z zakresu [min, max]
    // liczba_rund := randInt(1, 100)
	liczba_rund := 1000

    // Wyświetlenie wylosowanej liczby
    fmt.Println("Wylosowana liczba całkowita:", liczba_rund)
	// Inicjalizacja generatora liczb pseudolosowych
    rand.Seed(time.Now().UnixNano())

    // Generowanie losowej wartości typu bool
    strategia_gracza  := true

    // Wyświetlenie wylosowanej wartości
    fmt.Println("Losowa wartość:", strategia_gracza)
	// true - oznacza, że został przy swoim pudełku, false - oznacza, że wziął inne pudełko

	wynik := 0

	n := 10

	toDelete := 6
	
	//for 
	for i := 0; i < liczba_rund; i++ {
		fmt.Println("Runda:", i+1)

		// Tworzenie tablicy o długości n i wypełnianie jej zerami
		box := make([]int, n) 

		// Losowanie indeksu, w którym umieścimy 1
		index := rand.Intn(n)
	
		// Umieszczenie 1 w wylosowanym indeksie
		box[index] = 1

		// // Tablica odrzuconych indeksów pudełek
		// tablicaOdrzuconych := make([]int, toDelete)

		losowanieUczestnika := rand.Intn(n)

		randomDifferentNumber(losowanieUczestnika, index, n, &box, toDelete)

		fmt.Println("--------------", losowanieUczestnika, index, box)

		if !strategia_gracza {
			if losowanieUczestnika == index {
				wynik++
			}

		} else {
			losowanieUczestnika = randomDifferentNumber2(losowanieUczestnika, n, box)
			fmt.Println("PO ZMIANIE -----------:", losowanieUczestnika)
			if losowanieUczestnika == index {
				wynik++
			}
		}
		// Wyświetlenie zawartości tablicy
		fmt.Println("Tablica box po losowaniu:", box)
    }

	fmt.Println("Wynik wygranych prób:", wynik, "\nLiczba porażek:", liczba_rund-wynik)
	// Wyświetlenie wylosowanej wartości
    fmt.Println("Losowa wartość:", strategia_gracza)
 

}