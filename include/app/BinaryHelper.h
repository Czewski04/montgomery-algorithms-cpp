//
// Created by wiktor on 07.05.2025.
//

#ifndef BINARYHELPER_H
#define BINARYHELPER_H

#include <vector>

    // Dodawanie z przeniesieniem
    std::pair<int, int> addc(int a, int b, int c);
    // Propagowanie przeniesienia
    std::vector<int> propagateCarry(std::vector<int> bits, int start, int carry);
    // Propagowanie przeniesienia
    std::vector<int> propagateCarryInverted(std::vector<int> bits, int start, int carry);
    // Odejmowanie z pożyczką
    std::pair<int, int> subc(int x, int y, int borrow);
    // Konwersja liczby binarnej do dziesiętnej
    std::vector<int> intToBin(__int128 n);
    // Uzupełnianie liczby binarnej do określonej długości
    std::vector<int> fillBinary(std::vector<int> n, int s);

#endif //BINARYHELPER_H
