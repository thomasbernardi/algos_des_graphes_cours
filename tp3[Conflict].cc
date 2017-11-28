#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

void voisinsRandom(int n, int m, vector<int> voisins[]) {
  srand(time(NULL));
  for (int i = 0; i < m; i++) {
    bool add = false;
    while (!add) {
      add = true;
      int x = rand()%n;
      int y = rand()%n;

      //pas de boucles
      if (x == y) add = false;
      if (add) {
        //pas d'aretes multiples
        for (int j = 0; j < voisins[x].size(); j++) {
          if (voisins[x][j] == y) {
            add = false;
            break;
          }
        }
      }
      if (add) {
        //symmetrie
        voisins[x].push_back(y);
        voisins[y].push_back(x);
      }
    }
  }
}

void parcoursLargeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[]) {
  bool dejaVu[n];
  for (int i = 0; i < n; i++) {
    dejaVu[i] = false;
  }
  //racine == 0
  dejaVu[0] = true;
  niveau[0] = 0;
  ordre[0]  = 1;
  pere[0]   = 0; //pere[r] = r

  queue<int> AT;
  AT.push(0);
  cout << "AT Size: " << AT.size() << endl;
  int t = 2;
  while (AT.size() > 0) {
    int current = AT.front();
    AT.pop();
    cout << "Voisins[current] size: " << voisins[current].size() << endl;
    for (int j = 0; j < voisins[current].size(); j++)
      cout << "j: " <<
      if (!dejaVu[j]) {
        dejaVu[j] = true;
        AT.push(j);
        ordre[j] = t;
        t++;
        pere[j] = current;
        niveau[j] = niveau[current] + 1;
        cout << "::" << niveau[j] << endl;
      }
    }
  }
}

void printGraph(int n, int m, vector<int> voisins[]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < voisins[i].size(); j++) {
      cout << i << " --> " << voisins[i][j] << endl;
    }
  }
}

void printArray(int n, int a[]) {
  for (int i = 0; i < n; i++) {
    cout << a[n] << ", ";
  }
}
int
main()
{
  int n;                                    // Le nombre de sommets.
  int m;                                    // Le nombre d'aretes.
  cout << "Entrer le nombre de sommets: ";
  cin >> n;
  cout << "Entrer le nombre d'aretes: ";
  cin >> m;
  vector<int> voisins[n];                   // Les listes des voisins.
  int pere[n];                              // L'arbre en largeur.
  int ordre[n];                             // L'ordre de parcours.
  int niveau[n];
  voisinsRandom(n, m, voisins);
  printGraph(n, m, voisins);                          // Le niveau du point.
  parcoursLargeur(n, voisins, niveau, ordre, pere);
  cout << "voisins: ";
  printArray(n, niveau);
  cout << endl;
  return EXIT_SUCCESS;
}
