//
// Created by wiktor on 07.05.2025.
//

#include "../../include/app/BinaryHelper.h"

#include <algorithm>
#include <vector>
#include <utility>

// Dodawanie z przeniesieniem
std::pair<int, int> addc(int a, int b, int c) {
    int ab = a + b + c;
    if (ab >= 2) {
        c = 1;
        ab = ab % 2;
    } else {
        c = 0;
    }
    return {c, ab};
}

// Propagowanie przeniesienia
std::vector<int> propagateCarry(std::vector<int> bits, int start, int carry) {
    int i = start;
    while (carry > 0 && i < bits.size()) {
        std::tie(carry, bits[i]) = addc(bits[i], carry, 0);
        i++;
    }
    return bits;
}

// Propagowanie przeniesienia
std::vector<int> propagateCarryInverted(std::vector<int> bits, int start, int carry) {
    int i = start;
    int bSize = bits.size();
    while (carry > 0 && i < bits.size()) {
        std::tie(carry, bits[bSize-1 - i]) = addc(bits[bSize-1 - i], carry, 0);
        i++;
    }
    return bits;
}

// Odejmowanie z pożyczką
std::pair<int, int> subc(int x, int y, int borrow) {
    int diff = x - y - borrow;
    if (diff < 0) {
        borrow = 1;
        diff += 2;
    } else {
        borrow = 0;
    }
    return {borrow, diff};
}

std::vector<int> intToBin(int n) {
    std::vector<int> binaryVector;
    if (n == 0) {
        binaryVector.push_back(0);
        return binaryVector;
    }
    while (n > 0) {
        binaryVector.push_back(n % 2);
        n /= 2;
    }
    return binaryVector;
}

std::vector<int> fillBinary(std::vector<int> n, int s) {
    if (n.size() < s) {
        int zerosToAdd = s - n.size();
        n.insert(n.end(), zerosToAdd, 0);
    }
    return n;
}
