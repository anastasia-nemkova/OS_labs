#include "gtest/gtest.h"
#include "realizations.hpp"

TEST(FourthLabTest, DerivativeStaticTest) {
    float result = Derivative(0.0, 0.1);
    EXPECT_FLOAT_EQ(result, -0.049958348);
}

TEST(FourthLabTest, SquareStaticTest) {
    float result = Square(2.0, 3.0);
    EXPECT_FLOAT_EQ(result, 6.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

