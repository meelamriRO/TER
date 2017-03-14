#include "graph.hpp"

  
int main (){
  graph * G = ReadFromFile();
  GraphDisplay(G);
  RemoveEdge(G,0,1);
  cout<<"APres suppression de 0,1"<<endl;
  GraphDisplay(G);
  return 0; 
}
