#include<iostream>
#include<algorithm>
#include<list>
#include<vector>
using namespace std;

/* Graph Node Structure */

struct gnode
  {
    int vertexid;  // Store Vertex id of the Graph
    int weight;   // It store the weight between vertexid and and vertex whose adjecency list it is part of
    int key;     // Extra Variable which is used prim algorithm
    int parent;  // Store Vertex id of the parent Node 
  };


/*Graph Class structure */
 class graph
 {
   
   public:
   int V;   // V represent Number of vertices in the graph
   list<gnode> *adj;  // Adjecency List reprentaion of graph 
   vector<gnode> vertex;  // Store all the vertex in a vector 

   /* Following constructor is used for random mode of the graph 
      Edges are created with Random Number genrator 
      command line is :: mst -r n d
      run in random connected graph with n vertices and d% dessity */
   graph(int,int);
   /* Following constructor is used for user input mode,It create 
      graph from Input file 
      command line is ::
      a) Simple Scheme:: mst -s <
      b) f-heap Scheme:: mst -f <file-name> */
   graph(string);
   void graphrandommode(int);
   bool EdegeExists(int, int);
   void add_edge(int x,gnode node1);
   bool isconnected(graph);
   int  DFSutil(graph,bool visited[],int);
   void BFS(int);
 };

