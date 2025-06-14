//
// Created by wiktor on 07.05.2025.
//

#ifndef CIHSMETHOD_H
#define CIHSMETHOD_H
#include <vector>

std::vector<int> Cihs(int ap_bin,int bp_bin,int n_bin,int np,int s,int w=1);
std::tuple<std::vector<int>, double> CihsExp(__int128 a, __int128 e, __int128 n, int w);


#endif //CIHSMETHOD_H
