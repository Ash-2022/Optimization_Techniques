#ifndef LPP_H
#define LPP_H

#include <vector>
#include <iostream>
#include <string>
#include <limits>

// Takes in a LPP of the Form
// Max Z = c.T * X
// Subject to
// Constraints : A * X <= b
// X >= 0

enum class Operator{
    LT = 0,
    LE,
    GT,
    GE,
    EQ 
};

class LPP{
    private:
        size_t numVariables;
        size_t numConstraints;
        std::vector<double> objFunctionCoeffVector;
        std::vector<double> decisionVariableVector;
        std::vector<std::vector<double>> constraintsCoeffMatrix;
        // std::vector<std::vector<double>> bodyMatrix;
        std::vector<double> bVector;
        // std::vector<double> slackOrSurplusVector;
        std::string optimizationType;

    public:
        LPP(size_t numVariables, size_t numConstraint) : 
            numVariables(numVariables), 
            numConstraints(numConstraint),
            objFunctionCoeffVector(numVariables, 0.0),
            decisionVariableVector(numVariables, 0.0),
            constraintsCoeffMatrix(numConstraints, std::vector<double>(numVariables, 0.0)),
            bVector(numConstraints, 0.0),
            optimizationType("")
        {
            // Set Optimization Type
            this->setOptimizationType();
            // Compiling all info into Z
            this->setObjectiveFunction();
            // Setting Constraints
            this->setConstraints();
        }
        void setOptimizationType(){
            using namespace std;
            cout << "Enter Type of Optimization (Enter min for minimization and max for maximization): ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(cin, this->optimizationType);
        }
        void setObjectiveFunction(){
            using namespace std;
            cout << "Enter the Coefficient of Variable in J : " << endl;
            for(size_t varIdx = 0; varIdx < this->numVariables; varIdx++){
                cout << "Enter Coeff of x" << varIdx+1 << " (Enter 0 if not present) : ";
                double coeff;
                cin >> coeff;
                this->objFunctionCoeffVector[varIdx] = coeff;
            }
        }
        void setEachConstraintCoeff(size_t constraintIdx){
            using namespace std;
            cout << "Enter the Coefficient of Variable in Constraints " << constraintIdx << " :" << endl;
            for(size_t varIdx = 0; varIdx < this->numVariables; varIdx++){
                cout << "Enter Coeff of x" << varIdx+1 << " (Enter 0 if not present) : ";
                double coeff;
                cin >> coeff;
                this->constraintsCoeffMatrix[constraintIdx][varIdx] = coeff;
            }
        }
        void setEachConstraintBias(size_t constraintIdx){
            using namespace std;
            cout << "Enter the Bias of Constraint " << constraintIdx << " : ";
            double bias;
            cin >> bias;
            this->bVector[constraintIdx] = bias;
        }
        void setEachConstraint(size_t constraintIdx){
            this->setEachConstraintCoeff(constraintIdx);
            this->setEachConstraintBias(constraintIdx);
        }
        void setConstraints(){
            using namespace std;
            for(size_t constraintIdx = 0; constraintIdx < this->numConstraints; constraintIdx++){
                this->setEachConstraint(constraintIdx);
            }
        }
        void getObjectiveFunction(){
            using namespace std;
            cout << "Objective Function : " << this->optimizationType << " Z = ";
            for(size_t varIdx = 0; varIdx < this->numVariables - 1; varIdx++){
                cout << this->objFunctionCoeffVector[varIdx] << "x" << varIdx+1 << " + ";
            }
            cout << this->objFunctionCoeffVector[numVariables - 1] << "x" << numVariables << endl;
        }
        void getConstraints(){
            using namespace std;
            for(size_t constraintIdx = 0; constraintIdx < this->numConstraints; constraintIdx++){
                cout << "Constraints " << constraintIdx << " : ";
                for(size_t varIdx = 0; varIdx < this->numVariables - 1; varIdx++){
                    cout << this->constraintsCoeffMatrix[constraintIdx][varIdx] << "x" << varIdx+1 << " + ";
                }
                cout << this->constraintsCoeffMatrix[constraintIdx][numVariables - 1] << "x" << numVariables << " <= " << this->bVector[constraintIdx] << endl;
            }
        }
        void getLPP(){
            using namespace std;
            cout << "LPP : " << endl;
            this->getObjectiveFunction();
            this->getConstraints();
            cout << "Non-Negativity Constriant : ";
            for(size_t varIdx = 0; varIdx < this->numVariables - 1; varIdx++){
                cout << "x" << varIdx+1 << ", ";
            }
            cout << "x" << numVariables << " >= 0" << endl;
        }
};

// slack/Surplus vector
std::vector<double> sVector;

#endif
