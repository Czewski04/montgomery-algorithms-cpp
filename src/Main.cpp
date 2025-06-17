
#include <iostream>
#include <vector>

#include "BasicMontgomery.h"
#include "CihsMethod.h"
#include "Cios.h"
#include "FipsMethod.h"
#include "Int128Conversions.h"
#include "RandomNumbersGenerator.h"

int main() {
    double sumOfCihsTime = 0;
    double sumOfFipsTime = 0;
    int numberOfTests = 100;
    int numberOfBits = 54;
    for (int i=0; i<numberOfTests; i++) {
        auto[a,e,n] = generateRandomNumbers(numberOfBits);

        // std::cout << "a: " << int128ToString(a) << "\n";
        // std::cout << "e: " << int128ToString(e) << "\n";
        // std::cout << "n: " << int128ToString(n) << "\n";

        // __int128 result = modExp(a, e, n);
        // std::cout << "Wynik MonPro: "<<int128ToString(result) <<"\n";

        auto [resultCihs, cihsTime] = CihsExp(a,e,n,1);
        std::cout << "Wynik cichs: " <<"\n";
        for (int j : resultCihs) {
            std::cout << j;
        }
        std::cout << "\n";
        std::cout << "Czas: " << cihsTime << "\n";
        sumOfCihsTime += cihsTime;

        auto [resultFips, fipsTime] = FipsExp(a,e,n,1);
        std::cout << "Wynik fips: " <<"\n";
        for (int j : resultFips) {
            std::cout << j;
        }
        std::cout << "\n";
        std::cout << "Czas: " << fipsTime << "\n";
        sumOfFipsTime += fipsTime;

        // std::vector<int> resultCios = CiosExp(a,e,n,1);
        // std::cout << "Wynik cios: " <<"\n";
        // for (int j : resultCios) {
        //     std::cout << j;
        // }
    }
    std::cout << "\nLiczba bitow: " << numberOfBits << "\n";
    std::cout << "Sredni czas Cihs: " << sumOfCihsTime / 50 << "\n";
    std::cout << "Sredni czas Fips: " << sumOfFipsTime / 50 << "\n";

    return 0;
}