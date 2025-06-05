
#include <iostream>
#include <vector>

#include "CihsMethod.h"
#include "Cios.h"
#include "ModExp.h"
#include "FipsMethod.h"

int main() {
    int a = 13, e = 21, n = 19;
    //int a = 7, e = 10, n = 13;

    int result = modExp(a, e, n);
    std::cout << "Wynik MonPro: "<<result <<"\n";

    std::vector<int> resultCihs;
    double cihsTime;
    std::tie(resultCihs, cihsTime) = CihsExp(a,e,n,1);
    std::cout << "Wynik cichs: " <<"\n";
    for (int i : resultCihs) {
        std::cout << i;
    }
    std::cout << "\n";
    std::cout << "Czas: " << cihsTime << "\n";

    std::vector<int> resultFips;
    double fipsTime;
    std::tie(resultFips, fipsTime) = FipsExp(a,e,n,1);
    std::cout << "Wynik fips: " <<"\n";
    for (int i : resultFips) {
        std::cout << i;
    }
    std::cout << "\n";
    std::cout << "Czas: " << fipsTime << "\n";

    std::vector<int> resultCios = CiosExp(a,e,n,1);
    std::cout << "Wynik cios: " <<"\n";
    for (int i : resultCios) {
        std::cout << i;
    }
    return 0;
}
