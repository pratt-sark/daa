//Pratyay Sarkar (BSc. Semester IV)
//Finding minimum number of scalar multiplications in matrix
//chain multiplication and the multiplying sequence
//Program: 22

#include<stdio.h>
#include<stdlib.h>

//number of matrices at first, and then after increment, 
//it represents number of inputs required (no. of matrices + 1)
int n; 

//matrix -The sequence matrix from which it can be determined which multiplication
//operation to do at last, in a specified range -> [left,right] where left<right.
int **matrix;

int calculate(int *arr,int left,int right);
void printPar(int left,int right,char *matName);
void allocatemem ();
void displayMatrix ();

void main()
{

	int i; //used as control variable  of loops
	char matName='A'; //name of the matrices, necessary for printing parenthesized form

	//input - number of matrices
	printf("\nEnter the number of matrices:\n");
	scanf("%d",&n);

	n++; //for n matrices, n+1 inputs are required, hence the increment

	//memory alocation for array containing the rows and columns
	int *arr = (int *)calloc(n,sizeof(int));

	//orders accepted from user
	//Eg: For 3 matrices A(2*3),B(3*4) and C(4*3), the array = {2,3,4,3}
	printf("\nEnter row limits for %d matrices and \ncolumn limit of the last matrix at the end:\n",n-1);
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	
	//printing array containing the rows and columns
	printf("\nArray containing the rows and columns:\n");
	for(i=0;i<n;i++)
		printf("%d\t",arr[i]);

	//printing a confirmation so that the user can visualize 
	//and check whether the input was correct or flawed
	printf("\n\nYou've chosen matrices as follows:\n\n");
	for(i=0;i<n-1;i++)
		printf("Matrix %c of Order (%d * %d)\n",matName++,arr[i],arr[i+1]);
	
	//allocating memory for the sequence matrix
	allocatemem(matrix);
	
	//calculating and printing minimum number of scalar multiplications
	printf("\nMinimum number of scalar multiplications = %d\n",calculate(arr,1,n-1));
	
	printf("\nParenthesized form of matrix multiplication: ");
	matName = 'A'; //reinitializzed to 'A'
	printPar(1,n-1,&matName); //calling the parenthesizing function
	
	//display the sequence matrix if required
	displayMatrix(matrix,n);		
}

//To calculate minimum number of scalar multiplications
int calculate(int *arr,int left,int right)
{
	//base case; if the situation represents a single matrix it is 
	//obvious, cause how many scalar multiplications are required 
	//if there is only one matrix? None. Zero.
	if(right==left)
		return 0;
	
	int i,j,min = INT_MAX;
	for(i=left;i<right;i++)
	{
		//To multiply two matrices, the number of scalar multiplications = arr[left-1]*arr[i]*arr[right]
		int value = calculate(arr,left,i) + calculate(arr,i+1,right) + arr[left-1]*arr[i]*arr[right];
		if(min >= value)
		{
			min = value;
			matrix[left][right] = i;
			//Within range -> [left,right], i-th multiplication to be done at the last
			//where left<right
		}
	}
	return min;
}

//To print parenthesized form of the matrix chain multiplication
void printPar(int left,int right,char *matName)
{
	//to be uncommented during testing/debugging
	//printf("%d %d %c\n",left,right,*name);
	if(left == right)
	{
		printf("%c",*matName);
		*matName = *matName + 1;
		return;
	}
	printf("(");
	printPar(left,matrix[left][right],matName);
	printPar(matrix[left][right]+1,right,matName);
	printf(")");
}

//allocating memory for matrix
void allocatemem()
{
	int i;
	matrix = (int **)calloc(n,sizeof(int *));
		for(i=0;i<n;i++)
			matrix[i] = (int *)calloc(n,sizeof(int));
}

//displaying the sequence matrix
void displayMatrix()
{
	int i,j;
	printf("\n\nThe sequence matrix :\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			printf("%d ",matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

/* _________DISCUSSION ON THE APPROACH USED______
 
matrix -The sequence matrix from which it can be determined which multiplication
operation to do at last, in a specified range -> [left,right] where left<right.

Element representation:   
matrix[i][j] = 
index of the element following the * operation which is 
to be performed at last in range -> [i,j] , where i<j

EG: If 3 matrices A(4,2),B(2,5) and C(5,3) are to be multiplied - 
Imagine each array index from [1 to n-2] represent a * operation
For the above example, the array = {4,2,5,3}. Note that there are two * operations
before indices 1(element 2) and 2(element 5), representing the *s in A * B * C.

Now, the answer is (A(BC)). We can use it to cross check the matrix.
In range [1,2], matrix[1][2] = 1, meaning the * operation before B is to be done at last.
In range [1,3], matrix[1][3] = 1, meaning the * operation before B is to be done at last.
Similarly, In range [2,3], matrix[2][3] = 2, meaning the * operation before C is to be done at last.
Note that in this case, there is only one * operation in the range, i.e. the one before C.

Therefore, we start with the range (left=1 to right=n-1). If left==right, print the matrix name 
and change it to next matrix name. Otherwise, print a '(' , then recur(left,matrix[left][right]), 
then recur (matrix[left][right]+1,right), then print ')' .
*/	