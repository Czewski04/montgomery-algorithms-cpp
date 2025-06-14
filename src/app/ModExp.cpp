//
// Created by wiktor on 24.04.2025.
//

#include "../../include/app/ModExp.h"
#include <iostream>
#include <tuple>

#include "Int128ToStr.h"
#include "MonPro.h"
#include "PrepareMon.h"

// Funkcja obliczająca a^e mod n za pomocą Montgomery'ego
__int128 modExp(__int128 a, __int128 e, __int128 n) {
    auto [k, r, np] = prepareMontgomery(n);
    std::cout<<"k: "<<int128ToString(k)<<", r: "<<int128ToString(r)<<", np: "<<int128ToString(np)<<"\n";

    __int128 ap = (a * r) % n;
    __int128 up = (1 * r) % n;

    std::cout<<"ap: "<<int128ToString(ap)<<", up: "<<int128ToString(up)<<"\n";


    // Pętla potęgowania
    for (int i = k - 1; i >= 0; --i) {
        up = monPro(up, up, n, r, np);
        if ((e >> i) & 1) {
            up = monPro(up, ap, n, r, np);
        }
    }

    __int128 u = monPro(up, 1, n, r, np);
    return u;
}
