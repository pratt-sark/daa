//Pratyay Sarkar (BSc. Semester IV)
//Implementation of Selection Sort (iterative) 
//Program: 18

#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>

//macro to define the suitable swapping criteria according
//to user choosing either ascending or descending sort
#define CRITERIA(sign) (sign=='<')?(arr[j] < arr[min_or_max]):(arr[j] > arr[min_or_max])
//sign = '<' means Ascending sort, else descending

void selectionSort(int *arr, int n, char sign);
void swap(int *x, int *y);
void input(int *arr,int n);
void display(int *arr, int n); 

int main() 
{ 
	printf("\n\n___________This program implements SELECTION SORT (Iterative approach)__________\n\n");
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
		sign = (choice==1)?'<':(choice==2)?'>':'X';

		if (sign=='X') //for any choice other than 1 or 2
		{
			printf("\n\nINVALID CHOICE! Re-enter choice.\n.\n.\n.");
			continue;
		}	
		break;
	}

	//Function Call to perform selection sort on arr[]
	selectionSort(arr, n, sign); 

	//Display sorted array
	printf("\nSorted array: \n"); 
	display(arr, n); 

	return 0; 
}

//Function to implement selection sort 
void selectionSort(int *arr, int n, char sign)
{ 
    int i, j, min_or_max; 
  
    //Move boundary of unsorted subarray one by one
    for (i=0; i<n-1; i++) 
    { 
        //Assume the position of minimum(or maximum, depending 
        //on ascending or descending) element positon as 'i' 
        min_or_max = i;

        //Find the minimum(or maximum, depends) element's positon
        //in unsorted array 
        for (j = i+1; j<n; j++) 
            if (CRITERIA(sign)) //if swapping criteria is fulfilled
                min_or_max=j; //update the value of  max_or_min to j 
  
        //Swap the found minimum element (or maximum, depends)
        //with the first element of the unsorted array
        swap(&arr[min_or_max], &arr[i]); 
    } 
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