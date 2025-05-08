//
// Created by wiktor on 08.05.2025.
//

#include "../../include/app/FipsMethod.h"

#include <iostream>
#include "BinaryHelper.h"
#include "PrepareMon.h"

std::vector<int> Fips(std::vector<int> ap_bin, std::vector<int> bp_bin, std::vector<int> n_bin, std::vector<int> np, int s, int w) {
    std::vector<int> t(2 * s + 1, 0);
    std::vector<int> u = t;

    for (int i = 0; i < s; i++) {
        int carry = 0, sum;

        for (int j = 0; j < s - i; j++) {
            std::tie(carry, sum) = addc(t[i + j], ap_bin[j] * bp_bin[i], carry);
            t[i + j] = sum;
        }

        std::tie(carry, sum) = addc(t[s], 0, carry);
        t[s] = sum;
        t[s + 1] = carry;

        int m = t[0] * np[0] % w;
        carry = 0;

        for (int j = 0; j < s; j++) {
            std::tie(carry, sum) = addc(t[j], m * n_bin[j], carry);
            t[j] = sum;
        }

        std::tie(carry, sum) = addc(t[s], 0, carry);
        t[s] = sum;
        t[s + 1] += carry;

        for (int j = 0; j < s; j++) {
            u[j] = t[j + 1];
        }
        u[s] = t[s + 1];
    }

    int borrow = 0, diff;
    for (int i = 0; i < s; i++) {
        std::tie(borrow, diff) = subc(u[i], n_bin[i], borrow);
        t[i] = diff;
    }
    std::tie(borrow, diff) = subc(u[s], 0, borrow);
    t[s] = diff;

    if (borrow == 0) {
        return t;
    } else {
        return u;
    }
}

std::vector<int> FipsExp(int a, int e, int n, int w) {
    auto [k, r, np] = prepareMontgomery(n);
    int s = k / w;

    std::vector<int> npBin = intToBin(np);
    std::vector<int> apBin = fillBinary(intToBin((a * r) % n), s);
    std::vector<int> upBin = fillBinary(intToBin((1 * r) % n), s);
    std::vector<int> nBin = fillBinary(intToBin(n), s);

    for (int i = k - 1; i >= 0; i--) {
        upBin = Fips(upBin, upBin, nBin, npBin, s, w);
        if ((e >> i) & 1) {
            upBin = Fips(upBin, apBin, nBin, npBin, s, w);
        }
    }

    std::vector<int> t1(s, 0);
    t1[0] = 1;

    return Fips(upBin, t1, nBin, npBin, s, w);
}