#include <gtest/gtest.h>
#include "zad_02.cpp"

// Testy jednostkowe
TEST(CubeTest, PositiveNumbers) {
    EXPECT_TRUE(isCube(27));   // 27 jest sześcianem
    EXPECT_TRUE(isCube(64));   // 64 jest sześcianem
}

TEST(CubeTest, NegativeNumbers) {
    EXPECT_FALSE(isCube(100)); // 100 nie jest sześcianem
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// g++ -o test_02 zad_02_testy.cpp -lgtest -lgtest_main -pthread
//  -I /usr/src/gtest/include -L /usr/src/gtest/lib/ -l:libgtest.a

// ./test_02
