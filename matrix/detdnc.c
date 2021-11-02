//Pratyay Sarkar (BSc. Semester IV)
//Find determinant of a matrix (recursive)
//Program: 8

#include <stdio.h>
#include <stdlib.h>

void getCofactor(int **mat, int **temp, int cr, int cc, int n);
int determinantOfMatrix(int **mat, int n);
int ** allocatemem(int n);
void input(int **X,int n);
void display(int **X,int n);

int main()
{
	printf("\n This program is an implementation of finding Determinant of a matrix (recursive approach).\n");

    // Dimension of input square matrix (n*n)
    int n;

	//Accepting dimensions as input from user
    printf("\n----Receiving order for Matrix ----\n");
    printf("\nEnter order :\n");
    scanf("%d",&n);

	//Memory allocation for matrix & accepting elements from user
    int **A = allocatemem(n);
    printf("\n----Enter %d elements of Matrix ----\n",n*n);
    input(A,n);

	//Original matrix displayed
    printf ("\nThe Matrix: \n");
	display(A,n);

	//Function call to compute determinant
	printf("Determinant of the matrix is : %d",determinantOfMatrix(A, n));
	return 0;
}

//Function to store Co-factor of mat[p][q] in temp[][].
//n is current dimension of mat[][]
void getCofactor(int **mat, int **temp, int cr, int cc, int n)
{
	int i=0,j=0,row,col;

	// Looping for each element of the matrix
	for (row=0; row<n; row++)
	{
		for (col=0; col<n; col++) 
		{
			//Copying into temporary matrix only those
			//element which are not in given row and column
			if (row != cr && col != cc) 
			{
				temp[i][j++] = mat[row][col];

				//Row is filled, so increase row index and
				//reset col index
				if (j == n-1) 
				{
					j=0;
					i++;
				}
			}
		}
	}
}

//Recursive function for finding determinant of matrix.
//n is current dimension of mat[][].
int determinantOfMatrix(int **mat, int n)
{
	int D=0; //initialize result

	// Base case : if matrix contains single element
	if (n == 1)
		return mat[0][0];

	int **temp = allocatemem(n-1); //matrix for cofactors 

	int sign = 1; //sign multiplier
	int f;

	//iterate for each element of first row
	for (f=0; f<n; f++) 
	{
		//getting Cofactor of mat[0][f]
		getCofactor(mat, temp, 0, f, n);
		D += sign * mat[0][f] * determinantOfMatrix(temp, n-1);

		//terms are to be added with alternate sign
		sign = -sign;
	}

	return D;
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
void input(int **X, int n)
{
	int i,j;
	for (i=0;i<n;i++)
	    for (j=0;j<n;j++)
	        scanf("%d",&X[i][j]);
}

//to display matrix
void display(int **X,int n)
{
	int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
		printf("%d\t",X[i][j]);
		printf("\n");
	}
}