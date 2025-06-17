#include "Int128Conversions.h"
#include <algorithm>
#include <string>
//
// Created by wiktor on 14.06.2025.
//
std::string int128ToString(__int128 val) {
    if (val == 0) return "0";
    std::string s = "";
    bool negative = false;
    if (val < 0) {
        negative = true;
        val = -val;
    }
    while (val > 0) {
        s += (val % 10) + '0';
        val /= 10;
    }
    if (negative) {
        s += '-';
    }
    std::reverse(s.begin(), s.end());
    return s;
}

__int128 stringToInt128(const std::string& s) {
    __int128 res = 0;
    __int128 ten = 10;
    for (char c : s) {
        res = res * ten + (c - '0');
    }
    return res;
}