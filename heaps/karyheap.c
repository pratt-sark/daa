//Pratyay Sarkar (BSc. Semester IV)
//Implementation of heap and heapsort (k-ary tree)
//Program: 25

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//macro to define the suitable swapping criteria according
//to user choosing either minheap or maxheap
#define comp(heap_type) (heap_type=='i')?(child[j]<size && heap[child[j]]<heap[smallest]):(child[j]<size && heap[child[j]]>heap[smallest])

int* heap; //globally declared heap
char heap_type; //type of heap

/** ___Some information____
j-th child of node at  index i = k*i+j, for j in [1,k]
j-th child of node at  index i = k*i+j+1, for j in [0,k]
Parent node of index i = floor((i-1)/k)*/

void input(int x);
void display(int x,int rev);
void swap(int x,int y);
void createHeap(int i, int size,int k);
void buildHeap(int n,int k);
void heapSort(int size,int k);

//execution starts here
void main()
{
    int n,k,ch;
    // n - size of array 'heap'
    // ch - choice of user
    // k - number of children (k-value of a k-ary tree)

    enterkvalue:
        printf("\n\nEnter the value of k for a k-ary heap:\n");
        scanf("%d",&k);
        if (k<=1)
        {
            printf("\nInvalid Value. Enter a value greater than or equal to 2.\n");
            goto enterkvalue;
        }
    step:
        printf("\nEnter total number of elements :\n");
        scanf("%d",&n);
        if (n<=0)
        {
            printf("\nInvalid Value. Enter a positive value.\n");
            goto step;
        }

    //memory allocation of heap
    heap = (int *)calloc(n, sizeof(int));
    //elements entered by user
    input(n);

    enterheaptype:
        printf("\n\nSelect Heap type --->\n1. Min Heap\n2. Max Heap\n\nEnter your choice:\n");
        scanf("%d",&ch); //accept type of heap
        heap_type=(ch==1)?'i':(ch==2)?'a':'X';
        if (heap_type=='X')
        {
            printf("\nInvalid Input. Re-enter heap type.\n");
            goto enterheaptype;
        }

    //build the heap
    buildHeap(n,k);
    //heap displayed
    display(n,0);

    entersorttype:
        printf("\nDo you want Ascending Sort or Descending Sort?\n1. Ascending Sort\n2. Descending Sort\n");
        printf("\nEnter your choice:\n");
        scanf("%d",&ch); //accept type of sort
        //holds '<' or '>' or any other character, depending on user's choice
        //signifies whether we need to sort the heap in ascending or descending order
        char sign = (ch==1)?'a':(ch==2)?'d':'X';
        if (sign=='X') //for any choice other than 1 or 2
        {
            printf("\n\nINVALID CHOICE! Re-enter choice.\n.\n.");
            goto entersorttype;
        }
    
    int rev=0;
    printf("\nAfter Sorting : \n");
    //if the heap is minheap and the sort type is ascending,
    //the array needs to be displayed in reversed order
    if (heap_type=='i' && sign=='a')
        rev = 1;
    //if the heap is maxheap and the sort type is descending,
    //the array needs to be displayed in reversed order
    else if (heap_type=='a' && sign=='d')
        rev = 1;
    heapSort(n,k); //call to heapsort (int,int) 
    display(n,rev); //display heap after sorting
}

//building the heap
void buildHeap(int n,int k)
{
    int i;
    /**
    ------------Creation of heap-------------------
    
    Starting point of 'i' in loop to avoid leaf node checkings
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

    Update: In C, (n-1)/k == ceil ((n-1)/k) - 1. However, for better 
    algorithmic understanding purpose, ceil ((n-1)/k) - 1 is used.

    Update 2: In C, ceil ((n-1)/k) - 1 needs to be written as 
    ceil ((n-1)*1.0/k) - 1, otherwise integer division occurs
    due to 'n' and 'k' being integers.

    Tip: It's better to use (n-1)/k instead.
    -----------------------------------------------
    */
    
    for (i = ceil ((n-1)*1.0/k) - 1; i>=0; i--)
        createHeap(i,n,k); //also known as heapify
}

//creates a heap from an array of elements
void createHeap(int i, int size,int k)
{
    //'k' children represented by an array of length 'k'
    int *child = (int *) calloc(k,sizeof(int));
    int j;
    for(j=0;j<k;j++)
        child[j]=k*i+j+1; //formula for 'i' node's 'j'-th child
    int smallest = i; //assuming the smallest (or largest) node to be i-th node

    //Comparisons to find the smallest (or largest) value among 'j' and its children
    for(j=0;j<k;j++)
        if (comp(heap_type))
            smallest = child[j];
    
    //if it is found that root isn't the smallest
    //or the largest (depends on minheap or maxheap)
    if (smallest != i)
    {
        swap(smallest,i); //swap smallest-th (or largest-th) and i-th position elements
        createHeap(smallest,size,k); 
     /* recursive call to check and solve for possible inequilibrium
        in heap, caused due to swapping of the elements */
    }
}

//swaps x-th and y-th position elements in array
void swap(int x,int y)
{
    int t = heap[x];
    heap[x]=heap[y];
    heap[y]=t;
}

//performs heapsort
void heapSort(int size,int k)
{
 	int i;
 	int n = size;
 	for(i=size-1;i>=0;i--)
 	{
        //the smallest element in current heap 
        //[0...n] swapped with i-th element
 		swap(0,i);
 		n--; //n decremented
 		createHeap(0,n,k); //call to heapify the reduced heap
 	} 	 	
}

//to accept array elements
void input(int x)
{
    int i;
    printf("Enter %d elements :\n",x);
    for (i=0;i<x;i++)
        scanf("%d",&heap[i]);
    printf("\nHeap initialized with the entered elements.\n");
}

//To display heap 
void display(int x,int rev)
{
    int i;
    if (heap_type=='i')
        printf("\nThe Min Heap :\n");
    else
        printf("\nThe Max Heap :\n");
    if (rev==1)
    {
        for (i=x-1;i>=0;i--)
            printf("%d\t",heap[i]);
    }
    else
    {
        for (i=0;i<x;i++)
        printf("%d\t",heap[i]);
    }
    printf("\n.........................\n\n");
}