#include<iostream>

#ifndef HEADER_FILE_H //use a name that is unique though!!
#define HEADER_FILE_H
#include "graph.h"
#endif

#include<string>
using namespace std;

 struct mstedege
{
  int x;
  int y;
};

int remove__min(vector<gnode> v,bool vis[],int minval);
int primfibheap(graph g,bool flagmode);
int prim(graph g,string option,bool flagmode);
int primsimple(graph g,bool flagmode);
void printmst(vector<mstedege> mst);
bool is_dkey_req(vector<gnode> v,bool vis[],list<gnode>::iterator i);
vector<gnode> decrease_key(vector<gnode> v,list<gnode>::iterator j,int);

