#include "BinaryHelper.h"
#include "PrepareMon.h"
#include "CihsMethod.h"
#include <algorithm>
#include <chrono>
#include <cmath>

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

    for (int i=0; i<s; i++) {
        int m = t[0]*np[0] % (int)std::pow(2,w);
        int carry = 0, sum = 0;
        std::tie(carry, sum) = addc(t[0], m*n_bin[0], 0);
        for (int j=1; j<s; j++) {
            std::tie(carry, sum) = addc(t[j], m*n_bin[j], carry);
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

    int borrow = 0, diff;
    for (int i=0; i<s; i++) {
        std::tie(borrow, diff) = subc(t[i], n_bin[i], borrow);
        u[i] = diff;
    }

    std::tie(borrow, diff) = subc(t[s], 0, borrow);
    u[s] = diff;

    if (borrow==0) {
        return u;
    }
    return t;
}

std::tuple<std::vector<int>, double> CihsExp(__int128 a, __int128 e, __int128 n, int w=1) {
    auto [k, r, np] = prepareMontgomery(n);
    int s = k/w;

    std::vector<int> npBin = intToBin(np);

    __int128 ap = (a*r)%n;
    std::vector<int> apBin = intToBin(ap);
    apBin = fillBinary(apBin, s);

    __int128 up = (1*r)%n;
    std::vector<int> upBin = intToBin(up);
    upBin = fillBinary(upBin, s);

    std::vector<int> nBin = intToBin(n);

    auto start = std::chrono::system_clock::now();
    for (int i=k-1; i>=0; i--) {
        upBin = Cihs(upBin, upBin, nBin, npBin, s, w);
        if ((e>>i)&1) {
            upBin = Cihs(upBin, apBin, nBin, npBin, s, w);
        }
    }
    std::vector<int> t1(s, 0);
    t1[0] = 1;
    std::vector<int> ret = Cihs(upBin, t1, nBin, npBin, s, w);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);
    std::reverse(ret.begin(), ret.end());
    return std::make_tuple(ret, duration.count());
}