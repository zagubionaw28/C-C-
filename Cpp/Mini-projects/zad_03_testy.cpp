#include <gtest/gtest.h>
// #include "zad_03.cpp"
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

unsigned long long int silnia(int liczba) {

    unsigned long long int wynik = 1;
    while (liczba > 0) {
        wynik = wynik * liczba;
        liczba--;
    }
    return wynik;    

}


unsigned long long int iteracjaNewtona(int n, int k) {
    unsigned long long int licznik = silnia(n);
    unsigned long long int mianownik1 = silnia(k);
    unsigned long long int mianownik2 = silnia(n-k);

    unsigned long long int wynik = (licznik/(mianownik1 * mianownik2));
    return wynik;
}


unsigned long long int silnia_reku(int liczba, unsigned long long int acc) {
    if (liczba > 0) {
        acc = acc * liczba;
        liczba--;
        // cout << acc << endl;
        // cout << liczba << endl;
        return silnia_reku(liczba, acc);
    } else {
        return acc;
    }
}

unsigned long long int rekurencjaNewtona(int n, int k) {
    unsigned long long int licznik = silnia_reku(n, 1);
    unsigned long long int mianownik1 = silnia_reku(k, 1);
    unsigned long long int mianownik2 = silnia_reku(n-k, 1);

    unsigned long long int wynik = (licznik/(mianownik1 * mianownik2));

    return wynik;
}


unsigned long long int iteracjaEuklidesa(unsigned long long int n, unsigned long long int m) {
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



unsigned long long int nwd_r_helper(unsigned long long int number_1, unsigned long long int number_2) {
    if (number_1 == number_2) return number_1;
    else if (number_1 < number_2) return nwd_r_helper(number_1, number_2 - number_1);
    else return nwd_r_helper(number_1 - number_2, number_2);
}

unsigned long long int rekurencjaEuklidesa(unsigned long long int number_1, unsigned long long int number_2, unsigned long long int (*function)(unsigned long long int, unsigned long long int)) {
    if (number_1 == 0 || number_2 == 0) return 0;
    else return function(number_1, number_2);
}

// iteracjaNewtona 
TEST(NewtonTest, Iteration1) {
    EXPECT_EQ(924, iteracjaNewtona(12, 6));
}

TEST(NewtonTest1, Iteration11) {
    EXPECT_EQ(1.716, iteracjaNewtona(13, 6));
}

// rekurencjaNewtona
TEST(NewtonTest2, Recursion1) {
    EXPECT_EQ(924, rekurencjaNewtona(12, 6));
}

TEST(NewtonTest22, Recursion11) {
    EXPECT_EQ(1.716, rekurencjaNewtona(13, 6));
}

// iteracjaEuklidesa
TEST(EuclidTest, Iteration2) {
    EXPECT_EQ(4, iteracjaEuklidesa(12, 16));
}
// jak dodam 0 więcej to nie wyjdzie
TEST(EuclidTest1, Iteration21) {
    EXPECT_EQ(18446744073709551615ULL, iteracjaEuklidesa(18446744073709551615ULL, 18446744073709551615ULL));
}

// rekurencjaEuklidesa
TEST(EuclidTest2, Recursion2) {
    EXPECT_EQ(4, rekurencjaEuklidesa(12, 16, nwd_r_helper));
}
// jak dodam 0 więcej to nie wyjdzie
TEST(EuclidTest22, Recursion22) {
    EXPECT_EQ(18446744073709551615ULL, rekurencjaEuklidesa(18446744073709551615ULL, 18446744073709551615ULL, nwd_r_helper));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}