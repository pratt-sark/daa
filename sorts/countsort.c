//Pratyay Sarkar (BSc. Semester IV)
//Implementation of Counting Sort
//Program: 30

#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>

void countSort(int *arr, int n);
int get_max (int *a, int n);
void swap(int *x, int *y);
void input(int *arr,int n);
void display(int *arr, int n); 

int main() 
{ 
    printf("\n\n___________This program implements COUNTING SORT__________\n\n");
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
    printf("\n\nNOTE: Enter positive values only.\n\n");
    printf("\nEnter %d elements:\n",n);
    input(arr,n);

    //Display original array
    printf("\nOriginal array: \n"); 
    display(arr, n); 

    //Function Call to perform bubble sort on arr[]
	countSort(arr, n); 

	return 0; 
}

//Performs counting sort on an array of n elements
void countSort(int *arr,int n)
{
    //acts as final sorted array
    int *fin_array = (int *)calloc(n,sizeof(int));
    
    //finding the maximum value in the array
    int max=get_max(arr,n);
    
    //implements the count array
    int *count_arr = (int *)calloc(max+1,sizeof(int));
    for (int i=0;i<n;i++)
        count_arr[arr[i]]++;

    //Now, change count[i] so that count[i] now contains
    //actual position of this digit in output[]
    //performs cumulative sum of the contents of count array
    for (int i=1;i<max+1;i++)
        count_arr[i]= count_arr[i] + count_arr[i-1];
    
    //forming the final sorted array
    for (int i=0;i<n;i++)
    {
        fin_array[count_arr[arr[i]]-1] = arr[i];
        count_arr[arr[i]]--;
    }

    //Display sorted array
	printf("\nSorted array: \n"); 
	display(fin_array, n); 
}

//returns the maximum value from an array
int get_max (int *a, int n)
{
   int max = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
   return max;
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