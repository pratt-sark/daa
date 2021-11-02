//Pratyay Sarkar (BSc. Semester IV)
//Implementation of Quick Sort
//Program: 29

#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>

void quickSort(int *arr, int n, int,int);
void swap(int *x, int *y);
void input(int *arr,int n);
void display(int *arr, int n); 

int main() 
{ 
    printf("\n\n___________This program implements QUICK SORT__________\n\n");
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

    //Function Call to perform bubble sort on arr[]
	quickSort(arr, n, 0,n); 

    //Display sorted array
	printf("\nSorted array: \n"); 
	display(arr, n); 

	return 0; 
}

/* This function takes first element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot) to
left of pivot and all greater elements to right of pivot */
int partition(int *arr, int n, int low, int high)
{
    /**One pass showed as an example.
    34 12 44 2 76 56 9 33
    34 12 33 2 76 56 9 44
    34 12 33 2 9 56 76 44
    9 12 33 2 34 56 76 44 */
    int pivot = arr[low]; //pivot considered to be the first element, i.e. arr[low]
    int i=low,j=high-1; //iterators of the array, from front and back

    while(i<j) //while front iterator is less than back iterator
    {
        while (arr[i]<=pivot) //this loop ends when it finds a value > pivot
            i++;
        while (arr[j]>pivot) //this loop ends when it finds a value <= pivot
            j--;
        if (i<j) //if condition is satsfied, swap i-th and j-th element
            swap(&arr[i],&arr[j]);
    }
    swap(&arr[low],&arr[j]); //put pivot in its appropiate position
    printf("\n\nAfter a pass:\t");display(arr, n);printf("\nPivot = %d, i = %d\n",pivot,j);
    return j; //return the position of partition (or, the changed position of pivot)
}

//Function to implement quick sort using recursion
void quickSort(int *arr, int n, int low, int high)
{
    int j;
    if (low<high)
    {
        //find podition of partition
        j = partition(arr,n,low,high);
        quickSort(arr,n,low,j); //recursive call for the left subarray
        quickSort(arr,n,j+1,high); //recursive call for the right subarray
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