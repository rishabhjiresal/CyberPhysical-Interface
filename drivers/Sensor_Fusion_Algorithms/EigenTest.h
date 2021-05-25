
#ifndef EigenTest_h
#define EigenTest_h

#include</usr/local/include/eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

//int TestFunction();

    /**
 * Executes 1st step of the Sensor Fusion Algorithm.
 * Produces a 1D array which is the Support Degree Matrix when given
 * a 1D array of sensor readings at one time stamp and the number
 * of sensors being considered.
 */
double* sdm_calculator(double[],int);

/**
 * Executes a part of 2nd step of the Sensor Fusion Algorithm.
 * Produces a 1D array consisting of EigenValues for the given
 * support degree matrix in the form of a 1D array and size of that array
 */
double* eigen_value_calculation(double*,int);

/**
 * Executes a part of 2nd step of the Sensor Fusion Algorithm.
 * Produces a 1D array consisting of EigenVectors of one
 * EigenValue when support degree matrix in 1D array form,
 * the array size and the ordinal position of the EigenValue
 * when arranged in descending order is given to the function.
 */
double* eigen_vector_calculation(double*,int);



#endif