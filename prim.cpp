#ifndef HEADER_FILE_H //use a name that is unique though!!
#define HEADER_FILE_H
#include "graph.h"
#endif

#ifndef HEADER_FILE_H2 //use a name that is unique though!!
#define HEADER_FILE_H2
#include "fibheap.h"
#endif

#include "prim.h"
#include<string>


/* Following is main prim fuction which take a graph node and option .
   Option have two value , Simple scheme and and Fibonacci Heap Scheme 
   Default mode for Prim function is Fibonacci heap scheme */


int prim(graph g,string option,bool filemode)
  {

     if(option == "Simple" || option == "simple" || option == "SIMPLE")
        { 
           /* prim simple scheme take the graph node g and insert all the element 
              in an array ( Vector is used for this purpose ,which behave as a Dynamic
              array ) .To find out Minimum element we search all the node in the array
              and find out elment so it has complexity o(n) . Also for all the edege
              for given vertex , we are also updating its key value */
           return (primsimple(g,filemode));
        }
      
     else
        {
           /* prim fibonacci heap schem take the graph node g and insert all the element in 
              a Fibonacci heap. Finiding out Minimum has amortized complexity o(logn) while
               Decrease key have a  amortized complexity O(1) */
           return (primfibheap(g,filemode));
        }

  }

