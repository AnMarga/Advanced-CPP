#include "multiplication.h"

#include <stdexcept>

int64_t Multiply(int a, int b) {
    // throw std::runtime_error("Not implemented");
    if (a >= 0 and b >= 0) {
        return static_cast<uint64_t>(a) * static_cast<uint64_t>(b);
    } else if (a < 0 and b < 0) {
        return static_cast<uint64_t>(-a) * static_cast<uint64_t>(-b);
    } else {
        return static_cast<int64_t>(a) * b;
    }
}
