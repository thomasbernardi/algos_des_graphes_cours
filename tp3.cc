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
    niveau[i] = -1;
  }
  //racine == 0
  dejaVu[0] = true;
  niveau[0] = 0;
  ordre[0]  = 1;
  pere[0]   = 0; //pere[r] = r

  queue<int> AT;
  AT.push(0);
  int t = 2;
  int current;
  while (AT.size() > 0) {
    current = AT.front();
    AT.pop();
    for (int j = 0; j < voisins[current].size(); j++) {
      int voisin_actuel = voisins[current][j];
      if (!dejaVu[voisin_actuel]) {
        dejaVu[voisin_actuel] = true;
        AT.push(voisin_actuel);
        ordre[voisin_actuel] = t;
        t++;
        pere[voisin_actuel] = current;
        niveau[voisin_actuel] = niveau[current] + 1;
      }
    }
  }
}

void ecritureNiveaux(int n, int niveau[]) {
  int counts[n];
  int ailleurs = 0;
  for (int i = 0; i < n; i++) {
    counts[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    int niv = niveau[i];
    if (niv == -1) {
      ailleurs++;
    } else {
      counts[niv]++;
    }
  }
  for (int i = 0; i < n; i++) {
    int c = counts[i];
    if (c > 0) {
      cout << "Il y a " << c << " sommets au niveau " << i << endl;
    }
  }
  if (ailleurs != 0) {
    cout << "Il y a " << ailleurs << " sommets qui ne sont pas dans la composante de 0." << endl;
  }
}

void parcoursProfondeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[]) {
  bool dejaVu[n];
  int debut[n];
  int fin[n];
  for (int i = 0; i < n; i++) {
    dejaVu[i] = false;
    niveau[i] = -1;
    debut[i] = 0;
    fin[i] = 0;
  }
  //racine == 0
  dejaVu[0] = true;
  debut[0] = 1;
  niveau[0] = 0;
  ordre[0]  = 1;
  pere[0]   = 0; //pere[r] = r

  vector<int> AT;
  AT.push_back(0);
  int t = 2;
  int current;
  while (AT.size() > 0) {
    current = AT.back();
    if (voisins[current].size() == 0) {
      AT.pop_back();
      fin[current] = t;
      t++;
    } else {
      int voisin_actuel = voisins[current].back();
      voisins[current].pop_back();
      if (!dejaVu[voisin_actuel]) {
        dejaVu[voisin_actuel] = true;
        AT.push_back(voisin_actuel);
        debut[voisin_actuel] = t;
        t++;
        pere[voisin_actuel] = current;
        niveau[voisin_actuel] = niveau[current] + 1;
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
    cout << a[i] << ", ";
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
  int ordre[n];// L'ordre de parcours.
  int niveau[n]; //-1 veut dire que ce n'est pas dans la composante de 0
  voisinsRandom(n, m, voisins);
  printGraph(n, m, voisins);                          // Le niveau du point.
  parcoursLargeur(n, voisins, niveau, ordre, pere);
  cout << "niveaux: ";
  printArray(n, niveau);
  cout << endl;
  ecritureNiveaux(n, niveau);
  parcoursProfondeur(n, voisins, niveau, ordre, pere);
  cout << "avec parcours profondeur: " << endl;
  ecritureNiveaux(n, niveau);
  return EXIT_SUCCESS;
}
