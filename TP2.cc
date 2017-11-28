#include <vector>
#include <fstream>
#include <math.h>
#include <iostream>

#define ABS 612
#define ORD 792

using namespace std;
typedef struct coord{int abs; int ord;} coord;

void pointrandom(int n, coord point[]) {
  srand(time(NULL));
  for (int i = 0; i < n; ++i) {
    point[i].abs = rand()%ABS;
    point[i].ord = rand()%ORD;
  }
}

void printpoint(coord point) {
  cout << "(" << point.abs << ", " << point.ord << ")";
}

void printpoints(int n, coord point[]) {
  for (int i = 0; i < n; ++i) {
    printpoint(point[i]);
    cout << endl;
  }
}

void printdistances(int n, int m, coord point[], int edge[][3]) {
  for (int i = 0; i < m; ++i) {
    printpoint(point[edge[i][0]]);
    cout << "-->";
    printpoint(point[edge[i][1]]);
    cout << " :: " << edge[i][2] << endl;
  }
}

void printarbre(int n, coord point[], int arbre[][2]) {
  for (int i = 0; i < n - 1; i++) {
    printpoint(point[arbre[i][0]]);
    cout << " ---> ";
    printpoint(point[arbre[i][1]]);
    cout << endl;
  }
}

void distances(int n, int m, coord point[], int edge[][3]) {
  int edge_index = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      coord p1 = point[i];
      coord p2 = point[j];
      int distance_squared = pow(abs(p1.abs - p2.abs), 2)
          + pow(abs(p1.ord - p2.ord), 2);
      edge[edge_index][0] = i;
      edge[edge_index][1] = j;
      edge[edge_index][2] = distance_squared;
      ++edge_index;
    }
  }
}

void tri(int m, int edge[][3]) {
  for (int i = m - 1; i > 0; --i) {
    for (int j = 0; j < i; ++j) {
      if (edge[j][2] > edge[j+1][2]) {
        int temp[3];
        temp[0] = edge[j][0];
        temp[1] = edge[j][1];
        temp[2] = edge[j][2];
        edge[j][0] = edge[j+1][0];
        edge[j][1] = edge[j+1][1];
        edge[j][2] = edge[j+1][2];
        edge[j+1][0] = temp[0];
        edge[j+1][1] = temp[1];
        edge[j+1][2] = temp[2];
      }
    }
  }
}

void kruskal(int n, int m, int edge[][3], int arbre[][2]) {
  int comp[n];
  int current = 0;
  for (int i = 0; i < n; i++) {
    comp[i] = i;
  }

  for (int i = 0; i < m; i++) {
    int x = edge[i][0];
    int y = edge[i][1];
    if (comp[x] != comp[y]) {
      int aux = comp[x];
      arbre[current][0] = x;
      arbre[current][1] = y;
      current++;
      for (int j = 0; j < n; j++) {
        if(comp[j] == aux) {
          comp[j] = comp[y];
        }
      }
    }
  }
}

void kruskalOpt(int n, int m, int edge[][3], int arbre[][2]) {
  std::vector< std::vector< int > > comps(n);
  int comp[n];
  int current = 0;
  for (int i = 0; i < n; ++i) {
    comps[i].push_back(i);
    comp[i] = i;
  }
  for (int i = 0; i < m; ++i) {
    int x = edge[i][0];
    int y = edge[i][1];
    int aux;
    int acquiring;
    if (comp[x] != comp[y]) {
      arbre[current][0] = x;
      arbre[current][1] = y;
      current++;
      if (comps[comp[x]] > comps[comp[y]]) {
        aux = comp[y];
        acquiring = comp[x];
      } else {
        aux = comp[x];
        acquiring = comp[y];
      }
      while (comps[aux].size() > 0) {
        int sommetChangeant = comps[aux].back();
        comps[acquiring].push_back(sommetChangeant);
        comp[sommetChangeant] = acquiring;
        comps[aux].pop_back();
      }
    }
  }
}

void AffichageGraphique(int n, coord point[], int arbre[][2])       // Cree le fichier Exemple.ps qui affiche
                                                                     // les points et l'arbre de Kruskal.
{ofstream output;
 output.open("Exemple.ps",ios::out);
 output << "%!PS-Adobe-3.0" << endl;
 output << "%%BoundingBox: 0 0 612 792" << endl;
 output << endl;
 for(int i=0;i<n;i++)
   {output << point[i].abs << " " << point[i].ord << " 3 0 360 arc" <<endl;
   output << "0 setgray" <<endl;
   output << "fill" <<endl;
   output << "stroke"<<endl;
   output << endl;
   }
 output << endl;
 for(int i=0;i<n-1;i++)
   {output << point[arbre[i][0]].abs << " " << point[arbre[i][0]].ord
	   << " moveto" << endl;
   output << point[arbre[i][1]].abs << " " << point[arbre[i][1]].ord
	  << " lineto" << endl;
   output << "stroke" << endl;
   output << endl;
   }
 output << "showpage";
 output << endl;
}

int main() {
  int n;             //Le nombre de points.
  cout << "Entrer le nombre de points: ";
  cin >> n;
  int m=n*(n-1)/2;   // Le nombre de paires de points.
  coord point[n];   // Les coordonnees des points dans le plan.
  int edge[m][3];    // Les paires de points et le carre de leur longueur.
  int arbre[n-1][2]; // Les aretes de lâ€™arbre de Kruskal.
  pointrandom(n, point);
  printpoints(n, point);
  distances(n, m, point, edge);
  printdistances(n, m, point, edge);
  tri(m, edge);
  cout << endl << "trie: " << endl << endl;
  printdistances(n, m, point, edge);
  kruskalOpt(n, m, edge, arbre);
  printarbre(n, point, arbre);
  AffichageGraphique(n, point, arbre);
  cout << "DONE" << endl;
  return 0;
}
