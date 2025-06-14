//
// Created by wiktor on 24.04.2025.
//

#include "../../include/app/PrepareMon.h"

#include <cmath>
#include <iostream>
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
        return 0; // odwrotność nie istnieje
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
    __int128 r_inv = modInverse(r, n);
    __int128 np_tmp = 1 - r * r_inv;
    __int128 np;
    if (np_tmp >= 0)
        np = -(np_tmp / n);  // zaokrąglenie w dół
    else
        np = -((np_tmp - n + 1) / n);

    //std::cout << k << " " << r << " " << r_inv << " " << np << std::endl;
    return std::make_tuple(k, r, np);
}