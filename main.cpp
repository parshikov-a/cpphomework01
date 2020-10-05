#include <iostream>
#include "lib.h"

int main()
{
    std::cout << "build " << version() << "\nHello, World!" << std::endl;
    return !std::cout.good();
}
