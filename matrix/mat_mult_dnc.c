//Pratyay Sarkar (BSc. Semester IV)
//Multiplication of Matrices (Divide and conquer)
//Program: 6

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int ** allocatemem(int n);
void input(int **X,int m,int n);
int** multdnc(int **X,int **Y,int n);
int** add(int **X,int **Y,int n);
void display(int **X,int m,int n);

int **A, **B, **C;
// 3 double pointers for implementing 3 matrices:
// 2 operand matrices and a resultant matrix

int m,n,p,q; 
// m*n is the order of matrix A
// p*q is the order of matrix B

void main()
{
    printf("\n This program is an implementation of Matrix multiplication using Divide and Conquer Algorithm.\n");

    step: //Accepting dimensions as input from user
    printf("\n----Receiving dimensions of Matrix 'A' ----\n");
    printf("\nEnter number of rows :\n");
    scanf("%d",&m);
    printf("\nEnter number of columns :\n");
    scanf("%d",&n);

    printf("\n\n----Receiving dimensions of Matrix 'B' ----\n");
    printf("\nEnter number of rows :\n");
    scanf("%d",&p);
    printf("\nEnter number of columns :\n");
    scanf("%d",&q);

    if (n!=p) //if number of rows of A and columns of B are NOT equal
    {
        printf("\nMultiplication cannot be performed.\n");
        printf("Re-enter dimensions such that number of rows of A and columns of B are equal.\n");
        goto step; //go back to accepting dimensions again
    }

    /**NOTE: Divide & Conquer applies only to sqaure matrices which has order in powers of 2.
    For example, a 4*4 matrix or 8*8 matrix is suitable to implement D&C upon, whereas a 3*2 
    matrix or a 6*6 matrix isn't.
    
    -----FOR MULTIPLICATION----
    To convert an unsuitable matrix to one which is suitable, we do the following:

    1. We find out the maximum of the limits of the order of input matrices.
       Eg: For a 3*2 matrix and 2*5 matrix, the above mentioned maximum (max) = 5
    
    2. We then check if the order is in powers of 2. If yes, no modification is necessary to 
       the maximum. Else, max is changed to (int)(2^(int)(log(max)base2)+1)).
       Eg: For a 3*2 matrix and 2*5 matrix, max changes to (int)(2^(int)(log5base2 + 1)) = 8

    3. The 'max' is the order of matrix suitable for applying D&C algorithm. The operand matrices 
       each are converted to a max*max matrix, preserving the index positions of elements and 
       padding the missing positions with zero. These are then operated on.
    */

    int max=(m>=q)?m:q; //calculate max of rowA and colB
    max=(max>=n)?max:n; //then calculate max of max and rowB(or colA)
    if ( (log(max)/log(2)) != (int)(log(max)/log(2)) ) //if order is not in powers of 2
        max=(int)(pow(2, (int)(log(max)/log(2))+1));

    //printf("max=%d\n",max); //for debugging

    //Memory allocation for matrices
    A = allocatemem(max);
    B = allocatemem(max);
    C = allocatemem(max);

    //Elements of operand matrices accepted as input
    printf("\n----Enter %d elements of Matrix 'A' ----\n",m*n);
    input(A,m,n);
    printf("\n----Enter %d elements of Matrix 'B' ----\n",p*q);
    input(B,p,q);

    //Original matrices displayed
    printf ("\nMatrix 1: \n");
	display(A,m,n);
	printf ("\nMatrix 2: \n");
	display(B,p,q);

    //Function for multiplying two matrices invoked
    C=multdnc(A,B,max); 

    //Resultant matrix displayed
    printf("\nAfter Matrix Multiplication, the resultant Matrix 'C' : \n");
    display(C,m,q); 
}

//for memory allocation
int ** allocatemem(int n)
{
    int i;
    int **X = (int **)calloc(n,sizeof(int *));
    for (i=0;i<n;i++)
        X[i]=(int *)calloc(n,sizeof(int));
    return X;
}

//to accept elements of matrix
void input(int **X,int m,int n)
{
	int i,j;
	for (i=0;i<m;i++)
	    for (j=0;j<n;j++)
	        scanf("%d",&X[i][j]);
}

//to display matrix
void display(int **X,int m,int n)
{
	int i,j;
	for (i=0;i<m;i++)
	{
		for (j=0;j<n;j++)
		printf("%d\t",X[i][j]);
		printf("\n");
	}
}

//function to add matrices
int** add(int **X,int **Y,int n)
{
    int **Z = allocatemem(n);
    int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
            Z[i][j] = X[i][j] + Y[i][j];
	}
    return Z;
}

//function to multiply matrices using Divide and Conquer algorithm
int** multdnc(int **X,int **Y,int n)
{
    int** Z = allocatemem(n);
    //base case
    if (n == 1) 
    {
        Z[0][0] = X[0][0] * Y[0][0];
        return Z;
    }
    else
    {
        //defining order of sub-matrices
        int k = n/2;

        //initializing sub-matrices of X
        int** X11 = allocatemem(k);
        int** X12 = allocatemem(k);
        int** X21 = allocatemem(k);
        int** X22 = allocatemem(k);

        //initializing sub-matrices of Y
        int** Y11 = allocatemem(k);
        int** Y12 = allocatemem(k);
        int** Y21 = allocatemem(k);
        int** Y22 = allocatemem(k);

        //defining sub-matrices
        for(int i=0; i<k; i++)
            for(int j=0; j<k; j++) 
            {
                //defining sub-matrices of X
                X11[i][j] = X[i][j];
                X12[i][j] = X[i][k+j];
                X21[i][j] = X[k+i][j];
                X22[i][j] = X[k+i][k+j];

                //defining sub-matrices of Y
                Y11[i][j] = Y[i][j];
                Y12[i][j] = Y[i][k+j];
                Y21[i][j] = Y[k+i][j];
                Y22[i][j] = Y[k+i][k+j];
            }

        //initializing sub-matrices of Z
        int** Z11 = allocatemem(k);
        int** Z12 = allocatemem(k);
        int** Z21 = allocatemem(k);
        int** Z22 = allocatemem(k);

        //calculating sub-matrices of Z
        Z11 = add(multdnc(X11,Y11,k), multdnc(X12,Y21,k),k);
        Z12 = add(multdnc(X11,Y12,k), multdnc(X12,Y22,k),k);
        Z21 = add(multdnc(X21,Y11,k), multdnc(X22,Y21,k),k);
        Z22 = add(multdnc(X21,Y12,k), multdnc(X22,Y22,k),k);

        //copying values to Z and returning Z
        for(int i=0; i<k; i++)
            for(int j=0; j<k; j++) 
            {
                Z[i][j] = Z11[i][j];
                Z[i][j+k] = Z12[i][j];
                Z[k+i][j] = Z21[i][j];
                Z[k+i][k+j] = Z22[i][j];
            }
        return Z;
    }
}