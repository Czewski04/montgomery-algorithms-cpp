//
// Created by wiktor on 08.05.2025.
//

#include <cmath>
#include "BinaryHelper.h"
#include "PrepareMon.h"
#include "FipsMethod.h"

std::vector<int> Fips(std::vector<int> ap_bin, std::vector<int> bp_bin, std::vector<int> n_bin, std::vector<int> np, int s, int w) {
    std::vector<int> t(3, 0);
    std::vector<int> m(2 * s + 1, 0);
    std::vector<int> u = m;

    for (int i =0; i < s; i++) {
        int carry, sum;
        for (int j=0; j<i; j++) {
            std::tie(carry, sum) = addc(t[0], ap_bin[j]*bp_bin[i-j], 0);
            t = propagate_carry(t, 1, carry);
            std::tie(carry, sum) = addc(sum, m[j]*n_bin[i-j], 0);
            t[0] = sum;
            t = propagate_carry(t, 1, carry);
        }
        std::tie(carry, sum) = addc(t[0], ap_bin[i]*bp_bin[0], 0);
        t = propagate_carry(t, 1, carry);
        m[i] = sum*np[0] % (int)std::pow(2,w);
        std::tie(carry, sum) = addc(sum, m[i]*n_bin[0], 0);
        t = propagate_carry(t, 1, carry);
        t[0] = t[1];
        t[1] = t[2];
        t[2] = 0;
    }
    for (int i=s; i<2*s; i++) {
        int carry, sum;
        for (int j=i-s+1; j<s; j++) {
            std::tie(carry, sum) = addc(t[0], ap_bin[j]*bp_bin[i-j], 0);
            t = propagate_carry(t, 1, carry);
            std::tie(carry, sum) = addc(sum, m[j]*n_bin[i-j], 0);
            t[0] = sum;
            t = propagate_carry(t, 1, carry);
        }
        m[i-s] = t[0];
        t[0] = t[1];
        t[1] = t[2];
        t[2] = 0;
    }

    int borrow = 0, diff;
    for (int i=0; i<s; i++) {
        std::tie(borrow, diff) = subc(m[i], n_bin[i], borrow);
        u[i] = diff;
    }

    // std::tie(borrow, diff) = subc(m[s], 0, borrow);
    // u[s] = diff;

    if (borrow==0) {
        return u;
    }
    return m;
}

std::vector<int> FipsExp(int a, int e, int n, int w) {
    auto [k, r, np] = prepareMontgomery(n);
    int s = k/w;
    std::vector<int> npBin = intToBin(np);
    int ap = (a*r)%n;
    std::vector<int> apBin = intToBin(ap);
    apBin = fillBinary(apBin, s);
    int up = (1*r)%n;
    std::vector<int> upBin = intToBin(up);
    upBin = fillBinary(upBin, s);
    std::vector<int> nBin = intToBin(n);

    for (int i=k-1; i>=0; i--) {
        upBin = Fips(upBin, upBin, nBin, npBin, s, w);
        if ((e>>i)&1) {
            upBin = Fips(upBin, apBin, nBin, npBin, s, w);
        }
    }

    std::vector<int> t1(s, 0);
    t1[0] = 1;
    std::vector<int> ret = Fips(upBin, t1, nBin, npBin, s, w);
    return ret;
}

