// Napisz iteracyjną i rekurencyjną wersję funkcji obliczającej:

// dwumian Newtona
// największy wspólny dzielnik (algorytm Euklidesa)
// Opierając się na programie z wykładu zmierz czas działania algorytmów i określ granice stosowalności w zależności od wartości parametrów.

#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

long silnia(int liczba) {

    long wynik = 1;
    while (liczba > 0) {
        wynik = wynik * liczba;
        liczba--;
    }
    // printf("%d%s", liczba, "\n");
    return wynik;    

}


long iteracjaNewtona(int n, int k) {
    long licznik = silnia(n);
    long mianownik1 = silnia(k);
    long mianownik2 = silnia(n-k);

    long wynik = (licznik/(mianownik1 * mianownik2));
    return wynik;
}


long silnia_reku(int liczba, long acc) {
    if (liczba > 0) {
        acc = acc * liczba;
        liczba--;
        return silnia_reku(liczba, acc);
    } else {
        return acc;
    }
}

long rekurencjaNewtona(int n, int k) {
    long licznik = silnia_reku(n, 1);
    long mianownik1 = silnia_reku(k, 1);
    long mianownik2 = silnia_reku(n-k, 1);

    long wynik = (licznik/(mianownik1 * mianownik2));

    return wynik;
}


int iteracjaEuklidesa(int n, int m) {
    if (n == 0 || m == 0) {
        return 0;
    }
    while (n != m) {
        if (n < m) {
            m -= n;
        } else {
            n -= m;
        }
    }
    return n;
}



int nwd_r_helper(const int number_1, const int number_2) {
    if (number_1 == number_2) return number_1;
    else if (number_1 < number_2) return nwd_r_helper(number_1, number_2 - number_1);
    else return nwd_r_helper(number_1 - number_2, number_2);
}

int rekurencjaEuklidesa(const int number_1, const int number_2, int (*function)(int, int)) {
    if (number_1 == 0 || number_2 == 0) return 0;
    else return function(number_1, number_2);
}

int main() {
    // Mierzenie czasu wykonania iteracyjnej i rekurencyjnej funkcji obliczającej dwumian Newtona

    auto start = high_resolution_clock::now();
    cout << "Iteracyjna Newtona dla (12,2): " << iteracjaNewtona(12, 2) << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Czas wykonania iteracyjnej Newtona: " << duration.count() << " mikrosekund" << endl;

    start = high_resolution_clock::now();
    cout << "Rekurencyjna Newtona dla (12,2): " << rekurencjaNewtona(12, 2) << endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Czas wykonania rekurencyjnej Newtona: " << duration.count() << " mikrosekund" << endl;

    // Mierzenie czasu wykonania iteracyjnej i rekurencyjnej funkcji obliczającej największy wspólny dzielnik (algorytm Euklidesa)

    start = high_resolution_clock::now();
    cout << "Iteracyjna Euklidesa dla (12,16): " << iteracjaEuklidesa(12, 16) << endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Czas wykonania iteracyjnej Euklidesa: " << duration.count() << " mikrosekund" << endl;

    start = high_resolution_clock::now();
    cout << "Rekurencyjna Euklidesa dla (12,16): " << rekurencjaEuklidesa(12, 16, nwd_r_helper) << endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Czas wykonania rekurencyjnej Euklidesa: " << duration.count() << " mikrosekund" << endl;

    return 0;

}