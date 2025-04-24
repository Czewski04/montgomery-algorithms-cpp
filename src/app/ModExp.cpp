//
// Created by wiktor on 24.04.2025.
//

#include "../../include/app/ModExp.h"
#include <iostream>
#include <tuple>
#include "MonPro.h"
#include "PrepareMon.h"

// Funkcja obliczająca a^e mod n za pomocą Montgomery'ego
int modExp(int a, int e, int n) {
    auto [k, r, np] = prepareMontgomery(n);
    int ap = (a * r) % n;
    int up = (1 * r) % n;

    // Pętla potęgowania
    for (int i = k - 1; i >= 0; --i) {
        up = monPro(up, up, n, r, np);

        if ((e >> i) & 1) {
            up = monPro(up, ap, n, r, np);
        }
    }

    int u = monPro(up, 1, n, r, np);
    return u;
}
