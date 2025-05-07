//
// Created by wiktor on 07.05.2025.
//

#include "../../include/app/CihsMethod.h"

#include <iostream>
#include <ostream>

#include "BinaryHelper.h"
#include "PrepareMon.h"

std::vector<int> Cihs(std::vector<int> ap_bin,std::vector<int> bp_bin,std::vector<int> n_bin,std::vector<int> np,int s,int w=1) {
    std::vector<int> t(2 * s + 1, 0);
    std::vector<int> u = t;
    for (int i=0; i<s; i++) {
        int carry = 0, sum;
        for (int j=0; j<s-i; j++) {
            std::tie(carry, sum) = addc(t[i+j], ap_bin[j]*bp_bin[i], carry);
            t[i+j] = sum;
        }
        std::tie(carry, sum) = addc(t[s], 0, carry);
        t[s] = sum;
        t[s+1] = carry;
    }

    for (int i:t) {
        std::cout << i << std::endl;
    }

    for (int i=0; i<s; i++) {
        int m = t[0]*np[0] % w;
        int carry = 0, sum = 0;
        std::tie(carry, sum) = addc(t[0], m*n_bin[0], 0);
        for (int j=1; j<s; j++) {
            std::tie(carry, sum) = addc(t[j], m*n_bin[0], carry);
            t[j-1] = sum;
        }
        std::tie(carry, sum) = addc(t[s], 0, carry);
        t[s-1] = sum;
        t[s] = t[s+1] + carry;
        t[s+1] = 0;
        for (int j=i+1; j<s; j++) {
            std::tie(carry, sum) = addc(t[s-1], bp_bin[j]*ap_bin[s-j+i], 0);
            t[s-1] = sum;
            std::tie(carry, sum) = addc(t[s], 0, carry);
            t[s] = sum;
            t[s+1] = carry;
        }
    }
    int borrow = 0, diff = 0;
    for (int i=0; i<s; i++) {
        std::tie(borrow, diff) = subc(u[i], n_bin[i], borrow);
        t[i] = diff;
    }
    std::tie(borrow, diff) = subc(u[s], 0, borrow);
    t[s] = diff;
    if (borrow==0) {
        return t;
    }
    else return u;
}

std::vector<int> CihsExp(int a, int e, int n, int w=1) {
    auto [k, r, np] = prepareMontgomery(n);
    int s = k/w;
    std::vector<int> npBin = intToBin(np);
    int ap = (a*r)%n;
    std::vector<int> apBin = intToBin(ap);
    apBin = fillBinary(apBin, s);
    int up = (1*r)%n;
    std::vector<int> upBin = intToBin(up);
    upBin = fillBinary(upBin, s);
    std::vector<int> nBin = intToBin(up);
    for (int i=k-1; i>=0; i--) {
        upBin = Cihs(upBin, upBin, nBin, npBin, s, w);
        if ((e>>i)&1) {
            upBin = Cihs(upBin, apBin, nBin, npBin, s, w);
        }
    }
    std::vector<int> t1(s, 0);
    t1[0] = 1;
    return Cihs(upBin, t1, nBin, npBin, s, w);
}
