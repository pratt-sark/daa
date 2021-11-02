//Pratyay Sarkar (BSc. Semester IV)
//Multiplication of Matrices (mostly used)
//Program: 3

#include <stdio.h>
#include <stdlib.h>

int ** allocatemem(int r,int c);
void input(int **X,int r,int c);
void mult(int **X,int **Y,int **Z,int m,int p,int q);
void display(int **X,int r,int c);

int **A, **B, **C;
// 3 double pointers for implementing 3 matrices:
// 2 operand matrices and a resultant matrix

int m,n,p,q;
// m*n is the order of matrix A
// p*q is the order of matrix B

void main()
{
    printf("\n This program is an implementation of Matrix Multiplication.\n");

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

    //Memory allocation for matrices
    A = allocatemem(m,n);
    B = allocatemem(p,q);
    C = allocatemem(p,q);

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
    mult(A,B,C,m,p,q); 

    //Resultant matrix displayed
    printf("\nAfter Matrix Multiplication, the resultant Matrix 'C' : \n");
    display(C,m,q); 
}

//Allocate memory for a matrix
int ** allocatemem(int r, int c)
{
    int i;
    int **X = (int **)calloc(r,sizeof(int *));
    for (i=0;i<r;i++)
        X[i]=(int *)calloc(c,sizeof(int));
    return X;
}

//Accept elements of a matrix from user
void input(int **X,int r,int c)
{
	int i,j;
	for (i=0;i<r;i++)
	    for (j=0;j<c;j++)
	        scanf("%d",&X[i][j]);
}

//Display a matrix of dimensions r*c
void display(int **X,int r,int c)
{
	int i,j;
	for (i=0;i<r;i++)
	{
		for (j=0;j<c;j++)
		printf("%d\t",X[i][j]);
		printf("\n");
	}
}

//Add two matrices of dimensions m*p and p*q respectively
void mult(int **X,int **Y,int **Z,int m,int p,int q)
{
	int i,j,k;
	for (i=0;i<m;i++)
	{
		for (j=0;j<q;j++)
		{
			for (k=0;k<p;k++)
			    Z[i][j] = Z[i][j] + (X[i][k]*Y[k][j]);
		}
	}
}