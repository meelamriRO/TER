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

struct graph * GraphInit(struct graph *g, int NbNood){
  g->N = NbNood;
  g->neighbours = vector <list <nood> > (NbNood);
  return g;
}


int AddEdge(struct graph *g, int nood1, int nood2, int c){
  if(nood1 >= g->N || nood2 >= g-> N)
    return 0;
  else{ 
    struct nood n_; 
    n_.n = nood2; 
    n_.c= c;
    g->neighbours[nood1].push_back(n_); 
    return 1;
  }
}

std::ostream& operator<<(std::ostream& os, nood& p)
{
  return os  << " Destination: " << p.n << " Cout: " << p.c << " "<< endl;
}

    
void GraphDisplay(struct graph *g){
  for (int i = 0; i < g->N; i++){
   
    list<nood>::iterator p = g->neighbours[i].begin();
    while(p != g->neighbours[i].end()) {
      cout<<"\n"<<"source :"<< i; 
      cout << *p;
      p++;
    }
  }
  cout <<endl; 
}








graph* ReadFromFile(){
  struct graph * G = new struct graph;
  cout<<"CHOISIR VOTRE FICHIER:"<<endl; 
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir ("./archive")) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      cout << ent->d_name << "  ";
    }
    cout << endl;
    cout << endl;
    cout << endl; 
    closedir (dir);
  } else {
    perror ("");
  }
  string filename; 
  cin >> filename; 
  filename = "./archive/"+filename;
  ifstream myfile(filename.c_str(),std::ios::in | std::ios::out);
  if(!myfile)
    cout<<"FICHIER NON EXISTANT"<< endl;
  else{
    string tmp;
    int n;
    cout << "CONSTRUCTION DU GRAPHE..."<< endl;
    while (myfile >> tmp){
      if(tmp == "NODES"){
	myfile >> n;
	G = GraphInit (G,n);
	cout << "Initialisation... Nombre de Noeuds: "<<G->N <<endl<<endl;
      }
      if(tmp == "LINKS"){
	cout << "Ajout des arcs.."<<endl;
	break; 
      }
    }
    int s;
    int d; 
    int c; 
    while(myfile >>s >> d >> c){
      AddEdge(G,s,d,c);
    }    
  }
  myfile.close();
  return G; 
  
}

int main (){
  graph * G = ReadFromFile();
  GraphDisplay(G);
  return 0; 
}
  

