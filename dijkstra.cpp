#include <iostream>
#include <vector>
#include <list>
#include <new>
#include <string>
#include <fstream>
#include "dirent.h" 
#include "string.h"
#include <sstream> 
#include <stdlib.h>
#define pp pair<int,int>
#include <queue>


using namespace std; 


//structure noeud voisin
struct nood {
  int n;
  int c;
  int c_; 
};

//structure graphe
//Contenant un tabeleau de liste des voisins
struct graph{
  vector <list <nood> > neighbours;
  int N;
};

//Initialisation du graphe; 
//Noeud seulement; 
//les listes de voisins sont vides
struct graph * GraphInit(struct graph *g, int NbNood){
  g->N = NbNood;
  g->neighbours = vector <list <nood> > (NbNood);
  return g;
}

//Ajouter un arc nood1==source; noode2==destination; c==capacité; c_==cout
int AddEdge(struct graph *g, int nood1, int nood2, int c, int c_){
  if(nood1 >= g->N || nood2 >= g-> N)
    return 0;
  else{ 
    struct nood n_; 
    n_.n = nood2; 
    n_.c= c; 
    n_.c_= c_;
    g->neighbours[nood1].push_back(n_); 
    return 1;
  }
}

//surcharge de l'operateur << pour affichage 
std::ostream& operator<<(std::ostream& os, nood& p)
{
  return os  << " " << p.n << " " << p.c << " " <<p.c_<< endl;
}

//Affichage du graphe
void GraphDisplay(struct graph *g){
  for (int i = 0; i < g->N; i++){
   
    list<nood>::iterator p = g->neighbours[i].begin();
    while(p != g->neighbours[i].end()) {
      cout<<"\n"<< i; 
      cout << *p;
      p++;
    }
  }
  cout <<endl; 
}

//sauvegarde du graphe dans un fichier
//les fichiers sont dans le rep ./archive/
//le fichier est de la forme: 
//Nombre de noeud: N
//source destination capacité cout 
void SaveFile(struct graph *g){
  ofstream myfile;
  string filename; 
  cout << "Entrer le nom du fichier pour sauvegarde:  "<<endl;
  cin >> filename;
  filename = "./archive/"+filename;
  myfile.open(filename.c_str() );
  myfile << "Nombre de noeuds: "<<g->N;
  for (int i = 0; i < g->N; i++){
    if(g->neighbours[i].size()){
      list<nood>::iterator p = g->neighbours[i].begin();
      while(p != g->neighbours[i].end()) {
	myfile<<"\n"<< i;
	myfile << *p;
	p++;
      }
    }
  }
  myfile <<endl;
  myfile.close();
}

//fonction utile pour Dijkstra tableau
//retourne l'indice du plus petit element dans Q
//Q est notre tableau de traitement 
int indiceMinD (vector<int>Q, vector<int>D){
  vector <int> QD(Q.size());
  int indice_;
  int indice;   
  for (int i = 0; i < Q.size(); i++){
     
    indice = Q[i];
  
    QD[i]=D[indice]; 
  }
   
    
  int min = QD[0];
  indice_= 0; 
   
  for (int i = 0; i < QD.size(); i ++){
    
    if(min > QD[i]){
      min = QD[i]; 
     
      indice_= i;
    }
  }
  
  return indice_; 
}
	  
//algo dijkstra avec tableau
void DijsktraTab(struct graph *G, int s)
{
  
  vector<int>d(G->N);//tableau des distance
  vector<int>P(G->N);//tablea de pred
  vector<int>Q;//tableau des traitements
  vector<bool>B(G->N);// tableau de bool pour éviter les cycles infini
 
  /* Initialisation */
  for(int i=0; i< G->N; i++)
    {
      P[i] = -1; 
      d[i] = 1e9 ;
      B[i] = false; 
    }
    d[s] = 0 ;
    Q.push_back(s); 
  
  
  while(!Q.empty()) //tq le tableau de traitement n'est pas vide
    {
      
      int min = indiceMinD(Q,d); //min dans Q
     
      int min_ = Q[min];//indice min dans D
     
      Q.erase(Q.begin()+min);//enlever l'element min de Q
     
     
        
      if (B[min_] == false){


	for(list<nood>::iterator it = G->neighbours[min_].begin(); it != G->neighbours[min_].end(); it++)//pour tous les voisins du noeud le plus proche
	  {
	    if(d[(*it).n] > d[min_] + (*it).c_)
	      {
	
		d[(*it).n] = d[min_] + (*it).c_ ;
	
		P[(*it).n]= min_;
		
		Q.push_back((*it).n); 


		
	      }
	  }
	B[min_] = true; //Noeud traité
      }
    }
  //affichage de la liste de pred
  cout <<"Liste des predececeurs: "<<endl;
  
  for(int i = 0; i < G->N; i++) 
    {
      cout << "pred du noeud "<<i <<":"<<endl; 
      cout << P[i] << " avec un cout de: " <<d[i]<<endl ;
      }
  cout<<endl; 
  
}

//structure priorité pour tas 
struct Prio{
	//operateur de comparaison de distance
  int operator() ( const pair<int, int>& p1, const pair<int, int>& p2 ){
    return p1.second > p2.second;
  }
};

//Dijkstra avec tas; 
//On reprend le meme principe utilisé dans la premiere implémentation
//
void DijikstraTas(struct graph *G , int s)
{
  int n =G->N;
  int D[n];
  int P[n];
  bool B[n];
  for (int i=0;i<n;i++)
    {
      D[i]= 1e9 ;
      B[i]=false;
      P[i]=-1;
    }
  D[s]=0;
  priority_queue <pp, vector<pp > ,Prio> Q;//traitement par le tas Q 
  Q.push(pp(s,D[s]));
  while(!Q.empty())// tq le tas n'est pas vide 
    {
      int u = Q.top().first;//On prend le noeud le plus proche
      Q.pop();//on supprime ce noeud du tas de traitment
      if(B[u]==false)
	{
	  for (std::list<nood>::iterator it = G->neighbours[u].begin(); it != G->neighbours[u].end(); it++)//pour tous les voisin du noeud le plus prohce
	    {
	      if(D[(*it).n]>D[u]+(*it).c_)
		{
		  D[(*it).n]=D[u]+(*it).n;
		  P[(*it).n]=u;
		  Q.push(pp((*it).n,D[(*it).n]));
		  
		}
	      
	    }
	  B[u]=true;//Noeud traité

	  
	}
    }
	//Affichage de pred
	// -1 : pas de pred 
  cout <<"Liste des predececeurs: "<<endl;
  
  for(int i = 0; i < G->N; i++) 
    {
      cout << "pred du noeud "<<i <<":"<<endl; 
      cout << P[i] <<endl ;
    }
  cout<<endl; 
}


//Lecture du graphe a partir d'un fichier 
//la fonction permet de lister les fichiers du rep ./archive
void ReadFromFile(){
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
    struct graph * G = new struct graph;
    string tmp;
    int n;
    cout << "CONSTRUCTION DU GRAPHE POUR DIJKSTRA..."<< endl;
    myfile >> tmp >> tmp >> tmp >> n;
    G = GraphInit (G,n);
    cout << "Nombre de Noeuds: "<<G->N <<endl<<endl;   
    int s;
    int d; 
    int c; 
    int c_;
    while(myfile >>s >> d >> c >> c_){
      cout<< "Ajout de l'arc: "<<endl; 
      cout <<"source: "<< s<<" destination: "<< d << " capacite: "<<c <<" cout: "<< c_<< endl;
      AddEdge(G,s,d,c,c_);
      cout <<endl; 
    }
    GraphDisplay(G);
    int s_; 
    cout << "Execution Dijkstra, donnez sommet de depart: "<<endl; 
    cin >> s_; 
    cout << "Dijkstra avec tableau: "<<endl; 
    DijsktraTab(G,s_);
    cout << "Dijkstra avec tas: "<<endl;
    DijikstraTas(G,s_); 
    
  }  
  myfile.close();
  
  
}


//programme principal
//menu avec 3 options
//1)lecture du graphe depuis un fichier et execution de dijkstra
//2)Construction du graphe par l'utilisateur, avec sauvegarde dans le rep ./archive.
int main (){
  int menu; 
    
  do{
    cout<<"1)-LIRE VOTRE GRAPHE DEPUIS UN FICHIER"<<endl; 
    cout<< "2)-CREER VOTRE GRAPHE"<<endl; 
    cout<<"3)-QUITTER"<<endl; 
    
    cin >>menu; 
    if(menu == 1){
      ReadFromFile(); 
    }
    if(menu == 2){
      cout<<"Nombre de noeuds ?: "<<endl; 
      int n; 
      cin >> n; 
      int menu_2 = 1; 
      
      struct graph * G = new struct graph;
      G = GraphInit (G,n);
      
      while (menu_2 != 0){
	cout<<"Ajouter arc? [1/0]"<<endl; 
	cin >> menu_2; 
	if( menu_2){
	  cout<<"[source]"<<endl;
	  int source; 
	  cin >> source;
	  cout<<"[destination]"<<endl;
	  int destination; 
	  cin >> destination; 
	  
	  cout<<"[capacité]"<<endl;
	  int capacite;
	  cin >> capacite; 
	  
	  cout<<"[cout]"<<endl;
	  int cout_; 
	  cin >> cout_;
	  AddEdge(G,source,destination,capacite,cout_);
	
	} 
      }
      cout<<"Sauvegarder votre Graphe? [1/0]:"<<endl; 
      int save; 
      cin >> save; 
      if (save)
	SaveFile(G);
    }
    
  }while(menu !=3);
  
  return 0;
}
