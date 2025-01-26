#include "LPP.h"
#include <cassert>

int main(){
    std::cout << "Enter num of Decision Variables : ";
    size_t numVariables{0};
    std::cin >> numVariables;
    std::cout << "Enter num of Constraints : ";
    size_t numConstraints{0};
    std::cin >> numConstraints;
    LPP lppFormulation(numVariables, numConstraints);
    lppFormulation.getLPP();
    return 0;
}
