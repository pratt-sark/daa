//Pratyay Sarkar (BSc. Semester IV)
//Implementation of Insertion Sort (recursive)
//Program: 19

#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h> 

//macro to define the suitable swapping criteria according
//to user choosing either ascending or descending sort
#define CRITERIA(sign) (sign=='>')?(arr[j]>key):(arr[j]<key)
//sign = '>' means Ascending sort, else descending

void swap(int *x, int *y);
void input(int *arr,int n);
void display(int *arr, int n);
void insertionSort(int *arr, int n, int i, char sign);

int main() 
{ 
    printf("\n\n___________This program implements INSERTION SORT (Recursive approach)__________\n\n");
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

	//Function Call to perform insertion sort on arr[]
    //Note: It is crucial to pass 1 as the starting index for assuming 'key'
	insertionSort(arr, n, 1, sign); 

	//Display sorted array
	printf("\nSorted array: \n"); 
	display(arr, n); 

	return 0; 
}

//Function to implement insertion sort using recursion
void insertionSort(int *arr, int n, int i, char sign)
{
    if (i==n) //terminating criteria
        return;

    int key = arr[i]; //set value of key
    int j = i-1; //set an index less than that of key
 
    /**Move elements of arr[0..i-1], that are greater  
    than key (for ascending sort) or lesser than key 
    (for descending sort), to one position ahead of 
    their current position */
    while (j>=0 && CRITERIA(sign)) 
    {
        arr[j+1] = arr[j]; //move the element (> or <key) one place ahead
        j--; //decrement 'j' by 1
    }
 
    //insert key in its appropiate position
    arr[j+1] = key;
 
    //Currently the subarray [0...i-1] is sorted. This recursive call
    //passes an incremented (by 1) value of 'i' and changes the boundary
    //of next pass of insertion sort 
    insertionSort(arr, n, i+1, sign);
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