#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <queue>

#define ABS 612
#define ORD 792
using namespace std;

const int N=1400;
const int M=(N*(N-1))/2;

typedef struct coord{int abs; int ord;} coord;

void pointRandom(int n, coord point[]) {
  srand(time(NULL));
  for (int i = 0; i < n; ++i) {
    point[i].abs = rand()%ABS;
    point[i].ord = rand()%ORD;
  }
}
float distance(coord p1, coord p2) {
  int distance_squared = pow(abs(p1.abs - p2.abs), 2)
      + pow(abs(p1.ord - p2.ord), 2);
  return sqrt((float) distance_squared);
}
int voisins(int n, int dmax, coord point[], vector<int> voisin[]) {
  int nombredaretes = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (distance(point[i], point[j]) < dmax) {
        nombredaretes++;
        voisin[i].push_back(j);
        voisin[j].push_back(i);
      }
    }
  }
  return nombredaretes;
}

void voisins2arete(int n, vector<int> voisins[], int arete[][2]) {
  int arete_actuel = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < voisins[i].size(); j++) {
      int voisin = voisins[i][j];
      if (i < voisin) {
        arete[arete_actuel][0] = i;
        arete[arete_actuel][1] = voisin;
        arete_actuel++;
      }
    }
  }
}
void affichageGraphique(int n, int m, coord point[], int arete[][2], string name) {
  ofstream output;
   output.open(name + ".ps",ios::out);
   output << "%!PS-Adobe-3.0" << endl;
   output << "%%BoundingBox: 0 0 612 792" << endl;
   output << endl;
   //sommets
   for(int i=0;i<n;i++)
     {output << point[i].abs << " " << point[i].ord << " 3 0 360 arc" <<endl;
     output << "0 setgray" <<endl;
     output << "fill" <<endl;
     output << "stroke"<<endl;
     output << endl;
     }
   output << endl;
   //aretes
   for(int i = 0; i < m; i++) {
     output << point[arete[i][0]].abs << " " << point[arete[i][0]].ord
  	   << " moveto" << endl;
     output << point[arete[i][1]].abs << " " << point[arete[i][1]].ord
  	  << " lineto" << endl;
     output << "stroke" << endl;
     output << endl;
     }
   output << "showpage";
   output << endl;
}
bool existe(int n,int dis[],bool traite[],int &x);

void dijkstra(int n, vector<int> voisin[], coord point[], int pere[]) {
  float dist[n];
  bool traite[n];
  for (int i = 0; i < n; i++) {
    dist[i] = -1;
    traite[n] = false;
    pere[i] = -1;
  }
  pere[0] = 0;
  dist[0] = 0;

  bool fini = false;
  while(!fini) {
    int x = 0;
    for (int i = 0; i < n; i++) {
      if (traite[i] == false) {
        if (traite[x] || dist[x] < -.5 || (dist[i] < dist[x] && dist[i] > -.5)) {
          x = i;
        }
      }
    }
    traite[x] = true;
    for (int i = 0; i < voisin[x].size(); i++) {
      int y = voisin[x][i];
      if (!traite[y] &&
          (dist[y] == -1 ||
          dist[y] > dist[x] + distance(point[x], point[y])) ) {
        dist[y] = dist[x] + distance(point[x], point[y]);
        pere[y] = x;
      }
    }
  }
}
int construireArbre(int n,int arbre[][2],int pere[]) {
  //on commence avec 1 car on sait que pere[0] == 0
  int nombredaretes = 0;
  for (int i = 1; i < n; i++) {
    if (pere[i] != -1) { //i fait parti de l'arbre
      arbre[nombredaretes][0] = i;
      arbre[nombredaretes][1] = pere[i];
      nombredaretes++;
    }
  }
  return nombredaretes;
}

void print_distances(int n, coord point[]) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      cout << "between " << i << " and " << j << " :: " << distance(point[i], point[j]) << endl;
    }
  }
}

void print_arbre(int m, int arbre[][2]) {
  for (int i = 0; i < m; i++) {
    cout << arbre[i][0] << "-->" << arbre[i][1] << endl;
  }
}
int
main()
{
  int n;                           // Le nombre de points.
  cout << "Entrer le nombre de points: ";
  cin >> n;
  int dmax=250;                     // La distance jusqu'a laquelle on relie deux points.
  coord point[N];                  // Les coordonnees des points.
  vector<int> voisin[N];           // Les listes de voisins.
  int arbre[N-1][2];               // Les aretes de l'arbre de Dijkstra.
  int pere[N];                     // La relation de filiation de l'arbre de Dijkstra.
  int m;                           // Le nombre d'aretes
  pointRandom(n, point);
  m = voisins(n, dmax, point, voisin);
  cout << "m: " << m;
  int arete[M][2];                 // Les aretes du graphe
  voisins2arete(n, voisin, arete);
  affichageGraphique(n, m, point, arete, "graphe");
  dijkstra(n, voisin, point, pere);
  int nombredaretes = construireArbre(n, arbre, pere);
  print_arbre(nombredaretes, arbre);
  affichageGraphique(n, nombredaretes, point, arbre, "arbre");
  return EXIT_SUCCESS;
}
