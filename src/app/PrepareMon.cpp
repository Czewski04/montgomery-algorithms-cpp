#include "PrepareMon.h"
#include <cmath>
#include <tuple>

// Zmienne globalne
__int128 x, y;

// Rozszerzony algorytm Euklidesa
__int128 gcdExtended(__int128 a, __int128 b) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    __int128 gcd = gcdExtended(b % a, a);
    __int128 x1 = x;
    __int128 y1 = y;

    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}

// Obliczenie odwrotności modularnej
__int128 modInverse(__int128 r, __int128 n) {
    __int128 g = gcdExtended(r, n);
    if (g != 1) {
        return 0;
    } else {
        __int128 res = (x % n + n) % n;
        return res;
    }
}

// Przygotowanie algorytmu Montgomery'ego
std::tuple<int, __int128, __int128> prepareMontgomery(__int128 n) {
    __int128 k = 0;
    __int128 tmp = n;
    while (tmp > 0) {
        k++;
        tmp >>= 1;
    }

    __int128 r = (__int128)1 << k;
    __int128 rInv = modInverse(r, n);
    __int128 npTmp = 1 - r * rInv;
    __int128 np = -(npTmp / n);
    return std::make_tuple(k, r, np);
}