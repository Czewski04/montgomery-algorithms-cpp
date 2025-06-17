//
// Created by wiktor on 24.04.2025.
//

#ifndef PREPARE_H
#define PREPARE_H

#include <tuple>

// Funkcje do przygotowania parametrów dla algorytmu Montgomery'ego
std::tuple<int, __int128, __int128> prepareMontgomery(__int128 n);
// Rozszerzony algorytm Euklidesa
__int128 gcdExtended(__int128 a, __int128 b);
// Obliczenie odwrotności modularnej
__int128 modInverse(__int128 r, __int128 n);

#endif
