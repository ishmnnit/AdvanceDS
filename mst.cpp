#include<iostream>
#include<cstdlib>
#include<stdlib.h>
#include<ctime>
#include<unistd.h>
#include<sys/time.h>
#include<algorithm>
#include "prim.h"
#ifndef HEADER_FILE_H //Include header file only once
#define HEADER_FILE_H
#include "graph.h"
#endif
using namespace std;



/* This function calculate the diference between  start and end time and return the value in 
   Milisecond */

 long mseconds_diff(timeval &start, timeval &end){
    long seconds, useconds, mseconds;
    seconds = end.tv_sec - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    mseconds = (seconds*1000 + useconds/1000.0)+0.5;
    return mseconds;
  }


int main(int argc,char* argv[])
{

    if(argc < 3 || argc > 5 )
     {
        cout<<"Invalid Argument,Please input mst -r n d for random mode\n";
        cout<<"Plase Inpust mst -s <filename> or mst -f <filename> for filemode\n";
     }
     
     bool filemode=false;

  /* If Number of argument is 4(mst -r n d) ,Implies user want to create graph
     with random scheme Where 3rd argument represent  Number of 
     vertices and 4th argument represents percentage density in graph 
     so call the constructor of the graph of the random mode*/


    string option(argv[1]);
    string fname(argv[2]);  
    int cost1,cost2;
    timeval a,b;

    if( argc == 4)
     {
        int vertices=atoi(argv[2]);
        int density=atoi(argv[3]); 
        if(density > 100)
        {
           cout<<"Invalid Argument, Density can not be greater than 100\n";
           return 0;
        }

        /* Create an object of the Graph in random mode, In grpah constructor pass Number
           of vertices and  Graph density */
       bool connected=false;
       while(connected!=true)
         {
            graph g(vertices,density);
            connected=g.isconnected(g);
             
             cout<<"Graph Created \n";
            if(connected)
              cout<<"Graph is connected\n";
            else
              continue;

            gettimeofday(&a,0);
            string s="simple";

            /* Call the Prim alorithm for Minimum spanning Tree for Simple Scheme */
            cost1=prim(g,s,filemode);
            cout<<"\n##Cost of Minimum Spanning Tree with simple scheme##=="<<cost1<<"\n";
            gettimeofday(&b,0);
            cout<<"###Total Time taken="<<mseconds_diff(a,b) <<"\n";
            
            gettimeofday(&a,0);
            /* Call the Prim Algorithm for Minimum spanning Tree for Fibonacci Heap scheme*/
            cost2=prim(g,"fheap",filemode);
            gettimeofday(&b,0);
            cout<<"\n##Cost of Minimum Spanning Tree with Fibonacci scheme##=="<<cost2<<"\n\n";
            cout<<"###Total Time taken="<<mseconds_diff(a,b) << "\n";
        }
    }
    else 
    {
       /* If Number of argument is 1 ,Implies user want to create graph
       with textfile */

       /*Call the constructor to create graph from Textfile */
       graph g(fname);
       filemode=true;
       cout<<"Graph Created \n";
       string s2="-s";

       /* If Option is = -s , call simple scheme of prim Algorithm */
      if(option==s2)
     {
         gettimeofday(&a,0);
         string s1="simple";
         prim(g,s1,filemode);
         gettimeofday(&b,0);
     }
 
    /*If option is -f call  Prim with Fibonacci Heap scheme */
      if(option=="-f" )
    {
        gettimeofday(&a,0);
        prim(g,"fheap",filemode);
        gettimeofday(&b,0);
    } 

  }

}
