#include "graph.hpp"

  
int main (){
  graph * G = ReadFromFile();
  GraphDisplay(G);
  //RemoveEdge(G,0,1);
  //cout<<"Après suppression de 0,1"<<endl;
  //GraphDisplay(G);
  NetworkFlow * F = GraphToNetworkFlowInit(G,0,5);
  NetworkFlowDisplay(F);
  
  return 0; 
}
