#include "realizations.hpp"
#include <cmath>

extern "C" float Derivative(float a, float deltaX) {
    return (cos(a + deltaX) - cos(a)) / (2 * deltaX); 
}

extern "C" float Square(float a, float b) {
    return (a * b) / 2;
}
