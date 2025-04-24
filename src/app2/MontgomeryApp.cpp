//
// Created by wiktor on 08.04.2025.
//

#include "../../include/app2/MontgomeryApp.h"

#include <iostream>
#include <ostream>
#include <math.h>

void MontgomeryApp::runApp() {
    int result = 0;
    result = monPro(8,13,19);
    std::cout<<"Ostateczny wynik: "<<result<<"\n";
}

int MontgomeryApp::monPro(int a, int b, int m) {
    int result = 0;
    int aPrim = 0;
    int bPrim = 0;
    int mPrim = 0;
    int t = 0;
    int u = 0;
    int z = 0;
    int k = searchR(m);
        std::cout<<"k: "<<k<<"\n";
    int r = pow(2,k);
        std::cout<<"r: "<<r<<"\n";
    aPrim = (a*r)%m;
        std::cout<<"aPrim: "<<aPrim<<"\n";
    bPrim = (b*r)%m;
        std::cout<<"bPrim: "<<bPrim<<"\n";
    t = aPrim*bPrim;
        std::cout<<"t: "<<t<<"\n";
    mPrim = mInverse(r, m);
        std::cout<<"m': "<<mPrim<<"\n";
    u = (t*mPrim);
    u = u&(r-1);
        std::cout<<"u: "<<u<<"\n";
    z = (t+u*m);
    z = z>>k;
    if (z>=m)   z = z-m;
        std::cout<<"z: "<<z<<"\n";
    result = rInverse(r, m);
        std::cout<<"r^-1: "<<result<<"\n";
    result = z*result%m;
    return result;
}

int MontgomeryApp::nwd(int a, int b)
{
    while(a!=b)
        if(a>b)
            a-=b; //lub a = a - b;
        else
            b-=a; //lub b = b-a
    return a; // lub b - obie zmienne przechowują wynik NWD(a,b)
}

int MontgomeryApp::searchR(int m) {
    int k =1;
    int r=2;
    while(r<m || nwd(r,m)!=1) {
        r=r*2;
        k++;
    }
    return k;
}

int MontgomeryApp::mInverse(int R, int m) {
    int r0 = R, r1 = m;
    int t0 = 0, t1 = 1;

    while (r1 != 0) {
        int q = r0 / r1;
        int temp;

        // wykonujemy r = r0 % r1
        temp = r0 % r1;
        r0 = r1;
        r1 = temp;

        // aktualizacja t
        temp = t0 - q * t1;
        t0 = t1;
        t1 = temp;
    }

    // t0 = m^{-1} mod R
    if (t0 < 0) t0 += R;

    // m' = -m^{-1} mod R
    return (R - t0) % R;
}

int MontgomeryApp::rInverse(int r, int m) {
    int m0 = m;
    int x0 = 0, x1 = 1;

    while (r > 1) {
        int q = r / m;
        int t = m;

        // m to reszta, a := m
        m = r % m;
        r = t;

        // aktualizacja współczynników x
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // x1 może być ujemne
    if (x1 < 0)
        x1 += m0;

    return x1;
}

int MontgomeryApp::pow(int a, int b) {
    int result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}
