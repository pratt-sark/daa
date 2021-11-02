//C Program (use gcc for compilation)
//Pratyay Sarkar (BSc. Semester IV)
//Spanning Tree from Depth First Traversal of a connected, undirected, unweighted graph
//Program: 13

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Structure which represents an edge of an undirected Graph
struct edge
{
    int src; //edge source
    int dest; //edge destination
};

//____Structures List___
typedef struct edge edge;

//______Functions List_____
int ** allocatemem(int n);
void display();
void display1D();
int ifConnected();
void dfs(int i);
int allVisited();
void displaySpanningTree();

//____Global Variables List___
int **Adj; //adjacency matrix
int n; //number of vertices
int max_edges; //maximum number of edges possible for an undirected graph
int origin, dest; //origin node and destination node defining the edge
int *Visited; //indicates which vertices are visited
int *Traversal; //stores depth first traversal of the graph
int k; //indicates the index counter for Traversal array
edge* edges; //edges of the spanning tree
int edge_counter; //indicates the index counter for edges array

//Execution starts here
void main()
{
    printf("\n\nThis program accepts a Connected, Undirected, Unweighted Graph from user");
    printf("\nand displays a spanning tree using Depth First Traversal.\n\n"); 
    
    step:
        printf("\nEnter number of nodes:\n");
        scanf("%d",&n);
        if (n<=0)
        {
            printf("\nInvalid input for number of nodes. Re-enter Values.\n");
            goto step;
        }

    //necessary to flush standard input stream,as unexpected problems 
    //occur while accepting a character after an integer
    fflush(stdin); 
    
    max_edges = (n*(n-1)/2); //maximum number of edges possible for an undirected graph
    edges = (edge *)calloc(max_edges,sizeof(edge));
    
    //memory allocated for adjacency matrix
    Adj = allocatemem(n);
    //memory allocated for Visited[] array 
    Visited=(int *)calloc(n,sizeof(int));
    //memory allocated for Traversal[] array
    Traversal=(int *)calloc(n,sizeof(int)); 

    int i; 
    char ch;
    printf("\nGraph initialised and ready for input.\nNote: Vertix numbers will range from 0 to %d for %d total nodes.\n",n-1,n);
    for (i=1;i<=max_edges;i++)
    {
        inputedge:
        printf("\nEnter edge [enter '1 3' if there is an edge from Vertix 1 to Vertix 3]:\n");
        scanf("%d %d",&origin,&dest);

        if (origin>=n || dest>=n || origin<0 || dest<0) //checking validity of edges
        {
            printf("\nInvalid Edge.\n");
            goto inputedge;
        }
        else //adjacency matrix modified to represent edges
        {
            Adj[origin][dest] = 1;
            Adj[dest][origin] = 1;
        }

        if(i==max_edges) 
		{
			printf("\nMaximum possible edges entered. Displaying output.....\n");
			break; //if all possible edges are already entered,
			//there is no need to ask the question about adding more edges
		}
        
        fflush(stdin); //required when a character input follows one/many integer input(s)
        printf("\nDo you want to continue adding edges? [enter y or Y if yes, and any other character if no]\n");
        ch = getchar(); //stores decision whether to continue adding edges

        if (ch!='y' && ch!='Y') //if the user decides against adding more edges
            break;
    }

    //if the graph is not connected, we can't find Spanning Tree
    // hence this checking is absolutely necessary
    if (!ifConnected())
    {
        printf("\n\nThe entered graph is not connected.\nRe-run the program and enter a connected graph.\n\n");
        exit(1);
    }

    //displaying the Adjacency Matrix
    printf("\n\nThe Adjacency Matrix representing the graph:\n\n");
    display(Adj,n);
    
    //displaying the Depth First Traversal
    printf("\n\nThe Depth First Traversal of the graph :\n\n");
    display1D();    

    //displaying the spanning tree
    displaySpanningTree();
}


//Checks if a graph is connected
//returns 1 for Connected Graph, else 0
int ifConnected()
{
    //Setting the seed for rand() to generate random numbers
    srand(time(NULL));

    //initializing k and edge_counter to zero
    k=0; edge_counter=0;
    //generating a random node number to start DFS from
    int ran=rand()%n;
    //calling the dfs(int) with that random node number
    dfs(ran);
    return allVisited();
}

//Finds Depth First Traversal of the graph, starting
//at node 'src'and stores it in an array 'Traversal[]'
void dfs(int src)
{
    if(allVisited()) //if all vertices are visited
        return;
    Traversal[k++]=src; //node inserted in Traversal[] array
    Visited[src]=1; //node 'src' entered in Traversal[] is marked visited
    
    for(int i=0;i<n;i++) //loop to traverse all nodes in row of 'src'
    {
        //if node 'i' is not visited yet, and has an edge with node 'src'
        if(!Visited[i] && Adj[src][i])
        {
            //printf("\n%d--%d",src,i); //for debugging
            //Defining the edge with values 'src' and 'i'
            edges[edge_counter].src = src;
            edges[edge_counter].dest = i;
            edge_counter++;
            dfs(i); //recursive call to dfs(int) with 'j' as the parameter
        }
    }
}

//Checks if all nodes of the graph are visited
//returns 1 if all nodes are visited, else 0
int allVisited()
{
    int i;
    for (i=0;i<n;i++)
    {
        if (Visited[i]==0)
            break;
    }
    return !(i<n);
}

//For memory allocation
int ** allocatemem(int no_of_nodes)
{
    int i;
    int **X = (int **)calloc(no_of_nodes,sizeof(int *));
    for (i=0;i<no_of_nodes;i++)
        X[i]=(int *)calloc(no_of_nodes,sizeof(int));
    return X;
}

//To display Adjacency Matrix of order n
void display()
{
	int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
		printf("%d\t",Adj[i][j]);
		printf("\n");
	}
}

//To display Depth First Traversal of the graph
void display1D()
{
	int j;
		for (j=0;j<n;j++)
		    printf("%d\t",Traversal[j]);
		printf("\n");
    printf("\n");
}

//To display the spanning tree
void displaySpanningTree()
{
    int i;
    printf("\n\nThe Spanning Tree:\n");
    for (i=0;i<edge_counter;i++)
        printf("%d---%d\n",edges[i].src,edges[i].dest);
}