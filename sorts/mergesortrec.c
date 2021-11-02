//Pratyay Sarkar (BSc. Semester IV)
//Implementation of Merge Sort (recursive) 
//Program: 21

#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>

//macro to define the suitable swapping criteria according
//to user choosing either ascending or descending sort
#define CRITERIA(sign) (sign=='<')?(a[i] > b[j]):(a[i] < b[j])
//sign = '<' means Ascending sort, else descending

void merge(int *arr, int n, char sign, int low, int mid, int high);
void mergeSort(int *arr, int n, char sign, int low, int high);
void swap(int *x, int *y);
void input(int *arr,int n);
void display(int *arr, int n); 

int main() 
{ 
    printf("\n\n___________This program implements MERGE SORT (Recursive approach)__________\n\n");
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
        //or descending order.
		sign = (choice==1)?'>':(choice==2)?'<':'X';

		if (sign=='X') //for any choice other than 1 or 2
		{
			printf("\n\nINVALID CHOICE! Re-enter choice.\n.\n.\n.");
			continue;
		}	
		break;
	}

    //Function Call to perform merge sort on arr[]
	mergeSort(arr, n, sign,0,n-1); 
	//mergeSort(arr, 0,n-1); 

    //Display sorted array
	printf("\nSorted array: \n"); 
	display(arr, n); 

	return 0; 
}

void merge(int *arr, int n, char sign, int low, int mid, int high)
{
    int i, j, k;
	int n1 = mid - low + 1; //size of first subarray
	int n2 = high - mid; //size of first subarray

	//temporary subarrays created
	int a[n1], b[n2];

	//Data copied to temporary arrays a[] and b[]
	for (i = 0; i < n1; i++)
		a[i] = arr[low + i];
	for (j = 0; j < n2; j++)
		b[j] = arr[mid + j + 1];

	//Now, we will merge the temp arrays back into arr[]
	i = 0; //initial index of first subarray
	j = 0; //initial index of second subarray
	k = low; //initial index of merged array
	while (i<n1 && j<n2) 
	{
		//Find the minimum between a[i] and b[j] and store that element
		//in arr[k]. Then, increment the necessary array indices.
		if (CRITERIA(sign)) 
			arr[k] = a[i++];
		else 
			arr[k] = b[j++];
		k++; //index of merged array incrememnted
	}

	/**At this point, one of the subarrays may have remaining
	elements. We need to store them in the merged array.*/

	//copy any remaining elements of a[] into the merged array
	while (i < n1)
		arr[k++] = a[i++];
	//copy any remaining elements of b[] into the merged array
	while (j < n2)
		arr[k++] = b[j++];
}

//Function to implement merge sort using recursion
void mergeSort(int *arr, int n, char sign, int low, int high)
{
    int mid;
    if (low<high)
    {
        mid = (low+high)/2;
        mergeSort(arr,n,sign,low,mid);
        mergeSort(arr,n,sign,mid+1,high);
        merge(arr,n,sign,low,mid,high);
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