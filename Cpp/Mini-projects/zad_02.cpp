// Napisz funkcję, która sprawdza, czy zadana jako parametr liczba całkowita jest sześcianem pewnej liczby całkowitej. Wynikiem działania funkcji ma być jeden, jeśli liczba jest sześcianem oraz zero w przeciwnym wypadku. Przetestuj funkcję na wybranych przykładach.


#include <iostream>
#include <cmath>

bool isCube(int number) {
    int cubeRoot = round(pow(number, 1.0 / 3.0));
    return cubeRoot * cubeRoot * cubeRoot == number;
}

// int main() {
//     // Przykładowe testy
//     std::cout << "27 jest sześcianem pewnej liczby całkowitej: " << isCube(27) << std::endl;
//     std::cout << "64 jest sześcianem pewnej liczby całkowitej: " << isCube(64) << std::endl;
//     std::cout << "100 nie jest sześcianem pewnej liczby całkowitej: " << isCube(100) << std::endl;

//     return 0;
// }

