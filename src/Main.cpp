#include "BasicMontgomery.h"
#include "CihsMethod.h"
#include "FipsMethod.h"
#include "Int128Conversions.h"
#include "RandomNumbersGenerator.h"
#include <iostream>

void testing();
void runMon();

int main() {
    int choice;
    while (true) {
        std::cout<< "\nMenu:\n";
        std::cout<< "1. Algorytmy Montgomery'ego\n";
        std::cout<< "2. Testowanie\n";
        std::cout<< "3. Wyjscie\n";
        std::cin >> choice;
        if (choice == 1) {
            runMon();
        } else if (choice == 2) {
            testing();
        }
        else if (choice == 3) {
            return 0;
        }
    }
}

void runMon() {
    __int128 a,e,n;
    std::string aStr;
    std::string eStr;
    std::string nStr;

    std::cout << "Podaj liczbe a: ";
    std::cin >> aStr;
    std::cout << "Podaj liczbe e: ";
    std::cin >> eStr;
    std::cout << "Podaj liczbe n: ";
    std::cin >> nStr;
    a = stringToInt128(aStr);
    e = stringToInt128(eStr);
    n = stringToInt128(nStr);

    __int128 result = modExp(a, e, n);
    std::cout << "Wynik MonPro: \n"<<int128ToString(result) <<"\n";

    auto [resultCihs, cihsTime] = CihsExp(a,e,n,1);
    std::cout << "Wynik CIHS: " <<"\n";
    for (int j : resultCihs) {
        std::cout << j;
    }
    std::cout << "\n";
    std::cout << "Czas: " << cihsTime << "\n";

    auto [resultFips, fipsTime] = FipsExp(a,e,n,1);
    std::cout << "Wynik FIPS: " <<"\n";
    for (int j : resultFips) {
        std::cout << j;
    }
    std::cout << "\n";
    std::cout << "Czas: " << fipsTime << "\n";
}

void testing() {
    double sumOfCihsTime = 0;
    double sumOfFipsTime = 0;


    int numberOfTests, numberOfBits;
    std::cout << "Podaj liczbe testow: ";
    std::cin >> numberOfTests;
    std::cout << "Podaj liczbe bitow: ";
    std::cin >> numberOfBits;

    for (int i=0; i<numberOfTests; i++) {
        auto[a,e,n] = generateRandomNumbers(numberOfBits);

        auto [resultCihs, cihsTime] = CihsExp(a,e,n,1);
        sumOfCihsTime += cihsTime;
        auto [resultFips, fipsTime] = FipsExp(a,e,n,1);
        sumOfFipsTime += fipsTime;

    }
    std::cout << "Liczba bitow: " << numberOfBits << "\n";
    std::cout << "Sredni czas Cihs: " << sumOfCihsTime / 50 << " ms\n";
    std::cout << "Sredni czas Fips: " << sumOfFipsTime / 50 << " ms\n";
}