//Pratyay Sarkar (BSc. Semester IV)
//Implementation of Bubble Sort (recursive) 
//Program: 18

#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>

//macro to define the suitable swapping criteria according
//to user choosing either ascending or descending sort
#define CRITERIA(sign) (sign=='>')?(arr[j] > arr[j+1]):(arr[j] < arr[j+1])
//sign = '>' means Ascending sort, else descending

void bubbleSort(int *arr, int n, char sign);
void swap(int *x, int *y);
void input(int *arr,int n);
void display(int *arr, int n); 

int main() 
{ 
    printf("\n\n___________This program implements BUBBLE SORT (Recursive approach)__________\n\n");
    //arr - array of integers
	//n - number of integers in the array
    int n,*arr;

    step:
	
	//Accept array length from user
    printf("\nEnter number of elements:\n");
	scanf("%d",&n);

	if (n<=0)
	{
		printf("\nInvalid Value. Enter a positive number.\n");
		goto step;
	}

    //Allocate memory for arr[] array
    arr = (int *)calloc(n,sizeof(int));

    //Accept array elements from user
    printf("\nEnter %d elements:\n",n);
    input(arr,n);

    //Display original array
    printf("\nOriginal array: \n"); 
    display(arr, n); 

    //Choosing ascending or descending sort
	printf("\nDo you want Ascending Sort or Descending Sort?\n");
	int choice; char sign; 
	while(true)
	{
		printf("\nEnter 1 for Ascending Sort\nEnter 2 for Descending Sort\n");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);

        //holds '<' or '>' or any other character, depending on user's choice
        //signifies whether we need to sort the list of elements in ascending
        //or descending order
		sign = (choice==1)?'>':(choice==2)?'<':'X';

		if (sign=='X') //for any choice other than 1 or 2
		{
			printf("\n\nINVALID CHOICE! Re-enter choice.\n.\n.\n.");
			continue;
		}	
		break;
	}

    //Function Call to perform bubble sort on arr[]
	bubbleSort(arr, n, sign); 

    //Display sorted array
	printf("\nSorted array: \n"); 
	display(arr, n); 

	return 0; 
} 

//Function to implement bubble sort using recursion
void bubbleSort(int *arr, int n, char sign)
{
    if (n==1) return; //base case, a single element is always sorted

    //loop for a single pass of bubble sort. After this loop ends, the 
    //largest (or smallest, depending on ascending or descending type)
    //element in the range [0, current(n)-1] is pushed to the (n-1)th 
    //index of the array arr[].
    for (int j=0; j<n-1; j++)
    {
        if (CRITERIA(sign)) //if swapping criteria is fulfilled
            swap(&arr[j],&arr[j+1]); //swap the elements
    }
 
    //This recursive call shrinks the boundary of the next pass of 
    //bubble sort, by passing a decreased (by 1) value of 'n'.
    bubbleSort(arr, n-1, sign);
}

//To swap two integers by reference
void swap(int *x, int *y) 
{ 
	int temp = *x; 
	*x = *y; 
	*y = temp; 
}

//To accept array elements from user
void input(int *arr,int n)
{
    int i;
    for (i=0;i<n;i++)
        scanf("%d",&arr[i]);
}

//To display an integer array of length n
void display(int *arr, int n) 
{ 
	int i; 
	for (i=0; i<n; i++) 
		printf("%d\t", arr[i]); 
	printf("\n\n"); 
}