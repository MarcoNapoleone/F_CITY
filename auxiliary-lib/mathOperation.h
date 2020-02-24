#include <cmath>

float setFloatPrecision(float input, int precision) {

    if (input < 100000) {
        int intPart = static_cast<int>(input);
        float decimalPart = input - intPart;
        decimalPart *= pow(10, precision);
        int newDecimalPart = static_cast<int>(decimalPart);
        return (newDecimalPart / pow(10, precision) + intPart);
    } else return input;

}