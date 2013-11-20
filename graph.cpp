#include<iostream>
#include<list>
#include<algorithm>
#include<queue>
#include<utility>
#include<set>
#include<bitset>
#include<fstream>
#include<cstdlib>
#define INT_MAX 55555
#ifndef HEADER_FILE_H //use a name that is unique though!!
#define HEADER_FILE_H
#include "graph.h"
#endif 
using namespace std;

 
/*  Following constructor is used for random mode of the graph 
      Edges are created with Random Number genrator 
      command line is :: mst -r n d
      run in random connected graph with n vertices and d% dessity */
 
 graph::graph(int V,int d)
 {
   this->V=V;
   adj=new list<gnode> [V];

 for(int i=0;i<V;i++)
   {
     gnode g;
     g.key=INT_MAX;  /* For Prim Algorithm Intially we assume Key value infinte ,
                        we subsequently update this value */
     g.weight=0;
     g.vertexid=i;
     g.parent=-1;
     this->vertex.push_back(g);
   }
     /*Create Graph with randomly generated edeges */
     graphrandommode(d);
   
 }

 /* This function genrate the graph in random mode */

 void graph::graphrandommode(int density)
  {
    /* If V is total No of Vertices , maximum possible Node is V*(V-1)/2 */
     int maxnode= V*(V-1)/2;
    
    /* Number of Edges in our graph */
     int noedges=(density*maxnode)/100; 
     int i=0;
     srand(1378948858U);
     cout<<"#######Graph########\n";
     bitset<5001*5001> b;
     while(i< noedges)
     {
        int vertex1=rand()%V;
        int vertex2=rand()%V;
        int weight=rand()%1000+1;

        /* if there is already an edege in the graph don't add that vertices 
          Self looped is not allowed ,so don't add any such vertices */
      
        int a=vertex1*5000+vertex2;
        int c=vertex2*5000+vertex1;
  
        bool is_in = b.test(a) || b.test(c);
        if(is_in || vertex1==vertex2)
          continue;
         
        b.set(a);
        b.set(c);

        /*Create a new Edege with above value and add in the Graph */
        gnode g;
        g.vertexid=vertex2;
        g.weight=weight;
        g.key=INT_MAX;
        g.parent=-1;
        add_edge(vertex1,g);
        i++;
     }
}

 /* Add Node in the adjecency list of Node of vertex id x */ 

 graph::graph(string filename)
 {  
   string line;
   ifstream f;
   f.open(filename.c_str());
   int nline=0;
   while(getline(f,line))
   {
      nline++;
      int i=0,k=0,f=0;
      int n=line.length();
      char str[n];
      int vertex1,vertex2,weight;

      while(i<line.length())
      {
          if(line.c_str()[i] ==' ')
          {
             str[k]='\0';
             k=0;
             switch (f){
             case 0:
             vertex1=atoi(str);
             f++;
             break;
             case 1:
             vertex2=atoi(str);
             f++;
             break;
            } // End Switch
             
          }// End if
         else
         {
            str[k]=line[i];
            k++;
         }// End elese
         i++;
     }// End while
       str[k]='\0';
       int x=atoi(str);
       if(nline==1)
       {
          this->V=vertex1;
          adj=new list<gnode> [vertex1];
          for(int s=0;s<vertex1;s++)
          {
              gnode g;
              g.key=INT_MAX;  /* For Prim Algorithm Intially we assume Key value infinte ,
                        we subsequently update this value */
              g.weight=0;
              g.vertexid=s;
              g.parent=-1;
              this->vertex.push_back(g);
         }

       }// End if
       else
       {
           gnode g;
           g.vertexid=vertex2;
           g.weight=x;
           g.key=INT_MAX;
           g.parent=-1;
           add_edge(vertex1,g);
       }// End else
    }// End While
    f.close();
  
 }


/* Add a new Edege in the Graph */
 void graph::add_edge(int x,gnode node1)
 {
   int y=node1.vertexid;
   gnode node2;
   node2.weight=node1.weight;
   node2.vertexid=x;
// Undirected Graph,So for two vertices we need to Add in both ways
   adj[x].push_back(node1);
   adj[y].push_back(node2);
 }


 /* Following function is a Simple DFS function and it return Number of 
    connected node start from vertex ver and if this Number is less than
    total Number of vertex it Means our graph is not connected */

  int graph::DFSutil(graph g,bool visited[],int source)
  {
   static int cnt=0;
   visited[source]=true;
   cnt=cnt+1;
   list<gnode>::iterator i;
   for(i=g.adj[source].begin();i!=g.adj[source].end();i++)
      {
          if(visited[i->vertexid]==false)
            DFSutil(g,visited,i->vertexid); 
      }
   return cnt;
  }

 
 /* Follwing  function check whether graph in connected
    it do DFS to verify whether graph is conected or not */

 bool graph::isconnected(graph g)
 {
   bool *visited=new bool[g.V];

   for(int i=0;i<g.V;i++)
      visited[i]=false;

   int nodevisited=DFSutil(g,visited,0);

    /* If total Number of node visited is less than total Number of vertex in this graph
       this means our graph is not connected */
    if(nodevisited!=g.V)
       return false;
     return true;
 }
