#include "graph.hpp"
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;

bool bfs(NetworkFlow *R, int path[]){
  int s = R ->s;
  int t = R->t;
  
  // Create a visited array and mark all vertices as not visited
  bool visited[R->N];
  memset(visited, 0, sizeof(visited));
 
    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    path[s] = -1;
 
    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
	list<FlowNood>::iterator p = R->neighbours[u].begin();
	for (p; p!=R->neighbours[u].end();p++){
	  
	  if (visited[p->n]==false && p->c_ > 0)
            {
	      q.push(p->n);
	      path[p->n] = u;
	      visited[p->n] = true;
            }
        }
    }
    cout<<"Pred: "<<endl; 
    for (int i =0; i < R->N; i++)cout<<path[i]<<" ";
    cout<<endl; 
    cou<<"visited: "<<endl;
    for (int i =0; i < R->N; i++){
      if(visited[i])cout<<i<<" ";
    }
    cout<<endl; 
    
    
    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}

NetworkFlow * fordFulkerson(NetworkFlow *F){
 
  //Cree le graph residuel, mettre les capacités comme résidu 
  NetworkFlow *R = new struct NetworkFlow;
  R->N = F->N; 
  R->s = F->s; 
  R-> t = F->t;
  R->flow = F->flow; 
  R->neighbours = vector <list <FlowNood> > (R->N);
  
  for (int i = 0; i<F->N; i++){
    list<FlowNood>::iterator p1 = F->neighbours[i].begin();
    list<FlowNood>::iterator p2 = R->neighbours[i].begin();
    
    while(p1 != F->neighbours[i].end()){
      struct FlowNood r; 
      r.n=p1->n;
      r.c=p1->c;
      r.c_=p1->c_;
      r.flow = p1->flow;
      R->neighbours[i].push_back(r);
      p1++;
      p2++;
    }
  }

  int path[R->N];
  int max_flow = 0; 
  // Augmenter le flot si existe chemin entre s et t 
  while (bfs(R,path)){
    int path_flow = INT_MAX;
    for (int v = R->t; v!= R->s; v=path[v]) {
      int u = path[v];
      list<FlowNood>::iterator p = R->neighbours[u].begin();
      while(p != F->neighbours[u].end()){
	if(p->n == v)
	  break;
	p++;
      }
      path_flow = min(path_flow, p->c_);
    }
    
    for (int v = R->t; v != R->s; v=path[v]){
      u = path[v];
      list<FlowNood>::iterator p = R->neighbours[u].begin();
      while(p != F->neighbours[i].end()){
	if(p->n == v){
	  p->flow -= path_flow; 
	  rGraph[u][v] -= path_flow;
	  rGraph[v][u] += path_flow;
	}
      }
    }
    max_flow += path_flow;
  }
  
  // Return the overall flow
  return max_flow;
  
}

  int main (){
  graph * G = ReadFromFile();
  GraphDisplay(G);
  //GraphDisplay(G);
  NetworkFlow * F = GraphToNetworkFlowInit(G,0,1);
  NetworkFlowDisplay(F);
  NetworkFlow * R = fordFulkerson(F);
  NetworkFlowDisplay(R);
  int path[R->N]; 
  cout<<"Chemin: "<<bfs(R, path)<<endl; 
  return 0; 
}
