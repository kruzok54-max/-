#include <iostream>
#include <unistd.h>

extern "C" {
    int InitializeCheat() {
        std::cout << "Standoff 2 Cheat Module Initialized!" << std::endl;
        return 0;
    }
}
