#include <iostream>
#include <vector>

using namespace std;

const int N=6;
const int INF=9999;                      //La valeur infinie.

void floydWarshall(int longueur[][N],int dist[][N],int chemin[][N]) {
  //initialization
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (longueur[i][j] != INF) {
        dist[i][j] = longueur[i][j];
        chemin[i][j] = j;
      } else {
        dist[i][j] = INF;
        chemin[i][j] = -1;
      }
    }
  }

  //corps de l'algorithme
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        //have to make sure to exclude adding "shortcuts" of "infinite" length
        if (dist[j][k] > dist[j][i] + dist[i][k] && dist[i][k] != INF) {
          cout << j << "--" << k << " ==> " << j << "--" << i << "--" << k << endl;
          dist[j][k] = dist[j][i] + dist[i][k];
          chemin[j][k] = chemin[j][i];
        }
      }
    }
  }

  for (int i = 0; i < N; i++) {
    if (dist[i][i] < 0) {
      cout << "Il existe un cycle oriente de poids negatif" << endl;
      return;
    }
  }
}

void fermeturetransitive(int arc[][N], int fermeture[][N]) {
  //initialization
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j) {
        fermeture[i][j] = 1;
      } else {
        fermeture[i][j] = arc[i][j];
      }
    }
  }

  //corps de l'algorithme
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        //have to make sure to exclude adding "shortcuts" of "infinite" length
        if (fermeture[j][k] == 0 && fermeture[j][i] == 1 &&
            fermeture[i][k] == 1) {
          cout << j << "--" << k << " ==> " << j << "--" << i << "--" << k << endl;
          fermeture[j][k] = 1;
        }
      }
    }
  }
}

//TODO
void compfortconnexe(int fermeture[][N]) {
  std::vector< std::vector< int > > comps(N);
  int comp[N];
  for (int i = 0; i < N; ++i) {
    comps[i].push_back(i);
    comp[i] = i;
  }

  for (int x = 0; x < N; x++) {
    for (int y = 0; y < N; y++) {
      if (fermeture[x][y] == 1 && fermeture[y][x] == 1) {
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
  }
  cout << "Les composantes fortement connexes sont : ";
  for (int i = 0; i < N; i++) {
    int s = comps[i].size();
    if (s > 0) {
      cout << "{";
      for (int j = 0; j < s - 1; j++) {
        cout << comps[i][j] << ", ";
      }
      cout << comps[i][s - 1] << "}, ";
    }
  }
  cout << endl;
}

void affichage(int dist[][N], int chemin[][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << i << " --> " << j << " : ";
      if (dist[i][j] == INF) {
        cout << "pas de chemin" << endl;
      } else {
        cout << dist[i][j] << " -- " << chemin[i][j] << endl;
      }
    }
  }
}

void affichageFermeture(int fermeture[][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << fermeture[i][j] << ", ";
    }
    cout << endl;
  }
}

void itineraire(int i, int j, int chemin[][N]) {
  cout << "L'itineraire est :";
  int current = i;
  while (current != j) {
    cout << " " << current;
    current = chemin[current][j];
  }

  cout << " " << j << endl;
}

int
main() {
  int arc[N][N] = {
    {0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 1},
    {0, 0, 1, 0, 0, 1},
    {0, 0, 1, 0, 0, 0}
  };

  int fermeture[N][N];

  fermeturetransitive(arc, fermeture);
  affichageFermeture(fermeture);
  compfortconnexe(fermeture);
  // int longueur[N][N]={{0, 2, INF, 4, INF},   //Les longueurs des arcs.
	// 	      {INF, 0, INF, INF, INF}, //longueur[i][j]=INF si l'arc ij n'existe pas
	// 	      {INF, INF, 0, 2, INF},
	// 	      {INF, -3, INF, 0, 2},
	// 	      {2, INF, INF, INF, 0}};
  // int dist[N][N];                        //Le tableau des distances.
  // int chemin[N][N];                      //Le tableau de la premiere etape du chemin de i a j.
  // floydWarshall(longueur, dist, chemin);
  // affichage(dist, chemin);
  // int start;
  // int end;
  // cout << "Entrer le depart : ";
  // cin >> start;
  // cout << "Entrer la destination : ";
  // cin >> end;
  // itineraire(start, end, chemin);
  return EXIT_SUCCESS;
}
