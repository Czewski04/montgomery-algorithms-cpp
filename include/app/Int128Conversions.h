#ifndef INT128TOSTR_H
#define INT128TOSTR_H

#include <string>

// Funkcja do konwersji __int128 na string
std::string int128ToString(__int128 val);
// Funkcja do konwersji string na __int128
__int128 stringToInt128(const std::string& s);

#endif //INT128TOSTR_H
