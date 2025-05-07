//
// Created by wiktor on 07.05.2025.
//

#ifndef BINARYHELPER_H
#define BINARYHELPER_H

#include <vector>

    // Dodawanie z przeniesieniem
    std::pair<int, int> addc(int a, int b, int c = 0);

    // Propagowanie przeniesienia
    std::vector<int> propagate_carry(std::vector<int> bits, int start, int carry);

    // Odejmowanie z pożyczką
    std::pair<int, int> subc(int x, int y, int borrow);

    std::vector<int> intToBin(int n);

    std::vector<int> fillBinary(std::vector<int> n, int s);

#endif //BINARYHELPER_H
