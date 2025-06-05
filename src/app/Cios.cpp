//
// Created by wiktor on 04.06.2025.
//

#include "Cios.h"

#include <algorithm>

#include "PrepareMon.h"
#include "BinaryHelper.h"
#include <cmath>

std::vector<int> Cios(std::vector<int> ap_bin, std::vector<int> bp_bin, std::vector<int> n_bin, std::vector<int> np, int s, int w) {
    std::vector<int> t(2 * s + 1, 0);
    std::vector<int> u = t;
    int tSize = t.size()-1;
    int apSize = ap_bin.size()-1;
    int bpSize = bp_bin.size()-1;
    int nSize = n_bin.size()-1;
    int npSize = np.size()-1;
    for (int i=0; i<s; i++) {
        int carry = 0, sum;
        for (int j=0; j<s; j++) {
            std::tie(carry, sum) = addc(t[tSize - j], ap_bin[apSize - j]*bp_bin[bpSize - i], carry);
            t[tSize - j] = sum;
        }
        std::tie(carry, sum) = addc(t[tSize - s], carry, 0);
        t[tSize - s] = sum;
        t[tSize - (s+1)] = carry;
        carry = 0;
        int m = t[tSize]*np[npSize] % (int) std::pow(2,w);
        for (int j=0; j<s; j++) {
            std::tie(carry, sum) = addc(t[tSize - j], m*n_bin[nSize - j], carry);
            t[tSize - j] = sum;
        }
        std::tie(carry, sum) = addc(t[tSize - s], carry, 0);
        t[tSize - s] = sum;
        t[tSize - (s+1)] += carry;

        for (int j=0; j<=s; j++) {
            t[tSize - j] = t[tSize - (j+1)];
            u[tSize - j] = t[tSize - (j+1)];
        }
    }

    int borrow = 0, diff;
    for (int i=0; i<s; i++) {
        std::tie(borrow, diff) = subc(u[tSize - i], n_bin[nSize - i], borrow);
        t[tSize - i] = diff;
    }

    std::tie(borrow, diff) = subc(u[tSize - s], 0, borrow);
    t[tSize - s] = diff;

    if (borrow==0) {
        return t;
    }
    return u;
}

std::vector<int> CiosExp(int a, int e, int n, int w) {
    auto [k, r, np] = prepareMontgomery(n);
    int s = k/w;

    std::vector<int> npBin = intToBin(np);
    std::reverse(npBin.begin(), npBin.end());

    int ap = (a*r)%n;
    std::vector<int> apBin = intToBin(ap);
    apBin = fillBinary(apBin, s);
    std::reverse(apBin.begin(), apBin.end());

    int up = (1*r)%n;
    std::vector<int> upBin = intToBin(up);
    upBin = fillBinary(upBin, s);
    std::reverse(upBin.begin(), upBin.end());

    std::vector<int> nBin = intToBin(n);
    std::reverse(nBin.begin(), nBin.end());

    for (int i=k-1; i>=0; i--) {
        upBin = Cios(upBin, upBin, nBin, npBin, s, w);
        if ((e>>i)&1) {
            upBin = Cios(upBin, apBin, nBin, npBin, s, w);
        }
    }

    std::vector<int> t1(s, 0);
    t1.back() = 1;
    std::vector<int> ret = Cios(upBin, t1, nBin, npBin, s, w);
    return ret;
}
