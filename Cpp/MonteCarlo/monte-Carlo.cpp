#include <iostream>
#include <random>
#include <cmath> // Dla funkcji sqrt
#include <cstdlib> // Dla funkcji rand() i srand()
#include <ctime>   // Dla funkcji time()
#include <vector>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using namespace std;



// Funkcja do losowania liczby double w podanym zakresie
double losuj(std::mt19937& gen, double min, double max) {
    std::uniform_real_distribution<double> rozkład(min, max);
    return rozkład(gen);
}

double przyblizeniePi(int n){
    // Generator liczb losowych
    std::mt19937 gen{std::random_device{}()};
    // Rozklad jednorodny na przedziale -1.0 do 1.0
    std::uniform_real_distribution<double> losuj{0.0, 1.0};


    int a = 0;
    double x;
    double y;
    for (int i = 0; i < n; ++i) {
        x = losuj(gen);
        y = losuj(gen);
        if (std::sqrt(x*x + y*y) <= 1) {
            a++;
        }

    }

    float wynik = static_cast<float>(4 * a) / n;

    cout << "n = " << n << endl;
    std::cout << "a = " << a << "\n";
    
    // Iloraz
    std::cout << "Iloraz 4a/n przybliżenie liczby Pi: " << wynik << "\n";
    return wynik;
}

// Funkcja do zapisu danych do pliku
void zapiszDoPliku(const std::vector<double>& pi_values, const std::vector<int>& n_values) {
    std::ofstream file("dane.txt");
    if (file.is_open()) {
        for (size_t i = 0; i < n_values.size(); ++i) {
            file << pi_values[i] << " " << n_values[i] << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Nie udało się otworzyć pliku do zapisu." << std::endl;
    }
}

// Funkcja do rysowania wykresu punktowego za pomocą GNUplot
void rysujWykresGNUplot() {
    // Utwórzmy skrypt GNUplota, który wygeneruje wykres punktowy
    std::ofstream gnuplot_script("plot_script.gnu");
    if (gnuplot_script.is_open()) {
        gnuplot_script << "set terminal png\n";
        gnuplot_script << "set output 'wykres.png'\n";
        gnuplot_script << "set xlabel 'Wartosc n'\n"; // Zmieniamy etykietę osi X na "Wartosc n"
        gnuplot_script << "set ylabel 'Przyblizenie liczby Pi'\n"; // Zmieniamy etykietę osi Y na "Przyblizenie liczby Pi"
        gnuplot_script << "set title 'Wykres punktowy'\n";
        gnuplot_script << "set xrange [500:100000]\n"; // Ustawienie zakresu dla osi X
        gnuplot_script << "set label '' at 1,3.14 point pt 7 lc rgb 'blue'\n";
        gnuplot_script << "plot 'dane.txt' using 2:1 with points pt 7 lc rgb 'red', ";
        gnuplot_script << "'+' using (0):(3.14) with points pt 7 lc rgb 'blue' title 'Wartosc Pi'\n";
        gnuplot_script << "set arrow from 3.14,0 to 3.14,100 nohead lc rgb 'blue'\n";



        gnuplot_script.close();

        // Uruchommy GNUplot z utworzonym skryptem
        system("gnuplot plot_script.gnu");
    } else {
        std::cerr << "Nie udało się utworzyć skryptu GNUplota." << std::endl;
        return;
    }
}

int main()
{
    std::vector<int> n_values = {500, 600, 800, 1000, 5000, 6000, 8000, 10000, 50000, 60000, 80000, 100000};
    std::vector<double> pi_values;
    for (int n : n_values) {
        pi_values.push_back(przyblizeniePi(n));
    }

    // Wyświetl wartości n_values i odpowiadające im wartości pi_values
    std::cout << "n_values\t| pi_values" << std::endl;
    std::cout << "------------------------" << std::endl;
    for (size_t i = 0; i < n_values.size(); ++i) {
        std::cout << n_values[i] << "\t| " << pi_values[i] << std::endl;
    }

    // Zapisz dane do pliku
    zapiszDoPliku(pi_values, n_values);

    // Wygeneruj wykres punktowy za pomocą GNUplot
    rysujWykresGNUplot();
    
}