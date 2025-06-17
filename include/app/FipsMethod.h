//
// Created by wiktor on 08.05.2025.
//

#ifndef FIPSMETHOD_H
#define FIPSMETHOD_H
#include <chrono>
#include <vector>

std::vector<int> Fips(int ap_bin,int bp_bin,int n_bin,int np,int s,int w=1);
std::tuple<std::vector<int>, double> FipsExp(__int128 a, __int128 e, __int128 n, int w);

#endif //FIPSMETHOD_H
