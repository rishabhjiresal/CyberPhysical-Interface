#include "EigenTest.h"
#include<iostream>

// int TestFunction() {
//   MatrixXd m(2,2);
//   m(0,0) = 3;
//   m(1,0) = 2.5;
//   m(0,1) = -1;
//   m(1,1) = m(1,0) + m(0,1);
//   std::cout << m << std::endl;
// }

/** \brief Calculate Support Degree Matrix.
 *
 *  Creates the support degree matrix as a 1D array instead of a 2D array
 *  to make it easier for the calculation of Eigen Values and Eigen Vectors
 *  using the gsl library.
 *
 *  @param[in] sensorinputs Readings of all sensors for a specific timestamp.
 *  @param[in] size The number of sensors being considered.
 *
 *  \return A 1D array which is the Support Degree Matrix.
 */
double* sdm_calculator(double sensorinputs[], int size){

    int i,j,k=0;
    printf("size %d\n", size);
    double *dmatrix = (double *) malloc(sizeof(double)*(size*size));

    for(i=0; i<size;i++){

        for(j=0;j<size;j++){
            double temp = sensorinputs[i]-sensorinputs[j];

            if(temp<0){
                temp = -temp;
            }

            temp = exp(-(temp));
            dmatrix[k]= temp;
           // printf("%lf\t",dmatrix[k]);
            k++;

            if(k%size==0){
            //printf("\n");
            }
        }
    }
    return dmatrix;
}


/** \brief Calculates EigenValues for a given Support Degree Matrix.
 *
 *  Creates an 1D array of EigenValues for a given support degree matrix
 *  using functions from the gsl external library.
 *
 *  @param[in] dmatrix The Support Degree matrix produced by sdm_calculator
 *   function.
 *  @param[in] size The number of sensors being considered which is same as
 *   size of dmatrix.
 *
 *  \return A 1D array of EigenValues in descending order for the given dmatrix.
 */
double* eigen_value_calculation(double* dmatrix, int size){
   // int i;
    MatrixXd dmatrix1 = Map<MatrixXd>( dmatrix, size, size );
      //  cout<< dmatrix1 << endl;
   // EigenSolver<MatrixXd> solver(dmatrix1);
   // cout << "The eigenvalues of dmatrix are:" << endl << solver.eigenvalues() << endl;

    // gsl_matrix_view m = gsl_matrix_view_array (dmatrix, size, size);
    // gsl_vector *eval = gsl_vector_alloc (size);
    // gsl_matrix *evec = gsl_matrix_alloc (size, size);
    // gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (size);
    // gsl_eigen_symmv (&m.matrix, eval, evec, w);
    // gsl_eigen_symmv_free (w);
    // gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_DESC);
    // double *eval_i = (double *) malloc(sizeof(double)*(size));
    // for(i = 0; i < size; i++){
    //     eval_i[i] = gsl_vector_get (eval, i);
    //     //printf("eigenvalue = %g\n", eval_i[i]);
    // }
    // gsl_matrix_free(evec);
    // gsl_vector_free(eval);
    // return eval_i;
}


/** \brief Produces EigenVectors for a specific EigenValue of
 *   Support Degree Matrix.
 *
 *  Creates an 1D array of EigenVectors for a given support degree matrix
 *  using functions from the gsl external library. The actual EigenValue is
 *  not supplied but the position of EigenValue in a descending sorted
 *  array of EigenValues as returned by eigen_value_calculation method is
 *  given.
 *
 *  @param[in] dmatrix The Support Degree matrix produced by sdm_calculator
 *   function.
 *  @param[in] size The number of sensors being considered which is same as
 *   size of dmatrix.
 *  @param[in] column The column number of the EigenVector matrix produced
 *   by the gsl library. This is same as the position of EigenValue when
 *   the EigenValues are sorted in descending order.
 *
 *  \return A 1D array of EigenVectors for the given EigenValue.
 */
double* eigen_vector_calculation(double* dmatrix, int size){

    MatrixXd dmatrix1 = Map<MatrixXd>( dmatrix, size, size );
     //   cout<< dmatrix1 << endl;
    EigenSolver<MatrixXd> solver(dmatrix1);
    cout << "The eigen vectors of dmatrix are:" << endl << solver.eigenvectors() << endl <<endl;

    // int i;
    // gsl_matrix_view m = gsl_matrix_view_array (dmatrix, size, size);
    // gsl_vector *eval = gsl_vector_alloc (size);
    // gsl_matrix *evec = gsl_matrix_alloc (size, size);
    // gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (size);
    // gsl_eigen_symmv (&m.matrix, eval, evec, w);
    // gsl_eigen_symmv_free (w);
    // gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_DESC);
    // double *evec_i =(double *) malloc(sizeof(double)*(size));
    // for(i=0;i<size;i++){
    //     evec_i[i]= gsl_matrix_get(evec, i, column);
    //     //printf("Eigen Vector: %g\n", evec_i[i]);
    // }
    // gsl_matrix_free(evec);
    // gsl_vector_free(eval);
    // return evec_i;
}
