#include "StandardLPP.h"

int main(){
    std::cout << "Enter num of Decision Variables : ";
    size_t numVariables{0};
    std::cin >> numVariables;
    std::cout << "Enter num of Constraints : ";
    size_t numConstraints{0};
    std::cin >> numConstraints;
    StandardLPP lppFormulation(numVariables, numConstraints);
    lppFormulation.displayStandardLPP();
    return 0;
}
