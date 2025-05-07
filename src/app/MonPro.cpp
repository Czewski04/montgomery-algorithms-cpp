//
// Created by wiktor on 24.04.2025.
//

#include "../../include/app/MonPro.h"

#include <iostream>
#include <ostream>

// Funkcja wykonująca mnożenie Montgomery'ego
int monPro(int ap, int bp, int n, int r, int np) {
    long long t = static_cast<long long>(ap) * bp;  // używamy long long dla bezpieczeństwa
    //std::cout << "t = " << t << " = " << ap << " * " << bp << std::endl;
    long long m = (t * np) % r;
    if (m < 0) m += r;
    //std::cout << "m = " << m << " = " << t << " * " << np << " % " << r << std::endl;;
    long long u = (t + m * n) / r;
    //std::cout << "u = " << u << " = " << t << " + " << m << " * " << n << " // " << r << std::endl;

    if (u >= n) {
        return static_cast<int>(u - n);
    }

    return static_cast<int>(u);
}
