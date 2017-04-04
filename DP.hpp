#ifndef DP_HPP
#define DP_HPP


#include "graph.hpp"
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;

int AddEdgeNetwork(NetworkFlow *R, int nood1, int nood2, int c, int c_,int flow); 
bool bfs(NetworkFlow *R, int path[]);
int indiceMinD (vector<int>Q, vector<int>D);
bool DijsktraTab(NetworkFlow *R, int path[]);
int  fordFulkerson(NetworkFlow *F);
NetworkFlow *  FlotMaxCoutMin(NetworkFlow *F);
list<struct i_j>* ConstrainGeneration(graph *G);

#endif
