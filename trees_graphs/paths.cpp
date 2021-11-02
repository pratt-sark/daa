//C++ Program (use g++ for compilation)
//Pratyay Sarkar (BSc. Semester IV)
//Find all paths from one node to another in a connected, undirected and weighted graph
//Program: 17

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

//______Functions List_____
int ** allocatemem(int n);
void display();
int ifConnected();
void dfs(int i);
int allVisited();
int genRandom(int range);
void Find_All_Paths(int Origin, int Destination);
void display_path(vector<int> path);

//____Global Variables List___
int **Adj; //adjacency matrix
int n; //number of vertices
int max_edges; //maximum number of edges possible for an undirected graph
int origin, dest; //origin node and destination node defining the edge
int *Visited; //indicates which vertices are visited
int k; //path counter
vector<int> path; //stores path
bool* inStack; //boolean array 

//Execution starts here
int main()
{
    cout<<"\n\nThis program accepts a Connected, Undirected, Unweighted Graph from user";
    cout<<"\nand displays all paths from a particular node to another.\n\n"; 

    step:
        printf("\nEnter number of nodes:\n");
        scanf("%d",&n);
        if (n<=0)
        {
            cout<<"\nInvalid input for number of nodes. Re-enter Values.\n";
            goto step;
        }

    //necessary to flush standard input stream,as unexpected problems 
    //occur while accepting a character after an integer
    fflush(stdin); 
    
    max_edges = (n*(n-1)/2); //maximum number of edges possible for an undirected graph
    
    //memory allocated for adjacency matrix
    Adj = allocatemem(n);
    //memory allocated for Visited[] array 
    Visited=(int *)calloc(n,sizeof(int));
    //memory allocated for boolean array inStack
    inStack = new bool[n];
    for(int ii=0;ii<n;ii++)
        inStack[ii]=false; //all elements initialized to false

    int i; //control variable of loop
    char ch; //choice of user
    cout<<"\nGraph initialised and ready for input.\nNote: Vertix numbers will range from 0 to %d for %d total nodes.\n",n-1,n;
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
        cout<<"\nDo you want to continue adding edges? [enter y or Y if yes, and any other character if no]\n";
        ch = getchar(); //stores decision whether to continue adding edges

        if (ch!='y' && ch!='Y') //if the user decides against adding more edges
            break;
    }

    //if the graph is not connected, we can't find paths from
    //each node to another node, hence this checking is absolutely necessary
    if (!ifConnected())
    {
        cout<<"\n\nThe entered graph is not connected.\nRe-run the program and enter a connected graph.\n\n";
        exit(1);
    }

    //displaying the Adjacency Matrix
    cout<<"\n\nThe Adjacency Matrix representing the graph:\n\n";
    display(); 

    k=0; //path counter initialised to zero
    int src,dest; //source and destination nodes
    cout<<"\nEnter Source node and Destination node (Eg: '0 3') ...\n";
    cin>>src>>dest; //user inputs src and dest
    cout<<"\n\nAll possible paths from "<<src<<" to "<<dest<<" are:\n";
    Find_All_Paths(src, dest); //function call to find paths
    //to clearly seperate last path output from terminal prompt (after execution stops) 
    cout<<"\n"; 
    return 0;
}

//Checks if a graph is connected
//returns 1 for Connected Graph, else 0
int ifConnected()
{
    //calling the dfs(int) with that random node number
    dfs(genRandom(n));
    return allVisited();
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
void dfs(int src)
{
    if(allVisited()) //if all vertices are visited
        return;
    Visited[src]=1; //node 'src' entered in Traversal[] is marked visited   
    for(int i=0;i<n;i++) //loop to traverse all nodes in row of 'src'
    {
        //if node 'i' is not visited yet, and has an edge with node 'src'
        if(!Visited[i] && Adj[src][i])
            dfs(i); //recursive call to dfs(int) with 'j' as the parameter
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

//Finds all paths from node 'src' to node 'dest' and displays it
void Find_All_Paths(int src, int dest)
{
    inStack[src] = true; //source marked visited
    path.push_back(src); //source pushed at the end of vector

    if (src == dest) //if destination is found
    {
        k++; //increment path number by one
        display_path(path); //display the path
        path.pop_back(); //remove the last element of vector
        inStack[dest] = false; //mark the destination as NOT in vector
        return;
    }

    for (int i=0; i<n; i++) //if destination is not yet reached
        if (Adj[src][i] && !inStack[i])
            Find_All_Paths(i, dest); //find path from an adjacent unvisited node to dest
    path.pop_back(); //remove the last element of vector
    inStack[src] = false; //mark the source as NOT in vector
}

//Displays the vector, which contains a path
void display_path(vector<int> path)
{
    int i;
    cout<<"\nPath Number "<<k<<":\t";
    for(i=0;i<path.size()-1;i++)
        cout<<path[i]<<"-->";
    cout<<path[i];
    cout<<endl;
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