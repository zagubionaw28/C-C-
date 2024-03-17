// Liczba Armstronga to liczba, która jest sumą swoich cyfr podniesionych do potęgi, która jest liczbą cyfr tej liczby.

// Przykłady:

// 9 jest liczbą Armstronga, ponieważ: 9 = 9^1 = 9
// 10 nie jest liczbą Armstronga, ponieważ: 10 != 1^2 + 0^2 = 1
// 153 jest liczbą Armstronga, ponieważ: 153 = 1^3 + 5^3 + 3^3 = 1 + 125 + 27 = 153
// 154 nie jest liczbą Armstronga, ponieważ: 154 != 1^3 + 5^3 + 4^3 = 1 + 125 + 64 = 190
// Napisz funkcję, która jako parametr przyjmuje liczbę całkowitą i oddaje 1, jeżeli liczba jest liczbą Armstronga oraz 0 w przeciwnym przypadku.

// testy jednostkowe!!!!!!

#include <iostream>
#include <cmath>

bool isArmstrongNumber(int number) {
    int originalNumber = number;
    int numDigits = 0;
    int sum = 0;

    // Obliczanie liczby cyfr w liczbie
    while (originalNumber != 0) {
        originalNumber /= 10;
        numDigits++;
    }

    originalNumber = number;

    // Obliczanie sumy cyfr podniesionych do potęgi
    while (originalNumber != 0) {
        int digit = originalNumber % 10;
        sum += pow(digit, numDigits);
        originalNumber /= 10;
    }

    // Sprawdzenie, czy suma jest równa oryginalnej liczbie
    return sum == number;
}

/**int main() {
    // Przykładowe testy
    std::cout << "9 jest liczba Armstronga: " << isArmstrongNumber(9) << std::endl;
    std::cout << "10 nie jest liczba Armstronga: " << isArmstrongNumber(10) << std::endl;
    std::cout << "153 jest liczba Armstronga: " << isArmstrongNumber(153) << std::endl;
    std::cout << "154 nie jest liczba Armstronga: " << isArmstrongNumber(154) << std::endl;

    return 0;
}**/

