#ifndef LPP_H
#define LPP_H

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>


// Takes in a LPP of the Form
// Max Z = c.T * X
// Subject to
// Constraints : D * X <= b
// X >= 0

class LPP {
   protected:
    size_t numVariables;
    size_t numConstraints;
    std::vector<double> objFunctionCoeffVector;
    std::vector<double> decisionVariableVector;
    std::vector<std::vector<double>> constraintsCoeffMatrix;
    std::vector<double> bVector;
    std::vector<std::string> constraintOperators;
    std::string optimizationType;

   public:
    LPP(size_t numVariables, size_t numConstraint)
        : numVariables(numVariables),
          numConstraints(numConstraint),
          objFunctionCoeffVector(numVariables, 0.0),
          decisionVariableVector(numVariables, 0.0),
          constraintsCoeffMatrix(numConstraints,
                                 std::vector<double>(numVariables, 0.0)),
          bVector(numConstraints, 0.0),
          constraintOperators(numConstraints, "<="),
          optimizationType("") {
        // Set Optimization Type
        this->setOptimizationType();
        // Compiling all info into Z
        this->setObjectiveFunction();
        // Setting Constraints
        this->setConstraints();
    }
    void setOptimizationType() {
        using namespace std;
        cout << "Enter Type of Optimization (Enter min for minimization and "
                "max for maximization): ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, this->optimizationType);
    }
    void setObjectiveFunction() {
        using namespace std;
        cout << "Enter the Coefficient of Variable in J : " << endl;
        for (size_t varIdx = 0; varIdx < this->numVariables; varIdx++) {
            cout << "Enter Coeff of x" << varIdx + 1
                 << " (Enter 0 if not present) : ";
            double coeff;
            cin >> coeff;
            this->objFunctionCoeffVector[varIdx] = coeff;
        }
    }
    void setEachConstraintCoeff(size_t constraintIdx) {
        using namespace std;
        cout << "Enter the Coefficient of Variable in Constraints "
             << constraintIdx << " :" << endl;
        for (size_t varIdx = 0; varIdx < this->numVariables; varIdx++) {
            cout << "Enter Coeff of x" << varIdx + 1
                 << " (Enter 0 if not present) : ";
            double coeff;
            cin >> coeff;
            this->constraintsCoeffMatrix[constraintIdx][varIdx] = coeff;
        }
    }
    void setEachConstraintOperator(size_t constraintIdx) {
        using namespace std;
        cout << "Enter the Operator of Constraint " << constraintIdx << " : ";
        string op;
        cin >> op;
        this->constraintOperators[constraintIdx] = op;
    }
    void setEachConstraintBias(size_t constraintIdx) {
        using namespace std;
        cout << "Enter the Bias of Constraint " << constraintIdx << " : ";
        double bias;
        cin >> bias;
        this->bVector[constraintIdx] = bias;
    }
    void setEachConstraint(size_t constraintIdx) {
        this->setEachConstraintCoeff(constraintIdx);
        this->setEachConstraintOperator(constraintIdx);
        this->setEachConstraintBias(constraintIdx);
    }
    void setConstraints() {
        using namespace std;
        for (size_t constraintIdx = 0; constraintIdx < this->numConstraints;
             constraintIdx++) {
            this->setEachConstraint(constraintIdx);
        }
    }
    virtual void displayObjectiveFunction() {
        using namespace std;
        cout << fixed << setprecision(4);
        cout << "Objective Function : " << this->optimizationType << " Z = ";
        for (size_t varIdx = 0; varIdx < this->numVariables - 1; varIdx++) {
            cout << this->objFunctionCoeffVector[varIdx] << "x" << varIdx + 1
                 << " + ";
        }
        cout << this->objFunctionCoeffVector[numVariables - 1] << "x"
             << numVariables << endl;
    }
    virtual void displayConstraints() {
        using namespace std;
        cout << fixed << setprecision(4);
        for (size_t constraintIdx = 0; constraintIdx < this->numConstraints;
             constraintIdx++) {
            cout << "Constraints " << constraintIdx << " : ";
            for (size_t varIdx = 0; varIdx < this->numVariables - 1; varIdx++) {
                cout << this->constraintsCoeffMatrix[constraintIdx][varIdx]
                     << "x" << varIdx + 1 << " + ";
            }
            cout
                << this->constraintsCoeffMatrix[constraintIdx][numVariables - 1]
                << "x" << numVariables << " "
                << this->constraintOperators[constraintIdx] << " "
                << this->bVector[constraintIdx] << endl;
        }
    }
    virtual void displayOriginalLPP() {
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
        cout << " >= 0" << endl;
    }

    virtual ~LPP() = default;
};

#endif
