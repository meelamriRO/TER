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
#define CAPACITE 1


struct nood {
  int n;
  int c;
  int c_;
};

struct graph{
  vector <list <nood> > neighbours;
  int N;
};

struct FlowNood{
  int n;
  int flow;
  int c;
  int c_;
};

struct NetworkFlow{
  int N; 
  int s;
  int t;
  int flow; 
  vector <list <FlowNood>> neighbours;
}; 
  
  
struct graph * GraphInit(struct graph *g, int NbNood);
int AddEdge(struct graph *g, int nood1, int nood2, int c, int c_);
bool isEdge(graph *g, int i, int j); 
int RemoveEdge(struct graph *g, int nood1, int nood2); 
ostream& operator<<(std::ostream& os, nood& p);
void GraphDisplay(struct graph *g);
struct graph* ReadFromFile();

struct NetworkFlow * GraphToNetworkFlowInit(struct graph *g, int s, int t); 
ostream& operator<<(std::ostream& os, nood& p);
void NetworkFlowDisplay(struct NetworkFlow *F);

#endif
