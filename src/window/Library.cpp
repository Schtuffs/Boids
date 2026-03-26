#include "window/Library.h"

double Library::map(double value, double currentMin, double currentMax, double newMin, double newMax) {
    value -= currentMin;

    double currentRange = currentMax - currentMin;
    if (currentRange != 0)
        value /= currentRange;

    double newRange = newMax - newMin;
    value *= newRange;

    value += newMin;

    return value;
}

double Library::clamp(double value, double min, double max) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

