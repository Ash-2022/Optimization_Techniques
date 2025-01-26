#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>
#include <algorithm>
#include <iostream>

// Takes in a LPP of the Form
// Max Z = c.T * X
// Subject to
// Constraints : A * X <= b
// X >= 0  

bool maxType;

// C matrix
std::vector<std::vector<double>> coeffMatrix;

// b vector
std::vector<double> bVector;

// slack/Surplus vector
std::vector<double> sVector;

// Body Matrix 
std::vector<std::vector<double>> bodyMatrix;

// Cb Vector
std::vector<double> cbVector;




#endif
