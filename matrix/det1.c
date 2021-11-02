//Pratyay Sarkar (BSc. Semester IV)
//Find determinant of a matrix using iterations
//Program: 7

#include <stdio.h>
#include <stdlib.h>

int determinantOfMatrix(int **mat, int n);
int ** allocatemem(int n);
void input(int **X,int n);
void display(int **X,int n);
void swap(int *a, int *b);

int main()
{
	printf("\n This program is an implementation of finding Determinant of a matrix (iterative approach).\n");

    //Dimension of input square matrix
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

//Function to get determinant of matrix
int determinantOfMatrix(int **mat, int n)
{
	int i,num1, num2, det=1, sign=1, index, total=1; //Initialize values

	//temporary array for storing row of pivot element
	int temp[n+1];

	// loop for traversing the diagonal elements
	for (i=0;i<n;i++) 
	{
		index = i; // initialize the index
		printf ("\nThe Matrix: \n");
		display(mat,n);printf("\ni = %d\n",i);
		// finding the index which has non zero value (pivot element)
		while (index<n && mat[index][i] == 0) 
		{
			index++;
		}
		if (index == n) // if there is no non zero element
		{
			continue;
			// the determinant of matrix is zero
			// return 0;
		}
		if (index != i) 
		{
			// loop for swaping the diagonal element row and
			// index row
			for (int j = 0; j < n; j++) 
			{
				swap(&mat[index][j], &mat[i][j]); //printf("\n*\n");
			}
			// determinant sign changes when we shift rows
            sign = -sign;
			det = det*sign;
		}

		// storing the values of pivot elements' row
		for (int j=0; j<n; j++) 
		{
			temp[j] = mat[i][j];
		}
		// traversing every row below the pivot element
		for (int j = i+1; j<n; j++) 
		{
			num1 = temp[i]; // value of diagonal element
			num2 = mat[j][i]; // value of next row element

			// traversing the each element of j-th row
			for (int k=0; k<n; k++) 
			{
				// multiplying to make the diagonal
				// element and next row element equal
				// and then subtracting 
				mat[j][k] = (num1 * mat[j][k]) - (num2 * temp[k]);
			}
			total = total * num1; // Det(kA)=kDet(A);
            // 'total' represents the product of constants multiplied to 
            // the original matrix during row operations 

			//for debugging
			//printf ("\n\nAfter %dth pivot: \n",i);
			//display(mat,n);
		}
	}

	// mulitplying the diagonal elements to get determinant
    // we know: determinant of an upper triangular matrix is
    // equal to product of principal diagonal elements
	for (int i=0; i<n; i++) 
	{
		det = det * mat[i][i];
	}
	return (det / total); // as Det(kA)/k=Det(A);
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

//to swap two numbers
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}