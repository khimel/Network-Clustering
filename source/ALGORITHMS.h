/**
 * ALGORITHMS Summary:
 *
 *  Module of all algorithm's functions used in project CLUSTER
 *
 * algo_3 - returns a set of final modularity groups.
 *
 * algo_2 - divide GROUP g into two modularity groups.
 *
 * computeLead - computes leading eigen vector and leading eigen value of b^[g].
 *
 * norm_1 - computes norm1 of matrix B, where norm1 is the sum of its largest column.
 *
 * computeDominVec - computes dominating eigen vector of shifted b^[g].
 *
 * computeLeadVal - computes leading eigen value from leading eigen vector and shifted b^[g].
 *
 * compute_S - updates vector s's values to 1/-1 according to the leading eigen pair and maximizes the partition.
 *
 * improve_S - maximizes modularity of given partition presented by vector s.
 *
 * computeModularity - computes modularity of given partition presented by vector s and matrix B^[g].
 *
 * mult_B_g - computes the multiplication of the matrix B^[g]/B[g] with given vector v.
 *
 * sum_of_rows -  calculates the sum of rows of matrix B[g] (f_i_g), updates vector sums = [f_1_g, f_2_g,...., f_ng_g] .
 *
 * compute_g1_g2 - allocates g1,g2 according to vector s and GROUP g and fills them with correct indices.
 *
 * vectorMagnitude - computes vector's magnitude.

 * differenceIsZero - returns 1 if the absolute difference between vec1 and vec2 IS_POSITIVE, or 0 otherwise.
 *
 * find_max_arr - returns index of the element with maximal value in array arr.
 *
 * get_row_B_g - computes vector of the row of the matrix B[g].
 *
 *
 */

#include "SET.h"
#include "eigenPAIR.h"
#include <float.h>


#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

int q;
eigenPAIR *leadPair;
double *b0;
double *s;
double *mult_1;
double *my_tmp;
double *sums;
int *unmoved;
double *improve;
int *indices;
double *score, *x,*Bg_row;

#define IS_POSITIVE(X) ((X) > 0.00001)


/*
	 *The function algo_3 returns a set of final modularity groups.
	 *@param A - sparse matrix A, representing the input network
	 *@return SET of final modularity groups of matrix A
*/

SET* algo_3(spmat *A);



/*
	 *The function algo_2 divides GROUP g into two modularity groups, updates global variable vector s of partition.
	 *@param A - sparse matrix A, representing the input network
	 *@param g - GROUP g, to be divided into two modularity groups
	 *@param norm - norm1 of matrix B^[g], norm1 is the sum of its largest column
	 *@return
*/
void algo_2(spmat *A, GROUP *g, double norm);

/*
	 *The function computeLead computes leading eigen vector and leading eigen value of b^[g], updates global variable leadPair.
	 *@param A - sparse matrix A, representing the input network
	 *@param g - GROUP, representing sub matrix of A
	 *@param norm - norm1 of matrix B^[g], where norm1 is the sum of its largest column
	 *@return
*/


void computeLead(spmat *A, GROUP *g, double norm);


/*
	 *The function norm_1 computes norm1 of matrix B, where norm1 is the sum of its largest column.
	 *@param A - sparse matrix A, representing the input network
	 *@return norm1 of matrix B^[g]
*/
double norm_1(spmat *A);


/*
	 *The function computeDominVec computes dominating eigen vector of shifted b^[g], updates global variable leadPair.
	 *@param A - sparse matrix A, representing the input network
	 *@param g - GROUP g, representing sub matrix of A
	 *@param norm - norm1 of matrix B^[g], where norm1 is the sum of its largest column
	 *@return
*/
void computeDominVec(spmat* A, GROUP *g, double norm);


/*
	 *The function computeLeadVal computes leading eigen value from leading eigen vector and shifted b^[g], updates global variable leadPair.
	 *@param A - sparse matrix A, representing the input network
	 *@param g - GROUP g, representing sub matrix of A
	 *@param norm - norm1 of matrix B^[g], where norm1 is the sum of its largest column
	 *@return
*/
void computeLeadVal(spmat *A, GROUP *g, double norm);


/*
	 *The function compute_S updates vector s's values to 1/-1 according to the leading eigen pair and maximizes the partition.
	 *@param A - sparse matrix A, representing the input network
	 *@param g - GROUP g, representing sub matrix of A
	 *@return
*/
void compute_S(spmat *A, GROUP *g);



/*
	 *The function improve_S  maximizes modularity of given partition presented by vector s, updates vector s accordingly.
	 *@param A - sparse matrix A, representing the input network
	 *@param g - GROUP g, representing sub matrix of A
	 *@return
*/
void improve_S(spmat *A, GROUP *g);


/*
	 *The function computeModularity computes modularity of given partition presented by vector s and matrix B^[g].
	 *@param A - sparse matrix A, representing the input network
	 *@param g - GROUP g, representing sub matrix of A
	 *@return
*/
double computeModularity(spmat *A, GROUP *g);


/*
	 *The function mult_B_g computes the multiplication of the matrix B^[g]/B[g] with given vector v.
	 *@param A - sparse matrix A, representing the input network
	 *@param g - GROUP g, representing sub matrix of A
	 *@param s- vector s to be multiplied with matrix B^[g]
	 *@param res - result vector of the multiplication.
	 *@param kova - boolean value 0/1 - choose to multiplicate B^[g] or B[g].
	 *@return
*/
void mult_B_g(spmat *A, GROUP *g, double *s, double *res, int kova);




/*
	 *The function sum_of_rows calculates the sum of rows of matrix B[g] (f_i_g), updates global vector sums = [f_1_g, f_2_g,...., f_ng_g] .
	 *@param A - sparse matrix A, representing the input network
	 *@param g - GROUP g, representing sub matrix of A
	 *@return
*/
void sum_of_rows(spmat *A, GROUP *g);



/*
	 *The function compute_g1_g2 allocates g1,g2 according to vector s and GROUP g and fills them with correct indices.
	 *@param g - GROUP g, representing sub matrix of A
	 *@param g1- GROUP g1, to be generated according to vector s
	 *@param g2- GROUP g2, to be generated according to vector s
	 *@return
*/
void compute_g1_g2(GROUP *g, GROUP **g1, GROUP **g2);


/*
	 *The function vectorMagnitude computes vector's magnitude.
	 *@param g - GROUP g, representing sub matrix of A
	 *@param vec - the function calculates its magnitude
	 *@return vec's magnitude
*/
double vectorMagnitude (GROUP *g, double *vec);


/*
	 *The function differenceIsZero returns 1 if the absolute difference between vec1 and vec2 IS_POSITIVE, or 0 otherwise
	 **meaning smaller than 0.00001 .
	 *@param g - GROUP g, representing sub matrix of A
	 *@param vec1 - first vector
	 *@param vec2 - second vector
	 *@return 0 or 1 representing false or true respectively
*/
int differenceIsZero(GROUP *g, double *vec1, double *vec2);


/*
	 *The function find_max_arr returns index of the element with maximal value in array arr, from elements that are not moved (used in improve_S func).
	 **@param arr - array arr
	 *@param g - GROUP g, representing sub matrix of A
	 *@param unmoved - boolean array representing which elements were moved from arr nada: from arr?
	 *@return index of the element with maximal value
*/
int find_max_arr(double *arr, GROUP *g, int *unmoved);


/*
	 *The function get_row_B_g computes vector of the row of the matrix B[g] ( derives it from A, vector k and value M).
	 *@param A - array arr
	 *@param g - GROUP g, representing sub matrix of A
	 *@param j_tag  - number of wanted row.
	 *@param res - vector presenting the row of B[g].s
	 *@return
*/
void get_row_B_g(spmat *A,GROUP *g, int j_tag, double *res);

#endif /* ALGORITHMS_H_ */
