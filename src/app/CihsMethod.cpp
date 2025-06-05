//
// Created by wiktor on 07.05.2025.
//

#include <cmath>
#include "BinaryHelper.h"
#include "PrepareMon.h"
#include "CihsMethod.h"
#include <algorithm>
#include <chrono>

std::vector<int> Cihs(std::vector<int> ap_bin,std::vector<int> bp_bin,std::vector<int> n_bin,std::vector<int> np,int s,int w=1) {
    std::vector<int> t(2 * s + 1, 0);
    std::vector<int> u = t;

    int tSize = t.size()-1;
    int apSize = ap_bin.size()-1;
    int bpSize = bp_bin.size()-1;
    int nSize = n_bin.size()-1;
    int npSize = np.size()-1;

    for (int i=0; i<s; i++) {
        int carry = 0, sum;
        for (int j=0; j<s-i; j++) {
            std::tie(carry, sum) = addc(t[tSize - (i+j)], ap_bin[apSize - j]*bp_bin[bpSize - i], carry);
            t[tSize - (i+j)] = sum;
        }
        std::tie(carry, sum) = addc(t[tSize - s], 0, carry);
        t[tSize - s] = sum;
        t[tSize - (s+1)] = carry;
    }

    for (int i=0; i<s; i++) {
        int m = t[tSize]*np[npSize] % (int)std::pow(2,w);
        int carry = 0, sum = 0;
        std::tie(carry, sum) = addc(t[tSize], m*n_bin[nSize], 0);
        for (int j=1; j<s; j++) {
            std::tie(carry, sum) = addc(t[tSize - j], m*n_bin[nSize - j], carry);
            t[tSize - (j-1)] = sum;
        }
        std::tie(carry, sum) = addc(t[tSize - s], 0, carry);
        t[tSize - (s-1)] = sum;
        t[tSize - s] = t[tSize - (s+1)] + carry;
        t[tSize - (s+1)] = 0;
        for (int j=i+1; j<s; j++) {
            std::tie(carry, sum) = addc(t[tSize - (s-1)], bp_bin[bpSize - j]*ap_bin[apSize-(s-j+i)], 0);
            t[tSize - (s-1)] = sum;
            std::tie(carry, sum) = addc(t[tSize - s], 0, carry);
            t[tSize - s] = sum;
            t[tSize - (s+1)] = carry;
        }
    }

    int borrow = 0, diff;
    for (int i=0; i<s; i++) {
        std::tie(borrow, diff) = subc(t[tSize - i], n_bin[nSize - i], borrow);
        u[tSize - i] = diff;
    }

    std::tie(borrow, diff) = subc(t[tSize - s], 0, borrow);
    u[tSize - s] = diff;

    if (borrow==0) {
        return u;
    }
    return t;
}

std::tuple<std::vector<int>, double> CihsExp(int a, int e, int n, int w=1) {
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

    auto start = std::chrono::system_clock::now();
    for (int i=k-1; i>=0; i--) {
        upBin = Cihs(upBin, upBin, nBin, npBin, s, w);
        if ((e>>i)&1) {
            upBin = Cihs(upBin, apBin, nBin, npBin, s, w);
        }
    }
    std::vector<int> t1(s, 0);
    t1.back() = 1;
    std::vector<int> ret = Cihs(upBin, t1, nBin, npBin, s, w);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(ret, duration.count());
}