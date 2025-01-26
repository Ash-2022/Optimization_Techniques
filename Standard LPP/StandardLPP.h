#include "../LPP/LPP.h"

class StandardLPP : protected LPP {
   private:
    int numSlackOrSurplus;
    void setNumSlackOrSurplus() {
        this->numSlackOrSurplus = 0;
        for (int i = 0; i < this->numConstraints; i++) {
            if (this->constraintOperators[i] != "=") {
                this->numSlackOrSurplus++;
            }
        }
    }

   public:
    StandardLPP(size_t numVariables, size_t numConstraint)
        : LPP(numVariables, numConstraint), numSlackOrSurplus(0) {
        // Set Slacks & Surplus
        this->setNumSlackOrSurplus();
    }
};
