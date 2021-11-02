//Pratyay Sarkar (BSc. Semester IV)
//Binary Search Tree operations (insert,deletion,search)
//Program: 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Structure to represent a Binary Search Tree (BST)
struct node
{
 	char* data;
 	struct node * left;
 	struct node * right;
};

//____Global Variables List___
int n; //number of nodes currently in BST
bool found; //indicates whether item is present

//____Structures List___
typedef struct node node;

//______Functions List_____
bool isNum(char *x);
node* insert (node * temp, char* x);
int search (node * temp, char* x);
void inorder (node * temp);
void preorder (node * temp);
void postorder (node * temp);
node* del(node* root, char* x);
node* min(node* node);

//Execution starts here
int main()
{
	//Initialize stuff
    node* root=NULL;
	int ch;
	while(true)
	{
		printf("\n\n\n----------BINARY SEARCH TREE--------\n");
		printf("\n0. Exit program\n1. Insert\n2. Search\n3. Preorder Traversal\n4. Inorder Traversal (aka Ascending Order display)");
		printf("\n5. Postorder Traversal\n6. Delete a node\n");
        printf("\nCurrent number of nodes in BST : %d",n);
		printf("\n\nYour choice : \n");
		scanf("%d",&ch);

		//memory allocated for the data item 
		char *x = (char *)( calloc(20,sizeof(char)) );
		switch(ch)
		{
			case 0: printf("\nProgram terminated.\n");
					exit(0);
					break;

			case 1: printf("\nEnter data item : \n");
					scanf("%s",x);

					//call to insert function
					root=insert(root,x);
					break;

			case 2: printf("\nEnter a data item to be searched : \n");
					scanf("%s",x);
					if(search(root,x)>0) 
						printf("%s is FOUND\n",x);
					else
						printf("%s is NOT FOUND\n",x);
					break;

			case 3: printf("\nPreorder Traversal : \n");
					preorder(root);
					break;
			case 4: printf("\nInorder (Ascending Order) Traversal : \n");
					inorder(root);
					break;
			case 5: printf("\nPostorder Traversal : \n");
					postorder(root);
					break;

			case 6: printf("Enter the data item to be deleted : \n");
					scanf("%s",x);
					n--; //decreasing number of nodes
                    found = false;
					root = del(root,x); //call to delete function
                    
                    if (found==true)
                        printf("Element deleted.");
                    else
                        printf("Element not present in tree.");
					break;
			default: printf("\nInvalid Choice.\n");
		}
	}
    return 0;
}

//Checks if a string is made only of numbers (a leading + or - allowed)
bool isNum(char *x)
{
	int i;
	i = (x[0]=='-' || x[0]=='+')?1:0;
	while(x[i]!='\0')
	{
		if (x[i]<'0' || x[i]>'9')
			break;
		i++;
	}
	return (x[i]=='\0');
}

/**-------Parameters----------	
root - root node of BST	
x    - data value of new node to be inserted 
*/
//Function to insert a new node to the BST
node *insert (node * root, char* x)
{
	if (root==NULL) 
	{
        node * N = (node *)calloc(1,sizeof(node));
		N->data = x;
		n++;
		return N;
	}

	//if x is purely a number and data of current node is alphanumeric
	else if ( isNum(x) && !(isNum(root->data)) )
		root->left=insert(root->left,x);
	
	//if x is alphanumeric and data of current node is purely a number
	else if ( !(isNum(x)) && isNum(root->data) )
		root->right=insert(root->right,x);

	//if both are numeric
	else if ( isNum(x) && isNum(root->data) )
	{
		if (atoi(x)<atoi(root->data))
		    root->left=insert(root->left,x);
		else
		    root->right=insert(root->right,x);
	}

	else //if both are alphanumeric
	{
		if (strcmp(x,root->data)<0)
		    root->left=insert(root->left,x);
		else
		    root->right=insert(root->right,x);
	}    
}

/**-------Parameters----------	
temp - root node of BST	
x    - data value to be searched 
*/
//Function to search for a data value in the BST
int search (node *temp, char* x)
{
	if (temp==NULL) 
	{
		if (n==0)
		    printf("\nEMPTY TREE\n");
		return 0;
	}

	//element found
	else if (strcmp(x,temp->data)==0)
		return 1;

	//if x is purely a number and data of current node is alphanumeric
	else if ( isNum(x) && !(isNum(temp->data)) )
		search(temp->left,x);
	
	//if x is alphanumeric and data of current node is purely a number
	else if ( !(isNum(x)) && isNum(temp->data) )
		search(temp->right,x);
	
	//if both are numeric
	else if ( isNum(x) && isNum(temp->data) )
	{
		if (atoi(x)<atoi(temp->data))
		    search(temp->left,x);
		else
		    search(temp->right,x);
	}

	//if both are alphanumeric    
	else
    {
        if (strcmp(x,temp->data)<0)
            search (temp->left,x);
        else
            search (temp->right,x);
    }
}

//Given a binary search tree and a key, this function 
//deletes the key and returns the new root
node* del(node* root, char* x)
{
    // base case
    if (root == NULL)
    {   
        /**Note:
		n is currently (-1) as we decremented n before calling the
		del(node*,int) function. Therefore, it is readjusted to 0.
		*/

		n++; //number of nodes re-adjusted to zero
        return root;
    }

    //element found
	else if (strcmp(x,root->data)==0)
	{
        found = true; //element found
        //node with only one child or no child
        if (root->left == NULL) 
        {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) 
        {
            node* temp = root->left;
            free(root);
            return temp;
        }
 
        //For node with two children:
        //get the inorder successor (smallest in the right subtree)
        node* temp = min(root->right);
 
        //Copy the inorder successor's content to this node
        root->data = temp->data;
 
        //Delete the inorder successor
        root->right = del(root->right, temp->data);
    }
    
    //if x is purely a number and data of current node is alphanumeric
	else if ( isNum(x) && !(isNum(root->data)) )
		root->left = del(root->left,x);
	
	//if x is alphanumeric and data of current node is purely a number
	else if ( !(isNum(x)) && isNum(root->data) )
		root->right = del(root->right,x);
	
	//if both are numeric
	else if ( isNum(x) && isNum(root->data) )
	{
		if (atoi(x)<atoi(root->data))
		    root->left = del(root->left,x);
		else
		    root->right = del(root->right,x);
	}

	//if both are alphanumeric    
	else
    {
        if (strcmp(x,root->data)<0)
            root->left = del(root->left,x);
        else
            root->right = del(root->right,x);
    }
 
    return root;
}

//Finds the minimum value in the tree rooted at node* x
node* min(node* x)
{
    node* curr = x;
 
    /* loop down to find the leftmost leaf */
    while (curr && curr->left != NULL)
        curr = curr->left;
 
    return curr;
}

/**-----Parameters------	
temp - root node of BST	
*/
//Function to display inorder traversal of the BST
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
temp - root node of BST	
*/
//Function to display preorder traversal of the BST
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
temp - root node of BST	
*/
//Function to display postorder traversal of the BST
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