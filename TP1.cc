#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//n = #sommets
//m = #aretes
void grapherandom(int n, int m, int edge[][2], int comp[]) {
  srand(time(NULL));
  for (int i = 0; i < m; ++i) {
    edge[i][0]=rand()%n;
    edge[i][1]=rand()%n;
  }
  for (int i = 0; i < n; ++i) {
    comp[i] = i;
  }
}

void printgraph(int n, int m, int edge[][2], int comp[]) {
  cout << "n: " << n << endl;
  cout << "m: " << m << endl;
  for (int i = 0; i < m; ++i) {
    std::string result = "" + std::to_string(edge[i][0]) + " ---> "
        + std::to_string(edge[i][1]) + "   comp:  "
        + std::to_string(comp[edge[i][0]]) + " / " + std::to_string(comp[edge[i][1]]);
    cout << result << endl;
  }
  cout << "composantes:" << endl;
  for (int i = 0; i < n; ++i) {
    cout << i << " : " << comp[i] << endl;
  }
}

void composantes(int n, int m, int edge[][2], int comp[]) {
  for (int i = 0; i < m; ++i) {
    int x = edge[i][0];
    int y = edge[i][1];
    if (comp[x] != comp[y]) {
      int aux = comp[x];
      for (int j = 0; j < n; j++) {
        if (comp[j] == aux) {
          comp[j] = comp[y];
        }
      }
    }
  }
}

void composantesOpt(int n, int m, int edge[][2], int comp[]) {
  std::vector< std::vector< int > > comps(n);
  for (int i = 0; i < n; ++i) {
    comps[i].push_back(i);
  }
  for (int i = 0; i < m; ++i) {
    int x = edge[i][0];
    int y = edge[i][1];
    int aux;
    int acquiring;
    if (comp[x] != comp[y]) {
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

void ecrituretailles(int n, int m, int comp[]) {
  int nombredecomposantes[n];
  int tailles[n];
  //initialize to zero
  for (int i = 0; i < n; ++i) {
    nombredecomposantes[i] = 0;
    tailles[i] = 0;
  }

  //for every sommet in comp, increase nombredecomposantes
  //corresponding to that sommet
  for (int i = 0; i < n; ++i) {
    ++nombredecomposantes[comp[i]];
  }

  //for every composante, increase the count in tailles of
  //the number of composantes that have that number of sommets
  for (int i = 0; i < n; ++i) {
    ++tailles[nombredecomposantes[i]];
  }
  if (tailles[1] > 0) {
    cout << "Il y a " << tailles[1]
        << " points isoles." << endl;
  }
  for (int i = 2; i < n; ++i) {
    if (tailles[i] > 0) {
      cout << "Il y a " << tailles[i] <<
          " composantes de taille " << i << endl;
    }
  }
}
int main()
{
  int n;     // Nombre de sommets.
  int m;     // Nombre d'aretes.
  cout << "Entrer le nombre de sommets:";
  cin >> n;
  cout << "Entrer le nombre d'aretes:";
  cin >> m;
  int edge[m][2];    // Tableau des aretes.
  int comp[n];
  grapherandom(n, m, edge, comp);       // comp[i] est le numero de la composante contenant i.
  printgraph(n, m, edge, comp);
  composantesOpt(n, m, edge, comp);
  printgraph(n, m, edge, comp);
  ecrituretailles(n, m, comp);
  return EXIT_SUCCESS;
}
