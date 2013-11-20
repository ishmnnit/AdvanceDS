#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
#include<cmath>
#ifndef HEADER_FILE_H2 //use a name that is unique though!!
#define HEADER_FILE_H2
#include "fibheap.h"
#endif
#include<stdio.h>
using namespace std;
#define size 10

/*Constructor for Min Fibonacci Heap */

 MinFibheap::MinFibheap()
 {
    root=NULL;
    nodecount=0;
 }

/* This function take key value, wieigt and vertex as a parameter and create
   a Fibonacci node and return it */

 MinFibnode* MinFibheap::make_fibnode(int data,int weight,int vertex)
 { 
     MinFibnode *fnode= new MinFibnode;
     fnode->data=data;
     fnode->degree=0;
     fnode->weight=weight;
     fnode->parent=NULL;
     fnode->child=NULL;
     fnode->left=fnode;
     fnode->right=fnode;
     fnode->childcut=false;
     fnode->fvertexid=vertex;
     return fnode;
 }


/*Following Function insert a node in Fibonacci heap whose node data is data*/
void MinFibheap::insert(MinFibnode *node)
 {
    /* Concatenate the node in circular doubly link list and update the 
       min value if Required */
    if(root)
      {
        root->left->right=node;;
        node->right=root;
        node->left=root->left;
        root->left=node;
        if(node->data < root->data)
           root=node;
      }
    /*If root is NULL,Create a new fibbnoci heap and assign min value to this value*/
    else
      {
         root=node;
      }
  
     /* Increase the count of total no of node in Fibonacci Heap */
     nodecount=nodecount+1;
  }


   

 /* This Function extract Minimum node from Fibonacci Heap 
    When minimum node is removed from Fibonacci Heap, Pointer 
    remaining in list are updated but pointers in extracted 
    node left unchanged.Also use pairwise_combine procdure 
    for paiwise combining of Min Tree of same degree*/

 MinFibnode* MinFibheap::remove_min()
 {
    
    //Saving Pointer z to minimum node in Fibonacci Heap
    MinFibnode* z=root;
    
    //If z is NULL Fibbonacci Heap is already Empty and we are done 
    if(z==NULL)
    { 
      /* You can not return from empty heap */
      return z;
    }

    MinFibnode* childnode=z->child;
    MinFibnode *firstchild,*nextchild;
    if(childnode!=NULL)
      {
           firstchild=childnode;
        do
          {
           /* For the Minimum Node of the tree add all the children into the root list */
            nextchild=childnode->right;
            root->left->right=childnode;
            childnode->right=root;
            childnode->left=root->left;
            root->left=childnode;
            childnode->parent=NULL;
            childnode=nextchild;
          }while(firstchild!=nextchild);
      }  

      /* Removing Minimum Node z from the Fibonacci Heap */
      z->left->right=z->right;
      z->right->left=z->left;
     
      /*If z=z->right then z was the only node in the root list and it had no children
       so make Fibonacci heap Empty Now */
       if(z==z->right)
         root=NULL;
       else
       {
        /* Set root point to a Node other than the Node z , this node may not be Minimum Node 
         in the root list.Also do pairwise combining ,which repeatdley merge the node of the same degree until
         all the Min tree n Fibonacci Heap has a distinct degree */
        root=z->right;
        pairwise_combine();
       }

    /* Reset total count of the Node and then return Minimum node of the tree */
    nodecount=nodecount-1;
    return z;
 }


  /* pairwise combining repeatdley merge the node of the same degree until
     all the Min tree in Fibonacci Heap has a distinct degree */

  void MinFibheap::pairwise_combine()
   {
        
       int d;
       int D=45;
       MinFibnode* A[45+1];
       for(int i=0;i<=45;i++)
       A[i]=NULL;
       //  For each root list node look for others node of  of the same degree.
        
        MinFibnode* start = root;
        MinFibnode* w =root;
        do {
            MinFibnode* x = w;
            MinFibnode* nextnode = w->right;
            int d = x->degree;
            while (A[d] != NULL) 
              {
                
                MinFibnode *y = A[d];
                if (x->data > y->data) 
                  {
                     MinFibnode *temp = y;
                     y = x;
                     x = temp;
                   }
                
                    // Because removeMin() arbitrarily assigned the min
                    // reference, we have to ensure we do not miss the
                    // end of the root node list.
                    if(y == start)
                    start = start->right;

                    // If we wrapped around we need to check for this case.
                    if(y == nextnode)
                      nextnode = nextnode->right;
                
                    if(y==root)
                      root=x;
                   /* Make Node y child of node x , as x is the node which contain smaller value */
                   if(y!=NULL && x!=NULL && y->fvertexid!=x->fvertexid )
                      fibonacci_link(y,x);

                   if(x->right==x)
                       root=x;

                A[d] = NULL;
                d++;
            }//End While

            /* Save the MinFibnode in tha array,if later we found node with same Degree
               we again need it to combine it */
            A[d] = x;
            /* Go to the next node in the list */
            w = nextnode;
         } while (w != start);

        /* Now in the array we have all the Min tree with distict degree now by using these we would
           construct New fibonacci heap */
        root = NULL;

        for(int j=0;j<=D;j++)
        {
           if(A[j]!=NULL)
            {
               A[j]->left=A[j];
               A[j]->right=A[j];
              if(root!=NULL)
                {
                    (root->left)->right=A[j];
                    A[j]->right=root;
                    A[j]->left=root->left;
                    root->left=A[j];
                    if(A[j]->data<root->data)
                       root=A[j];
                }
              else
                {
                       root=A[j];
                }
            if(root==NULL)
              root=A[j];
            else if(A[j]->data < root->data)
              root=A[j];
           }
      }
  }



void MinFibheap::fibonacci_link(MinFibnode* y,MinFibnode* node)
{   

    /*Remove y from the root list of Fibonacci Heap */
    y->left->right=y->right;
    y->right->left=y->left;

    /*If there is only one node in Fibonacci Heap */
    if(node->right==node)
      root=node;
    
     /* Make Fibonacci heap node to the parent of y */
     y->left=y;
     y->right=y;
     y->parent=node;
    
    /*If smaller node dose not have any child make y child of the node */
    if(node->child==NULL)
       node->child=y;

    /*Add Node to the left of the child pointer of node */
    y->right=node->child;
    y->left=node->child->left;

    /* In the left of the child node ,now make it such that it right pointer 
       point to y and in left of node child input y*/
    node->child->left->right=y;
    node->child->left=y;
    
    /* Make it node child pointer always point to the minimum node */
    if(y->data < node->child->data)
       node->child=y;
      
    /*Increase the degree of the Node */
      node->degree++;
    
    /*Make childcut value for node y is false */
      y->childcut=false;
   
  }


/* This function decrease the value of fibonacci node x to value k */

void MinFibheap::decrease_key(MinFibnode* x,int k)
  {
    /* Ensure new key is not greater than current key. In that situation
       do nothing */
    if(x->data < k || root == NULL)
      {
        return;
      }
    /* Assign new key to x */
    x->data=k;
    MinFibnode *y=x->parent;
    
    /*If Heap order is violated call funtion cut and cascade_cut */
    if(y!=NULL && x->data < y->data)
      {
        cut(x,y);
        cascade_cut(y);
      }

   if(x->data < root->data)
      root=x;

  }

  
/* Remove x from the child list of y and then decrease 
    degree of y*/


void MinFibheap::cut(MinFibnode* x,MinFibnode* y)
  {
    
    /* if x is only child ,make child of y is NULL */
    if(x==x->right)
      y->child=NULL;

    /*Remove x from list of child node of y */
     x->left->right=x->right;
     x->right->left=x->left;
    
    /* x is Minimum child ,update pointer to child node */
    if(x==y->child)
      y->child=x->right;
    
    /* Update the degree of the node y */
    y->degree=y->degree-1;

    x->right=x;
    x->left=x;
    
    /* Add x into the root List */
    root->left->right=x;
    x->right=root;
    x->left=root->left;
    root->left=x;
    x->parent=NULL;
    x->childcut=false;
  }
  
  
void MinFibheap::cascade_cut(MinFibnode* y)
  { 
    
    MinFibnode* z=y->parent;
    /* If y is a root list  no more cascading required, For y to be
       in root list it parent would be NULL */

    if(z!=NULL)
      {
        /* If childcut happens first time no more cut and cascading required
           just mark the node to indicate childcut is true */

        if(y->childcut==false)
            {
              y->childcut=true;
            }
        /* if y is marked y is just lost the second child , y is cut from here 
           and added to the root list and cascading cut is called to the parent 
           of the node */
        else
          {
            cut(y,z);
            cascade_cut(z);
          }
              
      }
  }
