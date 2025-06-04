//
// Created by wiktor on 24.04.2025.
//

#include "../../include/app/PrepareMon.h"
#include <iostream>
#include <tuple>

// Zmienne globalne
int x, y;

// Rozszerzony algorytm Euklidesa
int gcdExtended(int a, int b) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    int gcd = gcdExtended(b % a, a);
    int x1 = x;
    int y1 = y;

    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}

// Obliczenie odwrotności modularnej
int modInverse(int R, int N) {
    int g = gcdExtended(R, N);
    if (g != 1) {
        return 0; // odwrotność nie istnieje
    } else {
        int res = (x % N + N) % N;
        return res;
    }
}

// Przygotowanie algorytmu Montgomery'ego
std::tuple<int, int, int> prepareMontgomery(int n) {
    int k = 0;
    int tmp = n;
    while (tmp > 0) {
        k++;
        tmp >>= 1;
    }

    int r = 1 << k;
    int r_inv = modInverse(r, n);
    int np_tmp = 1 - r * r_inv;
    int np;
    if (np_tmp >= 0)
        np = -(np_tmp / n);  // zaokrąglenie w dół
    else
        np = -((np_tmp - n + 1) / n);

    //std::cout << k << " " << r << " " << r_inv << " " << np << std::endl;
    return std::make_tuple(k, r, np);
}