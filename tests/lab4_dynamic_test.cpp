#include "gtest/gtest.h"
#include <dlfcn.h>

typedef float (*DerivativeFunc)(float, float);
typedef float (*SquareFunc)(float, float);

TEST(FoufthLabTest, DerivativeDynamicTest) {
    void* libraryHandle = dlopen(getenv("PATH_TO_LIB1"), RTLD_LAZY);
    ASSERT_TRUE(libraryHandle != nullptr);

    DerivativeFunc Derivative = reinterpret_cast<DerivativeFunc>(dlsym(libraryHandle, "Derivative"));
    ASSERT_TRUE(Derivative != nullptr);

    float result = Derivative(0.0, 0.1);
    ASSERT_FLOAT_EQ(result, -0.049958348);

    dlclose(libraryHandle);
}

TEST(FoufthLabTest, SquareDynamicTest) {
    void* libraryHandle = dlopen(getenv("PATH_TO_LIB2"), RTLD_LAZY);
    ASSERT_TRUE(libraryHandle != nullptr);

    SquareFunc Square = reinterpret_cast<SquareFunc>(dlsym(libraryHandle, "Square"));
    ASSERT_TRUE(Square != nullptr);

    float result = Square(2.0, 3.0);
    ASSERT_FLOAT_EQ(result, 3.0);

    dlclose(libraryHandle);
}

TEST(FoufthLabTest, SwitchLibraryTest) {
    void* libraryHandle1 = dlopen(getenv("PATH_TO_LIB1"), RTLD_LAZY);
    ASSERT_TRUE(libraryHandle1 != nullptr);

    DerivativeFunc Derivative1 = reinterpret_cast<DerivativeFunc>(dlsym(libraryHandle1, "Derivative"));
    ASSERT_TRUE(Derivative1 != nullptr);
    SquareFunc Square1 = reinterpret_cast<SquareFunc>(dlsym(libraryHandle1, "Square"));
    ASSERT_TRUE(Square1 != nullptr);

    void* libraryHandle2 = dlopen(getenv("PATH_TO_LIB2"), RTLD_LAZY);
    ASSERT_TRUE(libraryHandle2 != nullptr);

    DerivativeFunc Derivative2 = reinterpret_cast<DerivativeFunc>(dlsym(libraryHandle2, "Derivative"));
    ASSERT_TRUE(Derivative2 != nullptr);
    SquareFunc Square2 = reinterpret_cast<SquareFunc>(dlsym(libraryHandle2, "Square"));
    ASSERT_TRUE(Square2 != nullptr);

    float result1 = Derivative1(0.0, 0.1);
    float result2 = Derivative2(0.0, 0.1);
    ASSERT_NE(result1, result2);

    dlclose(libraryHandle1);
    dlclose(libraryHandle2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
