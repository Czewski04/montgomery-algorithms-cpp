
#include <iostream>
#include <vector>

#include "CihsMethod.h"
#include "MonPro.h"
#include "ModExp.h"
#include "../include/app2/MontProImpl.h"

int main() {
    // MontgomeryApp *mont = new MontgomeryApp();
    // mont->runApp();

    // MontProImpl *mPro = new MontProImpl();
    // mPro->runM();

    int a = 7, e = 10, n = 13;
    int result = modExp(a, e, n);
    std::vector<int> resultCihs = CihsExp(a,e,n,1);
    std::cout << "Wynik: " << result<<"\n";
    for (int i : resultCihs) {
        std::cout << i << std::endl;
    }
    return 0;
}
