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
func randomDifferentNumber(exclude, exclude2 int) int {
    // Wylosowanie liczby
    randomNum := rand.Intn(3)

    // Sprawdzenie, czy wylosowana liczba jest różna od wartości zmiennej
    for ((randomNum == exclude) || (randomNum == exclude2)) {
        // Jeśli nie, wylosuj nową liczbę
        randomNum = rand.Intn(3)
    }

    // Zwrócenie wylosowanej liczby
    return randomNum
}

func main() {

	rand.Seed(time.Now().UnixNano())

    // Wywołanie funkcji do generowania losowej liczby całkowitej z zakresu [min, max]
    // liczba_rund := randInt(1, 100)
	liczba_rund := 100

    // Wyświetlenie wylosowanej liczby
    fmt.Println("Wylosowana liczba całkowita:", liczba_rund)
	// Inicjalizacja generatora liczb pseudolosowych
    rand.Seed(time.Now().UnixNano())

    // Generowanie losowej wartości typu bool
    strategia_gracza  := randBool()

    // Wyświetlenie wylosowanej wartości
    fmt.Println("Losowa wartość:", strategia_gracza)
	// true - oznacza, że został przy swoim pudełku, false - oznacza, że wziął inne pudełko

	wynik := 0
	
	//for 
	for i := 0; i < liczba_rund; i++ {
		fmt.Println("Runda:", i+1)

		// Tworzenie tablicy o długości 3 i wypełnianie jej zerami
		box := [3]int{0, 0, 0}

		// Losowanie indeksu, w którym umieścimy 1
		index := rand.Intn(3)
	
		// Umieszczenie 1 w wylosowanym indeksie
		box[index] = 1

		losowanieUczestnika := rand.Intn(3)

		toOdpadaBoPuste := randomDifferentNumber(losowanieUczestnika, index)
		fmt.Println("--------------", losowanieUczestnika, index, toOdpadaBoPuste)

		if !strategia_gracza {
			if losowanieUczestnika == index {
				wynik++
			}
		} else {
			losowanieUczestnika = randomDifferentNumber(losowanieUczestnika, toOdpadaBoPuste)
			if losowanieUczestnika == index {
				wynik++
			}
		}
		// Wyświetlenie zawartości tablicy
		fmt.Println("Tablica box po losowaniu:", box)
    }

	fmt.Println("Wynik wygranych prób:", wynik, "\nLiczba porażek:", liczba_rund-wynik)
 

}

// Badania:
// Dla ilość_prób = 10
// boolean wygrane/przegrane
// true:    9/1,      5/5,       6/4
// false:   2/8,      1/9,       5/5


// Dla różnych liczb : 
// boolean     ilość_prób -> wygrane
// true:         58 -> 39,     79 -> 46,      82 -> 52,       58 -> 38,      32 -> 17
// false:        56 -> 17,     51 -> 15,      43 -> 16,       93 -> 30,      100 -> 37


// Dla n= 100




// Gracz ma za zadanie odgadnąć w którym z trzech pudełek umieszczona jest nago-
// da. Po dokonaniu wyboru prwadzący grę odsłania jedną z poostałych bramek
// otwiera jedno z pozostałych pudełek, zawsze to, w którym nie ma nagrody. Na-
// stępnie prowadzący pyta gracza, czy ten chce pozosać przy swoim początkowym
// wyborze, czy chce zmienić swój typ na pozostałe nieotwarte pudełko. Czy decyzja
// gracza o zmianie wyboru pudełka ma wpływ na jegoszanse wygranej? Jaka strate-
// gia gry jest optymalna?

// Zadanie polega na napisaniu prostego programu, który zasymuluje powyższą grę.
// Parametry początkowe programu to:
// liczba_rund - liczba rund rozgrywki
// strategia_gracza - zmienna określająca czy gracz będzie zmieniał swój wy-
// bór czy nie
// Na końcu program ma zwracać zbiorczą liczbę wygranych i porażek (5 pkt)
// Jeżeli ktoś miałby ochotę popracować więcej: jak zmienią się wnioski dotyczące
// strategii jeżeli pudeł będzie N (na przykład n=100)? Ile pudeł powinien otworzyć
// prowadzący by wnioski płynące z wariantu z trzema pudłami były również praw-
// dziwe w tym przypadku? (3 pkt)