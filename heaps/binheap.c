//Pratyay Sarkar (BSc. Semester IV)
//Implementation of heap and heapsort (binary tree)
//Program: 24

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//macro to define the suitable swapping criteria according
//to user choosing either minheap or maxheap
#define compLeft(heap_type) (heap_type=='i')?(left<size && heap[left]<heap[smallest]):(left<size && heap[left]>heap[smallest])
#define compRight(heap_type) (heap_type=='i')?(right<size && heap[right]<heap[smallest]):(right<size && heap[right]>heap[smallest])

int* heap; //globally declared heap
char heap_type; //type of heap

void input(int x);
void display(int x,int rev);
int leftt(int i);
int rightt(int i);
void swap(int x,int y);
void createHeap(int i,int size);
void buildHeap(int n);
void heapSort(int size);

//execution starts here
void main()
{
    int n,ch;
    // n - size of array 'heap'
    // ch - choice of user

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
    buildHeap(n);
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
    heapSort(n); //call to heapsort (int) 
    display(n,rev); //display heap after sorting
}

//Building the heap
void buildHeap(int n)
{
    int i;
    /**
    ------Creation of heap-------------
    Note 1: Index starting from floor(n/2) - 1 means 
    unnecessary checkings for leaf nodes are avoided.
    
    Note 2: In C, n/2 == floor(n/2), if n is an integer.
    For simplicity, n/2 is used here. 
    -----------------------------------
    */
    
    for (i = n/2 - 1; i>=0; i--)
        createHeap(i,n);
}

//Commmonly referred to as heapify
//Creates a heap from an array of elements
void createHeap(int i, int size)
{
    int left = leftt(i); //position of left child of i-th element
    int right = rightt(i); //position of right child of i-th element
    int smallest = i; //assuming the smallest (or largest) node to be i-th node

    //if the left child of i-th element is smaller than smallest
    //or larger than the largest (depends on minheap or maxheap)
    if (compLeft(heap_type))
        smallest = left;
    
    //if the right child of i-th element is smaller than smallest
    //or larger than the largest (depends on minheap or maxheap)
    if (compRight(heap_type))
        smallest = right;
    
    //if it is found that root isn't the smallest (or largest,depends on minheap or maxheap)
    if (smallest != i)
    {
        swap(smallest,i); //swap smallest-th (or largest-th) and i-th position elements
        createHeap(smallest,size); 
     /* recursive call to check and solve for possible inequilibrium
        in heap, caused due to swapping of the elements */
    }
}

//performs heapsort
void heapSort(int size)
{
 	int i;
 	int n = size;
 	for(i=size-1;i>=0;i--)
 	{
        //the smallest element in current heap 
        //[0...n] swapped with i-th element
 		swap(0,i); 
 		n--; //n decremented
 		createHeap(0,n); //call to heapify the reduced heap
 	} 	 	
}

//To find the left child of i-th element
int leftt(int i)
{
    return 2*i+1;
}

//To find the right child of i-th element
int rightt(int i)
{
    return 2*i+2;
}

//Swaps x-th and y-th position elements in heap
void swap(int x,int y)
{
    int t = heap[x];
    heap[x]=heap[y];
    heap[y]=t;
}

//To accept elements
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