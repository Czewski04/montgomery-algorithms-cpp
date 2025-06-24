#include "BasicMontgomery.h"
#include "PrepareMon.h"

// Funkcja wykonująca mnożenie Montgomery'ego
__int128 monPro(__int128 ap, __int128 bp, __int128 n, __int128 r, __int128 np) {
    __int128 t = (ap) * bp;
    __int128 m = (t * np) % r;
    if (m < 0) m += r;
    __int128 u = (t + m * n) / r;

    if (u >= n) {
        return u - n;
    }

    return u;
}

// Funkcja obliczająca a^e mod n za pomocą Montgomery'ego
__int128 modExp(__int128 a, __int128 e, __int128 n) {
    auto [k, r, np] = prepareMontgomery(n);

    __int128 ap = (a * r) % n;
    __int128 up = (1 * r) % n;

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
