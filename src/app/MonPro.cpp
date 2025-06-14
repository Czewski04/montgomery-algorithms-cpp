//
// Created by wiktor on 24.04.2025.
//

#include "../../include/app/MonPro.h"

#include <iostream>
#include <ostream>

// Funkcja wykonująca mnożenie Montgomery'ego
__int128 monPro(__int128 ap, __int128 bp, __int128 n, __int128 r, __int128 np) {
    __int128 t = (ap) * bp;  // używamy __int128 dla bezpieczeństwa
    //std::cout << "t = " << t << " = " << ap << " * " << bp << std::endl;
    __int128 m = (t * np) % r;
    if (m < 0) m += r;
    //std::cout << "m = " << m << " = " << t << " * " << np << " % " << r << std::endl;;
    __int128 u = (t + m * n) / r;
    //std::cout << "u = " << u << " = " << t << " + " << m << " * " << n << " // " << r << std::endl;

    if (u >= n) {
        return u - n;
    }

    return u;
}
