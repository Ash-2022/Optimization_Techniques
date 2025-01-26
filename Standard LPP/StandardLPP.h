#include "../LPP/LPP.h"

// Standard LPP is a LPP of the Form
// Max Z = c.T * X + d.T * S 
// Subject to
// Constraints : D * X + E * S = b
// X , S >= 0

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
