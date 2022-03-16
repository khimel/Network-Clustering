/**
 * spmat Summary:
 *
 *  Module spmat represents linked list sparse matrix
 *
 *spmat_allocate_list - allocates and initializes sparse matrix of size n.
 *
 *insertLast - inserts a node in the end of a linked list.
 *
 *add_row_list - adds a new row to the sparse matrix.
 *
 *free_list - releases the memory allocated for spmat.
 *
 *mult_list - calculates multiplication of A[g] with vector v.
 *
 */

#include <time.h>
#include <math.h>
#include "GROUP.h"

#ifndef _SPMAT_H
#define _SPMAT_H


typedef struct _node{
	double val; /* changed from double to int!!!!!!!!!! */
	int colInd;
	struct _node *next;
} node;

typedef struct _list{
	node *head;
	node *tail;
	int len;
}list;


typedef struct _spmat {
	/* Matrix size (n*n) */
	int		n;
	list **Mat; /* ineer implementation */
	double M; /* sum of all degrees */
	double *k; /* vector k = [k0,k1,...,kn] where ki is the degree of node i */
} spmat;


/*
	 *The function spmat_allocate_list allocates a new linked-lists sparse matrix of size n.
	 *@param n- size of the matrix
	 *@return spmat - the allocated sparse matrix
*/
spmat* spmat_allocate_list(int n);


/*
	 *The function insertLast inserts a node in the end of a linked list.
	 *@param listy - given linked list.
	 *@param value - node value.
	 *@param colIndex - node colomun index.
	 *@return
*/
void insertLast(list *listy, double value, int colIndex);


/*
	 *The function add_row_list adds a new row to the spmat A. nada: saaa7?
	 *@param A - the modified spmat
	 *@param rpw - the row to be added
	 *@param i - number of row .
	 *@return
*/
void add_row_list(struct _spmat *A, const double *row, int i);


/*
	 *The function free_list releases the memory allocated for spmat.
	 *@param A - the modified spmat
	 *@return
*/
void free_list(struct _spmat *A);

/* Calculates B^[g] * v */

/*
	 *The function mult_list calculates multiplication of A[g] with vector v.
	 *@param A - the modified spmat
	 *@param g - represents sub matrix of A
	 *@param v - vector to multiply it with A
	 *@param result - where result of multiplication is saved
	 *@return
*/
void mult_list(const struct _spmat *A, GROUP *g, const double *v, double *result);


/*
	*Binary search  value x in given indices of group g.
	*@param g - the given group.
	*@param x - the value to be searched.
	*@return - returns the index of the vlue if found, else -1.
*/
int binarySearch(GROUP *g, int l, int r, int x);

#endif
