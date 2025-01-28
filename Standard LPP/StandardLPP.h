#ifndef STANDARD_LPP_H
#define STANDARD_LPP_H
#include "../LPP/LPP.h"

// Standard LPP is a LPP of the Form
// Max Z = c.T * X + d.T * S
// Subject to
// Constraints : D * X + E * S = b
// X , S >= 0

class StandardLPP : protected LPP {
   private:
    size_t numSlackOrSurplus;
    std::vector<std::vector<double>> bodyMatrix;
    void setNumSlackOrSurplus() {
        this->numSlackOrSurplus = 0;
        for (size_t i = 0; i < this->numConstraints; i++) {
            if (this->constraintOperators[i] != "=") {
                this->numSlackOrSurplus++;
            }
        }
    }

    void setBodyMatrix() {
        this->bodyMatrix = std::vector<std::vector<double>>(
            this->numConstraints,
            std::vector<double>(
                this->numVariables + this->numSlackOrSurplus + 1, 0.0));
        for (size_t i = 0; i < this->numConstraints; i++) {
            for (size_t j = 0; j < this->numVariables; j++) {
                bodyMatrix[i][j] = this->constraintsCoeffMatrix[i][j];
            }
            if (this->constraintOperators[i] != "=") {
                for (size_t j = 0; j < this->numSlackOrSurplus; j++) {
                    bodyMatrix[i][this->numVariables + j] =
                        (this->constraintOperators[i] == ">" ||
                         this->constraintOperators[i] == ">=")
                            ? (double)-1.0
                            : (double)1.0;
                }
            }
            bodyMatrix[i][this->numVariables + this->numSlackOrSurplus] =
                this->bVector[i];
        }
    }

    void convertObjectiveFunctionToStandardForm() {
        for (size_t i = 0; i < this->numVariables; i++) {
            if (this->optimizationType == "min") {
                this->objFunctionCoeffVector[i] *= -1.0;
            }
        }
        for(size_t i = 0; i < this->numSlackOrSurplus; i++){
            this->objFunctionCoeffVector.push_back(0.0);
        }
    }

   public:
    StandardLPP(size_t numVariables, size_t numConstraint)
        : LPP(numVariables, numConstraint),
          numSlackOrSurplus(0),
          bodyMatrix(numConstraint, std::vector<double>(numVariables, 0.0)) {
        // Set Slacks & Surplus
        this->setNumSlackOrSurplus();
        // Convert Objective Function to Standard Form
        this->convertObjectiveFunctionToStandardForm();
        // Setting Body Matrix
        this->setBodyMatrix();

    }
    void rowTransformation(size_t rowToTransform, double scale,
                           size_t baseRow) {
        for (size_t i = 0; i < this->numConstraints; i++) {
            bodyMatrix[rowToTransform][i] =
                scale * bodyMatrix[rowToTransform][i] + bodyMatrix[baseRow][i];
        }
    }

    void printBodyMatrix() {
        using namespace std;
        cout << fixed << setprecision(4);
        for (size_t i = 0; i < this->numConstraints; i++) {
            for (size_t j = 0; j < this->numVariables + this->numSlackOrSurplus;
                 j++) {
                cout << this->bodyMatrix[i][j] << "  ";
            }
            cout << endl;
        }
    }

    void displayObjectiveFunction() override {
        using namespace std;
        cout << fixed << setprecision(4);
        cout << "Objective Function : " << this->optimizationType << " Z = ";
        for (size_t varIdx = 0; varIdx < this->numVariables; varIdx++) {
            cout << this->objFunctionCoeffVector[varIdx] << "x" << varIdx + 1
                 << " + ";
        }
        for (size_t varIdx = 0; varIdx < this->numSlackOrSurplus - 1;
             varIdx++) {
            cout << (double)0.0 << "s" << varIdx + 1 << " + ";
        }
        cout << (double)0.0 << "s" << numSlackOrSurplus << endl;
    }

    void displayConstraints() override {
        using namespace std;
        cout << fixed << setprecision(4);
        for (size_t constraintIdx = 0; constraintIdx < this->numConstraints;
             constraintIdx++) {
            cout << "Constraints " << constraintIdx << " : ";
            for (size_t varIdx = 0; varIdx < this->numVariables; varIdx++) {
                cout << this->constraintsCoeffMatrix[constraintIdx][varIdx]
                     << "x" << varIdx + 1 << " + ";
            }
            for (size_t varIdx = 0; varIdx < this->numSlackOrSurplus - 1;
                 varIdx++) {
                cout << this->bodyMatrix[constraintIdx]
                                        [this->numVariables + varIdx]
                     << "s" << varIdx + 1 << " + ";
            }
            cout << this->bodyMatrix[constraintIdx][this->numVariables +
                                                    this->numSlackOrSurplus - 1]
                 << "s" << numVariables << " "
                 << this->constraintOperators[constraintIdx] << " "
                 << this->bVector[constraintIdx] << endl;
        }
    }

    void displayStandardLPP() {
        using namespace std;
        cout << "LPP : " << endl;
        this->displayObjectiveFunction();
        this->displayConstraints();
        cout << "Non-Negativity Constriant : ";
        if (numVariables == 0) {
            cout << "Invalid LPP" << endl;
            return;
        }
        cout << "x1";
        for (size_t varIdx = 1; varIdx < this->numVariables; varIdx++) {
            cout << " ,x" << varIdx + 1;
        }
        if (numSlackOrSurplus) {
            cout << " ,s1";
            for (size_t varIdx = 1; varIdx < this->numSlackOrSurplus;
                 varIdx++) {
                cout << " ,s" << varIdx + 1;
            }
        }
        cout << " >= 0" << endl;
    }
};

#endif
