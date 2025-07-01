#include "functions.h"

int main() {
    bankAccount test;
    test.initializeFile();
    test.addFunds();
    test.deductFunds();
    test.deductFunds();
    test.printBalance();

    return 0;
}