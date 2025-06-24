#ifndef RANDOMNUMBERSGENERATOR_H
#define RANDOMNUMBERSGENERATOR_H

#include <tuple>

// Generowanie losowych liczb o określonej liczbie bitów
__int128 generateRandomBits(int bits);
// Generowanie trzech losowych liczb: a, e, n
std::tuple<__int128, __int128, __int128> generateRandomNumbers(int bits);

#endif //RANDOMNUMBERSGENERATOR_H
