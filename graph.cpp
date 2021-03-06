#include "graph.hpp"

struct graph * GraphInit(struct graph *g, int NbNood){
  g->N = NbNood;
  g->neighbours = vector <list <nood> > (NbNood);
  return g;
}


int AddEdge(struct graph *g, int nood1, int nood2, int c, int c_){//ajout <=0;
  if(nood1 >= g->N || nood2 >= g-> N)
    return 0;
  else{ 
    struct nood n_; 
    n_.n = nood2; 
    n_.c= c;
    n_.c_=c_;
    g->neighbours[nood1].push_back(n_); 
    return 1;
  }
}


bool isEdge(graph *g,int i, int j){
  list<nood>::iterator p = g->neighbours[i].begin();
  while(p != g->neighbours[i].end())
    {
      if(p->n == j)return true;
      p++;
      
    }
  return false;
}

int updateEdge(graph *g,int i, int j, int cost){
  list<nood>::iterator p = g->neighbours[i].begin();
  while(p != g->neighbours[i].end())
    {
      if(p->n == j){
	p->c=cost;
	return 1;
      }
      p++;
      
    }
  return 0;
}

int RemoveEdge(graph* g, int i, int j){
  if(!isEdge(g,i, j))
    return 0 ;
  else {
    list<nood>::iterator p = g->neighbours[i].begin();
    while(p != g->neighbours[i].end())
      {
	if(p->n == j)
	  {
	     g->neighbours[i].erase(p) ;
	    return 1;
	  }
	p++ ;
      }
  }
}


std::ostream& operator<<(std::ostream& os, nood& p)
{
  return os  << " Destination: " << p.n << " Cout: " << p.c << " Capcité: "<<p.c_<<" "<< endl;
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
    int c_= CAPACITE;
    while(myfile >>s >> d >> c){
      AddEdge(G,s,d,c,c_);
    }    
  }
  myfile.close();
  return G; 
  
}

NetworkFlow * GraphToNetworkFlowInit(struct graph *G, int s, int t){
  NetworkFlow * F = new struct NetworkFlow;

  F->N = G->N;
  F->s = s;
  F->t = t;
  F->flow = 0;
  F->neighbours = vector <list <FlowNood> > (F->N);

  for (int i = 0; i<F->N; i++){
    list<nood>::iterator p1 = G->neighbours[i].begin();
    list<FlowNood>::iterator p2 = F->neighbours[i].begin();
    
    while(p1 != G->neighbours[i].end()){
      struct FlowNood f; 
      f.n=p1->n;
      f.c=p1->c;
      f.c_=p1->c_;
      f.flow = 0;
      F->neighbours[i].push_back(f);
      p1++;
      p2++;
    }
  }
    
  return F;
}

std::ostream& operator<<(std::ostream& os, FlowNood& p)
{
  return os  << " Destination: " << p.n << " Cout: " << p.c << " Capcité: "<<p.c_<<" Flot: "<< p.flow<<" "<< endl;
}



void NetworkFlowDisplay(NetworkFlow *F){
  cout<<"REDEAU DE FLOT CORRESPONDANT..."<<endl;
  cout<<"FLOT CIRCULANT: "<<F->flow<<endl; 
  for (int i = 0; i < F->N; i++){
    list<FlowNood>::iterator p = F->neighbours[i].begin();
    while(p != F->neighbours[i].end()) {
      cout<<"\n"<<"source :"<< i; 
      cout << *p;
      p++;
    }
  }
  cout <<endl; 
}
  
