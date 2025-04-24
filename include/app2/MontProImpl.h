//
// Created by wiktor on 10.04.2025.
//

#ifndef MONTPROIMPL_H
#define MONTPROIMPL_H



class MontProImpl {
public:
    typedef unsigned long long uint64;
    typedef long long int64;
    void runM();
    void xbinGCD(uint64 a, uint64 b, uint64 *pu, uint64 *pv);
    uint64 modul64(uint64 x, uint64 y, uint64 z);
    void mulul64(uint64 u, uint64 v, uint64 *whi, uint64 *wlo);
    uint64 montmul(uint64 abar, uint64 bbar, uint64 m, uint64 mprime);
};



#endif //MONTPROIMPL_H
