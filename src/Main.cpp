
#include <iostream>

#include "MonPro.h"
#include "ModExp.h"
#include "../include/app2/MontProImpl.h"

int main() {
    // MontgomeryApp *mont = new MontgomeryApp();
    // mont->runApp();

    // MontProImpl *mPro = new MontProImpl();
    // mPro->runM();

    int a = 3, e = 12, n = 19;
    int result = modExp(a, e, n);
    std::cout << "Wynik: " << result;
    return 0;
}
