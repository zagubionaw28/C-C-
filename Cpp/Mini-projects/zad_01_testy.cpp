#include <gtest/gtest.h>
#include "zad_01.cpp"

// Testy jednostkowe za pomocą Catch2
TEST(ArmstrongNumberTest, StartTests) {
    EXPECT_TRUE(isArmstrongNumber(9));    // 9 jest liczbą Armstronga
    EXPECT_FALSE(isArmstrongNumber(10));  // 10 nie jest liczbą Armstronga
    EXPECT_TRUE(isArmstrongNumber(153));  // 153 jest liczbą Armstronga
    EXPECT_FALSE(isArmstrongNumber(154)); // 154 nie jest liczbą Armstronga
}


// ++ -o test_01 zad_01_testy.cpp -lgtest -lgtest_main -pthread -I /usr/src/gtest/include -L /usr/src/gtest/lib/ -l:libgtest.a

// ./test_01

