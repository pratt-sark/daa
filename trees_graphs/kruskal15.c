//C Program (use gcc for compilation)
//Pratyay Sarkar (BSc. Semester IV)
//MST (Kruskal's Algorithm) of a connected, undirected and weighted graph
//Program: 15

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Structure to represent a weighted edge in graph
struct Edge 
{
	//source, destination, weight
	int src, dest, weight;
};

//Structure to represent a connected, undirected and weighted graph
struct Graph 
{
	int V; // V-> Number of vertices
	int E; //E-> Number of edges
	//the graph is represented as an array of edges
	struct Edge* edge;
	int **Adj; //adjacency matrix
};

//A structure to represent a subset
struct subset 
{
	int parent; //parent of the subset
	int rank; //rank of the subtree
};

//____Structures List___
typedef struct Edge Edge;
typedef struct Graph Graph;
typedef struct subset subset;

//______Functions List_____
int ** allocatemem(int n);
struct Graph* createGraph(int V, int E);
int find(subset *subsets, int i);
void Union(subset *subsets, int x, int y);
int myComp(const void* a, const void* b);
void KruskalMST(Graph* graph);
void display(int **X,int n);
int ifConnected(int**A,int n);
void dfs(int src,int n,int **Adj,int *Visited);
int allVisited(int *Visited,int n);
int genRandom(int range);

//Execution starts here
int main()
{
	int V; //Number of vertices in graph
	printf("\n\nThis program accepts a Weighted, Connected Graph and finds a Minimum Spanning Tree.\n");
    step:
        printf("\nEnter number of nodes:\n");
        scanf("%d",&V);
        if (V<=0)
        {
            printf("\nInvalid input for number of nodes. Re-enter Values.\n");
            goto step;
        }
	int E = V*(V-1)/2; //Number of maximum permissible edges in graph

	Graph* graph = createGraph(V, E); //graph created and initialised
	printf("\nGraph initialised and ready for input.\nNote: Vertix numbers will range from 0 to %d.\n",V-1);

	int i=0,w,src,dest; 
    char ch;
    while (i<E) //test condition to ensure number of edges stay within maximum edge limit
    {
		inputedge:
        printf("\nEnter edge [Eg: enter '1 3' if there is an edge from Vertix 1 to Vertix 3]:\n");
        scanf("%d %d",&src,&dest);
		printf("\nEnter weight :\n");
		scanf("%d",&w);

		//if edge number exceeds permissible boundaries
        if (src>=V || dest>=V || src<0 || dest<0 ||w<=0) 
        {
			printf("\nInvalid Edge.\n");
			goto inputedge;
		}
		//if edge exists already
		else if(graph->Adj[src][dest]!=0 && graph->Adj[dest][src]!=0) 
			printf("\nYou already defined this edge with the same or different weight.\n");
        else
        {
			printf("\n***\n"); //for debugging

			//Modifying Adjacency matrix to reflect added edge
			graph->Adj[src][dest] = w;
            graph->Adj[dest][src] = w;

			//Adding edge to the array of edges
            graph->edge[i].src = src;
			graph->edge[i].dest = dest;
			graph->edge[i].weight = w;
			i++; //index for the array of edges
        }

		if(i==E) 
		{
			printf("\nMaximum possible edges entered. Displaying output.....\n");
			break; //if all possible edges are already entered,
			//there is no need to ask the question about adding more edges
		}

        fflush(stdin); 
		//necessary to flush standard input stream,as unexpected problems  
    	//occur while accepting a character after an integer

        printf("\nDo you want to continue adding edges? [enter y or Y if yes, and any other character if no]\n");
        ch = getchar(); //stores decision whether to continue adding edges

        if (ch!='y' && ch!='Y') //if the user decides against adding more edges
            break;
		fflush(stdin); 
    }

	graph->E=i; //no of edges = actual number of edges entered

	//if the graph is not connected, we can't find a spanning tree
    //hence this checking is absolutely necessary
	if (ifConnected(graph->Adj,V)==0)
    {
        printf("\nThe entered graph is not connected.\nRe-run the program and enter a connected graph.\n");
        exit(1);
    }
	
	//Adjacency Matrix displayed
	printf("\n______________________________________");
	printf("\n\nThe Adjacency Matrix : \n\n");
	display(graph->Adj,V);
	printf("\n______________________________________\n");

	KruskalMST(graph); //creates and displays MST and its cost

	return 0;
}


//The function to construct MST using Kruskal's algorithm
void KruskalMST(Graph* graph)
{
	int V = graph->V;
	Edge result[graph->E]; // This will store the resultant MST
	int e=0; // An index variable, used for result[]
	int i=0; // An index variable, used for sorted edges

	//Sort all the edges in increasing order of their weight. 
	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
	//edgesort(graph->edge, graph->E);

	//debugging section
	//printing sorted edges fpr verification of qsort
	printf("\nSorted Edges: ");
	for (int ii=0;ii<graph->E;ii++)
		printf("\n%d,%d\n",graph->edge[ii].src,graph->edge[ii].dest); 
	
	// Allocate memory for creating V subsets
	subset* subsets = (subset*)malloc(V *sizeof(subset));

	// Create V subsets with single elements
	for (int v=0; v < V; ++v) 
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}
	
	//Note: For a graph having V verices, each spanning tree has V-1 edges
	//Number of edges to be taken is equal to V-1	
	while (e < V-1 && i < graph->E) 
	{
		//Pick the smallest edge. And increment
		//the index for next iteration
		Edge next_edge = graph->edge[i++];

		int x = find(subsets, next_edge.src);
		int y = find(subsets, next_edge.dest);
		
		//If including this edge does't cause cycle, include it
		//in result and increment the index of result for next edge
		if (x != y) 
		{
			result[e++] = next_edge;
			Union(subsets, x, y);
		}
		//Else discard the next_edge
	}
	
	//Display the array result[] to display the MST
	printf("\n______________________________________\n");
	printf("\nFollowing are the edges in the constructed MST: \n");
	int minCost = 0;
	for (i=0; i<e; i++)
	{
		printf("%d -- %d ==> Weight : %d\n", result[i].src, result[i].dest, result[i].weight);
		minCost += result[i].weight;
	}
	printf("\nCost of the Minimum Spanning tree = %d\n\n",minCost);
	return;
}

//Function to find set of an element i
int find(subset *subsets, int i)
{
	// find root and make root as parent of i (path compression)
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent);

	return subsets[i].parent;
}

//Function that does union of two sets of x and y (Union by rank)
void Union(subset *subsets, int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	//Attach smaller rank tree under root of higher rank tree
	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;

	//If ranks are same, then make one as root and increment its rank by one
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

//Checks if a graph is connected
//returns 1 for Connected Graph, else 0
int ifConnected(int **A,int n)
{
	int *Visited = (int *)calloc(n,sizeof(int));
    //calling the dfs(int) with that random node number
    dfs(genRandom(n),n,A,Visited);
    return allVisited(Visited,n);
}

//Generates a random number in [0,range)
int genRandom(int range)
{
    //Setting the seed for rand() to generate random numbers
    srand(time(NULL));
    //generating a random node number to start DFS from
    return (int)(rand()%range);
}

//Performs Depth First Traversal of the graph, starting at node 'src'
void dfs(int src,int n,int **Adj,int *Visited)
{
    if(allVisited(Visited,n)) //if all vertices are visited
        return;
    Visited[src]=1; //node 'src' entered in Traversal[] is marked visited   
    for(int i=0;i<n;i++) //loop to traverse all nodes in row of 'src'
    {
        //if node 'i' is not visited yet, and has an edge with node 'src'
        if(!Visited[i] && Adj[src][i])
            dfs(i,n,Adj,Visited); //recursive call to dfs(int) with 'j' as the parameter
    }
}

//Checks if all nodes of the graph are visited
//returns 1 if all nodes are visited, else 0
int allVisited(int *Visited,int n)
{
    int i;
    for (i=0;i<n;i++)
    {
        if (Visited[i]==0)
            break;
    }
    return !(i<n);
}

//Compares two edges according to their weights.
//Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
	Edge* a1 = (Edge*)a;
	Edge* b1 = (Edge*)b;
	return (a1->weight) > (b1->weight);
}

//For memory allocation
int ** allocatemem(int n)
{
    int i;
    int **X = (int **)calloc(n,sizeof(int *));
    for (i=0;i<n;i++)
        X[i]=(int *)calloc(n,sizeof(int));
    return X;
}

//Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
	//memory allocated for graph
	Graph* graph = (Graph*)(malloc(sizeof(Graph)));
	graph->V = V;
	graph->E = E;

	//memory allocated for array of edges
	graph->edge = (Edge*)malloc(E*sizeof(Edge));
	//memory allocated for adjacency matrix
	graph->Adj = allocatemem(V); 
	return graph;
}

//Displays adjacency matrix.
void display(int **X,int n)
{
	int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
		printf("%d\t",X[i][j]);
		printf("\n");
	}
}