//
// Created by wiktor on 08.05.2025.
//

#ifndef FIPSMETHOD_H
#define FIPSMETHOD_H
#include <vector>

std::vector<int> Fips(int ap_bin,int bp_bin,int n_bin,int np,int s,int w=1);
std::vector<int> FipsExp(int a, int e, int n, int w);

#endif //FIPSMETHOD_H
