//
// Created by wiktor on 17.06.2025.
//

#include "RandomNumbersGenerator.h"
#include <random>


std::random_device rd;
std::mt19937_64 engine(rd());

__int128 generateRandomBits(int bits) {
    unsigned long long minVal;
    unsigned long long maxVal;
    if (bits == 1) {
        minVal = 1ULL;
        maxVal = 1ULL;
    } else {
        minVal = 1ULL << (bits - 1);
        if (bits == 64) {
            maxVal = std::numeric_limits<unsigned long long>::max();
        } else {
            maxVal = (1ULL << bits) - 1;
        }
    }

    std::uniform_int_distribution<unsigned long long> dist(minVal, maxVal);

    return static_cast<__int128>(dist(engine));
}

std::tuple<__int128, __int128, __int128> generateRandomNumbers(int bits) {
    __int128 n = generateRandomBits(bits);
    while (n%2==0 || n==0) {
        n = generateRandomBits(bits);
    }
    __int128 a = generateRandomBits(bits);
    while (a>n) {
        a = generateRandomBits(bits);
    }
    __int128 e = generateRandomBits(bits);
    return std::make_tuple(a, e, n);
}
