//Pratyay Sarkar (BSc. Semester IV)
//Binary Tree traversals
//Program: 9

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//Structure to represent a Binary Tree
struct node
{
 	char* data;
 	struct node * left;
 	struct node * right;
};

//____Global Variables List___
int n; //number of nodes currently in Binary Tree
int level; //indicates level number (starting from 0)
int k; //number of elements currently present in current level

//____Structures List___
typedef struct node node;

//______Functions List_____
node* insert (node * temp, char* x);
void inorder (node * temp);
void preorder (node * temp);
void postorder (node * temp);

//Execution starts here
int main()
{
	//Initialize stuff
    node* root=NULL;
	int ch;
	level=0;k=0; 

	while(true)
	{
		printf("\n\n----------BINARY TREE Traversals Only--------\n");
		printf("\n0. Exit program\n1. Insert\n2. Preorder Traversal\n3. Inorder Traversal\n4. Postorder Traversal");
        printf("\nCurrent number of nodes in Binary Tree : %d",n);
		printf("\nYour choice : \n");
		scanf("%d",&ch);

		//memory allocated for the data item 
		char *x = (char *)( calloc(20,sizeof(char)) );
		switch(ch)
		{
			case 0: printf("\nProgram terminated.\n");
					exit(0);
					break;

			case 1: printf("Enter data item : \n");
					scanf("%s",x);

					//call to insert function
					root=insert(root,x);
					break;

			case 2: printf("\nPreorder Traversal : \n");
					preorder(root);
					break;
			case 3: printf("\nInorder Traversal : \n");
					inorder(root);
					break;
			case 4: printf("\nPostorder Traversal : \n");
					postorder(root);
					break;

			default: printf("\nInvalid Choice.\n");
		}
	}
    return 0;
}

/**
-------Description----------	
Fills a Binary Tree in Level order.

First, in a level, left child of first node is filled, then right child of next node, and so on.
Then, in the same level, the right child of first node is filled, then left child of next node, and so on.

If the level is in its full capacity, level is incremented.

-------Parameters----------	
root - root node of Binary Tree	
x    - data value of new node to be inserted 
*/

//Function to insert a new node to a Binary Tree in level order 
//(only once a level is filled, insertion is allowed in next level)
node *insert (node * root, char* x)
{
    //if the root has no elements
	if (root==NULL) 
	{
        node * N = (node *)calloc(1,sizeof(node));
		N->data = x;
		n++; //number of elements in node
		k++; //(number of elements currently present in current level) incremented
		if (k==pow(2,level)) //checks if the level is filled
		{
			level++; //level incremented
			k=0; //current number of elements in a level reset to zero
		}
		return N;
	}
	else
	{
		//k being odd or even determines the subtree to recurse into
		if (k%2==1) 
			root->right = insert(root->right,x);
		else
			root->left = insert(root->left,x);
	}
	return root;
}

/**-----Parameters------	
temp - root node of Binary Tree	
*/
//Function to display inorder traversal of the Binary Tree
void inorder (node * temp)
{
	if (temp==NULL)
	{
		if (n==0)	
		 printf("\nEMPTY TREE\n");
		return;
	}
	else
	{
		inorder(temp->left);
		printf("%s ",temp->data);
		inorder(temp->right);
	}
}

/**-----Parameters------	
temp - root node of Binary Tree	
*/
//Function to display preorder traversal of the Binary Tree
void preorder (node * temp)
{
	if (temp==NULL)
	{
		if (n==0)	
		 printf("\nEMPTY TREE\n");
		return;
	}
	else
	{
		printf("%s ",temp->data);
		preorder(temp->left);	
		preorder(temp->right);
	}
}

/**-----Parameters------	
temp - root node of Binary Tree	
*/
//Function to display postorder traversal of the Binary Tree
void postorder (node * temp)
{
	if (temp==NULL)
	{
		if (n==0)	
		 printf("\nEMPTY TREE\n");
		return;
	}
	else
	{	
		postorder(temp->left);	
		postorder(temp->right);
		printf("%s ",temp->data);
	}
}