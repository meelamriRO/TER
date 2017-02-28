#ifndef graph_hpp
#define graph_hpp


#include <iostream>
#include <vector>
#include <list>
#include <new>
#include <string>
#include <fstream>
#include "dirent.h" 



using namespace std; 



struct nood {
  int n;
  int c; 
};

struct graph{
  vector <list <nood> > neighbours;
  int N;
};

struct graph * GraphInit(struct graph *g, int NbNood);
int AddEdge(struct graph *g, int nood1, int nood2, int c);
ostream& operator<<(std::ostream& os, nood& p);
void GraphDisplay(struct graph *g);
struct graph* ReadFromFile(); 

#endif
