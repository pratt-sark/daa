//Pratyay Sarkar (BSc. Semester IV)
//Implementation of Radix Sort
//Program: 31

#include<stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

void input(int *arr,int n);
void display(int *arr, int n);
void radixSort(int *arr, int n,char c);
void countSort(int *arr, int n, int exp,char c);

int k; //number of passes

void main() 
{ 
    printf("\n\n___________This program implements RADIX SORT__________\n\n");
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

        //holds 'a' or 'b' or any other character, depending on user's choice
        //signifies whether we need to sort the list of elements in ascending
        //or descending order
		sign = (choice==1)?'a':(choice==2)?'d':'X';

		if (sign=='X') //for any choice other than 1 or 2
		{
            fflush(stdin);
			printf("\n\nINVALID CHOICE! Re-enter choice.\n.\n.\n.");
			continue;
		}	
		break;
	}

    k=0; //number of passes
    //Function Call to perform bubble sort on arr[]
	radixSort(arr,n,sign);

    //Display sorted array
	printf("\nSorted array: \n"); 
	display(arr, n); 
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

//Performs counting sort of an array according to
//the current digit represented by exp.
void countSort(int *arr, int n, int exp, char sign)
{
    int output[n]; //acts as final sorted array
    int i;
    int count[10] = {0}; //count array initialised with zeros
 
    //Store count of occurrences of each number's last digit
    //in their respective indices in count
    for (i=0; i<n; i++)
        count[(arr[i]/exp) % 10]++;
 
    //Now, change count[i] so that count[i] now contains
    //actual position of this digit in output[]. 
    //performs cumulative sum of the contents of count array
    for (i=1; i<10; i++)
        count[i] = count[i] + count[i-1];
 
    //forming the final sorted array
    for (i=n-1; i>=0; i--)
    {
        output[count[(arr[i]/exp) % 10] - 1] = arr[i];
        count[(arr[i]/exp) % 10]--;
    }
 
    //copy output array to arr[]
    //arr[] now contains sorted numbers according to current digit
    if (sign == 'a') //for ascending order
        for (i=0; i<n; i++)
            arr[i] = output[i];
    else //for descending order
        for (i=0; i<n; i++)
            arr[i] = output[n-i-1];

    //for debugging 
    //printf("\nAfter %d pass: ",k);
    //display(arr, n); k++;
}
 
//Performs radix sort on an array of n elements
void radixSort(int *arr, int n, char sign)
{
    //useful in knowing the number of maximum digits ocurring in a single number
    int max = get_max(arr, n); //the maximum number in the list

    /** Counting sort is performed for every digit. Exp is passed to
    countingSort(int*,int,int) and NOT the digit. Exp=10^(digit number).
    Eg: For the digit 6 in 546, Exp= 10^0= 1

    Each pass of the loop below sorts the numbers in the list according to their
    unit's place digit/ten's place digit/... according to the value of exp passed.
    */
    for (int exp=1; max/exp>0; exp*=10)
        countSort(arr,n,exp,sign);
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