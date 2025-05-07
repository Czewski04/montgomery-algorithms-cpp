//
// Created by wiktor on 07.05.2025.
//

#include "../../include/app/CihsMethod.h"
#include "BinaryHelper.h"
#include "PrepareMon.h"

std::vector<int> Cihs(std::vector<int> ap_bin,std::vector<int> bp_bin,std::vector<int> n_bin,std::vector<int> np,int s,int w=1) {
    std::vector<int> t(2 * s + 1, 0);
    std::vector<int> u = t;
    for (int i=0; i<s-1; i++) {
        int carry, sum = 0;
        for (int j=0; j<s-i-1; j++) {
            std::tie(carry, sum) = addc(t[i+j], ap_bin[j]*bp_bin[i], carry);
            t[i+j] = sum;
        }
        std::tie(carry, sum) = addc(t[s], 0, carry);
        t[s] = sum;
        t[s+1] = carry;
    }
    for (int i=0; i<s-1; i++) {
        int m = t[0]*np[0] % w;
        int carry, sum = 0;
        std::tie(carry, sum) = addc(t[0], m*n_bin[0], 0);
        for (int j=1; j<s-1; j++) {
            std::tie(carry, sum) = addc(t[j], m*n_bin[0], carry);
            t[j-1] = sum;
        }
        std::tie(carry, sum) = addc(t[s], 0, carry);
        t[s-1] = sum;
        t[s] = t[s+1] + carry;
        t[s+1] = 0;
        for (int j=i+1; j<s-1; j++) {
            std::tie(carry, sum) = addc(t[s-1], bp_bin[j]*ap_bin[s-j+i], 0);
            t[s-1] = sum;
            std::tie(carry, sum) = addc(t[s], 0, carry);
            t[s] = sum;
            t[s+1] = carry;
        }
    }
}

int CihsExp(int a, int e, int n, int w=1) {
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
}
