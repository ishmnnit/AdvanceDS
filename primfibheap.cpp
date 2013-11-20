#include<map>
#ifndef HEADER_FILE_H //use a name that is unique though!!
#define HEADER_FILE_H
#include "graph.h"
#endif
#include "prim.h"
#ifndef HEADER_FILE_H2 //use a name that is unique though!!
#define HEADER_FILE_H2
#include "fibheap.h"
#endif
#define INT_MAX 9999999

    /* prim fibonacci heap schem take the graph node g and insert all the element in 
       a Fibonacci heap. Finiding out Minimum has amortized complexity o(logn) while
       Decrease key have a  amortized complexity O(1) */


int primfibheap(graph g,bool filemode)
  {
     
     int cost=0;
     /* Make a Boolean array and mark all the node of the graph  as false
         which indicate that none of node of the graph is visted yet */
     bool vis[g.V];
     for(int i=0;i<g.V;i++)
         vis[i]=false;

     /* Push all the vertex node in a Fibonacci heap .Pushing all element
         without deleting any other element means we are just adding element
         in a circular doubly link list. Root node always point to Minimum 
         node in the Fibonacci heap */

     MinFibheap f;
     vector<gnode>::iterator i=g.vertex.begin();

      /* Make Key of this node Zero ,So our remove_min algorithm First pick the 
        source element */
     MinFibnode* fnode=f.make_fibnode(0,INT_MAX,0);

     f.insert(fnode);
     /* Insert the Node in a Map, we maintain this map beacause at any time we 
        want Node address to give it into the decrease key, if we don't give 
        it to the Map we need to search it in whole Fibonacci Heap structure 
        which will result in increase the complexity */

      map<int,MinFibnode*> MinFibmap;
      MinFibmap[0]=fnode;
      i++;
      int k=1;
      while(i!=g.vertex.end())
       {
         MinFibnode* tnode=f.make_fibnode(i->key,i->weight,k);
         MinFibmap[k]=tnode;
         f.insert(tnode);
         i++;
         k++;
       }
       
     int cnt=g.V;  /* This variable has the count number of node Not visited yet */
     int min; /* It store the index of the key whose value is minimum */
     vector<mstedege> mst;

     //cout<< "\n ###### Minimum Spanning Tree with Fibonacci Heap Scheme ####### \n";
     while(cnt) /* Run the while loop till all the node of the graph is visited */
     {
       /* Find Out Minimum element in the Vector i.e whose key is smallest */
          MinFibnode *z;
          z=f.remove_min();
          min=z->fvertexid;
          cost=cost+z->data;
       /* Node with Vertexid min is next node which is included in mst, so set the flag 
          for it as a true */ 
       vis[min]=true;
       cnt--; // Decrease the count of number of node visited
        
       if(filemode && cnt+1 != g.V)
        {
           mstedege m;
           m.x=g.vertex[z->fvertexid].parent;
           m.y=z->fvertexid;
           mst.push_back(m);
        }

      list<gnode>::iterator j;
      for(j=g.adj[min].begin();j!=g.adj[min].end();j++)
      {
            MinFibnode* x=MinFibmap[j->vertexid];
            if(vis[j->vertexid]==false && x->data > j->weight )
            {  
                g.vertex[j->vertexid].parent=min;
               
               /* Now We should decrease the key Value in Minimum Fibonacci Heap 
                  which is O(1) in Fibonacci Heap , If we use any normal heap decrease 
                  Key will take O(logn) time .We need to pass the pointer of the node
                  whose value we want to decrease ,New value would be j->weight*/
                f.decrease_key( MinFibmap[j->vertexid],j->weight);
            }//End if
      }//End For

     }//End While
     if(filemode)
     {
        cout<<cost<<"\n";
        vector<mstedege>::iterator i;
        for(i=mst.begin();i!=mst.end();i++)
         {
           cout<<i->x<<" "<<i->y<<"\n";

         }
      }

     return cost;
  }//End Function

