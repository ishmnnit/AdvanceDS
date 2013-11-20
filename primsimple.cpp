#include<iostream>
#include<stack>
#include<list>
#include "prim.h"
#ifndef HEADER_FILE_H //use a name that is unique though!!
#define HEADER_FILE_H
#include "graph.h"
#endif
#define INT_MAX 6866886
using namespace std;


/* prim simple scheme take the graph node g and insert all the element 
   in an array ( Vector is used for this purpose ,which behave as a Dynamic
   array ) .To find out Minimum element we search all the node in the array
   and find out elment so it has complexity o(n) . Also for all the edege
   for given vertex , we are also updating its key value */

int primsimple(graph g,bool filemode)
  {

     /* Make a Boolean array and mark all the node of the graph  as false
         which indicate that none of node of the graph is visted yet */
     if(filemode)
        cout<<"PrimSimple Scheme\n";

     bool vis[g.V];
     for(int i=0;i<g.V;i++)
         vis[i]=false;

     /* Push all the vertex node in the vector(Dynamic Array) 
        (In fibonacci Heap scheme we put all the element in the 
         Fibonacci heap) */
     
     int cost=0;
     vector<gnode> v;
     for(vector<gnode>::iterator i=g.vertex.begin();i!=g.vertex.end();i++)
       {
         v.push_back(*i);
       }

     /* Assume that out source is vertex with vertexid=0 , It does not matter 
        we can select any source . By Default it is implemanted as Zero */
     int source=0;

     /* Make Key of this node Zero ,So our remove_min algorithm First pick the 
        source element */

     v[source].key=0;
     int cnt=g.V;  /* This variable has the count number of node Not visited yet */
     int min; /* It store the index of the key whose value is minimum */
     int minval=INT_MAX; /*It stores the minimum key value seen so far */

     vector<mstedege> mst; 
 
     if(filemode)
        cout<<"####  Minimum Spanning Tree ####\n";  

     while(cnt) /* Run the while loop till all the node of the graph is visited */
     {
       /* Find Out Minimum element in the Vector i.e whose key is smallest */
       minval=INT_MAX;
       min=remove__min(v,vis,minval);
       minval=v[min].key;
       cost=cost+minval;

       /* Node with Vertexid min is next node which is included in mst, so set the flag 
          for it as a true */ 
       vis[min]=true;
       cnt--; // Decrease the count of number of node visited 

       if(filemode && cnt+1!=g.V)
        { 
           mstedege m;
           m.x=v[min].parent;
           m.y=min;
           mst.push_back(m);
        }
         // cout<<v[min].parent<<"----"<<min<<"----"<<v[min].key<<"\n";
      /* In the Adjecency List travese all the node and update parent to Min and key to weight
         if that node is not visted yet */

      list<gnode>::iterator j;
      for(j=g.adj[min].begin();j!=g.adj[min].end();j++)
      {
          if(vis[j->vertexid]==false && v[j->vertexid].key > j->weight)
            {  
               v=decrease_key(v,j,min);
            }//End if
      }//End For

     }//End While
     if(filemode)
     {  
        cout<<cost<<"\n";    
        printmst(mst);
      /*  vector<mstedege>::iterator i;
        for(i=mst.begin();i!=mst.end();i++)
         {
           cout<<i->x<<" "<<i->y<<"\n";
          
         
         }
       */
      }
       
      return cost;
  }//End Function

 int remove__min(vector<gnode> v,bool vis[],int minval)
{
   int min;
   for(int i=0;i!=v.size();i++)
       {
           if(v[i].key < minval && vis[i]==false)
             {
               minval=v[i].key;
               min=i;
              }
       }
  return min;
}


void printmst(vector<mstedege> mst)
{
       vector<mstedege>::iterator i;
        for(i=mst.begin();i!=mst.end();i++)
         {
           cout<<i->x<<" "<<i->y<<"\n";

         }

}


bool is_dkey_req(vector<gnode> v,bool vis[],list<gnode>::iterator j)
{
   if (vis[j->vertexid]==false && v[j->vertexid].key > j->weight)
        return true;
   return false;

}

 vector<gnode> decrease_key(vector<gnode> v,list<gnode>::iterator j,int min)
     {
               v[j->vertexid].parent=min;
               v[j->vertexid].key=j->weight;
               return v;
      }
