//Pratyay Sarkar (BSc. Semester IV)
//Implementation of Bucket Sort
//Program: 32

#include<stdio.h>
#include<stdlib.h>

//node to represent a singly linked list
struct node
{
  int data;
  struct node* next;  
};
typedef struct node node;

//___functions list____
void bucket_sort(int*,int);
int get_max(int*,int);
node *insert(node *head, int key);
void swap(int *a, int *b);
void displayBuckets(node* bucket);

int BUCKETS; //total number of buckets

//returns the maximum value from an array
int get_max(int* arr,int size)
{
    int max = arr[0];
    for(int i=0;i<size;i++)
        max = (arr[i] > max)? arr[i]:max;
    return max;
}

//insert an element in the list
node *insert(node *head, int key)
{
    node *temp=head;
    node *newnode=(node *)calloc(1,sizeof(node));
    newnode->data = key;
    if(head==NULL)
    {
        head=newnode;
        return head;
    }
    else
    {
        while(head->next!=NULL)
            head=head->next;
        head->next = newnode;
    }
    return temp;
}

//sorts a bucket
node* sort_bucket(node *bucket)
{
    node *head = bucket;
    for (node *i = head; i && i->next!=NULL; i = i->next)
    {
        for (node *j = i->next; j!=NULL; j = j->next)
        {
            if (i->data > j->data)
                swap(&i->data, &j->data);
        }
    }
    return head;
}

//swap two elements
void swap(int* a,int* b)
{
    int temp = *a;
    *a=*b;
    *b=temp;
}

//display a bucket
void displayBuckets(node* bucket)
{
    if(!bucket) return;
    while (bucket)
    {
        printf("%d\t",bucket->data);
        bucket = bucket->next;
    }
  
}

//Performs bucket sort on an array of n elements
void bucket_sort(int* arr,int n)
{
    //total number of buckets (each of range 5)
    BUCKETS = get_max(arr,n)/5 +1;
    //list of buckets
    node** buckets = (node **)calloc(BUCKETS,sizeof(node*));
    int i; //loop variable

    //elements put in respective buckets
    for(i=0;i<n;i++)
        buckets[arr[i]/5] = insert(buckets[arr[i]/5],arr[i]);
    
    //display original array
    printf("\nOriginal Array: \t");
    for(i=0;i<BUCKETS;i++)
        displayBuckets(buckets[i]);

    //sort the elements
    for(i=0;i<BUCKETS;i++)
        sort_bucket(buckets[i]);
    
    //display sorted elements
    printf("\n\nSorted Elements: \t");
    for(i=0;i<BUCKETS;i++)
        displayBuckets(buckets[i]);
}

//execution starts
void main()
{
    int n;
    //input elements
    printf("Enter number of inputs:");
    scanf("%d",&n);
    int* arr = (int*)calloc(n,sizeof(int));

    //elements accepted from user
    printf("Enter the elements:\n");
    for (int i=0; i<n; i++)
        scanf("%d",&arr[i]);

    //bucket sort function called
    bucket_sort(arr,n);  
}