#include <iostream>
#include <vector>

using namespace std;

const int N=5;
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

void affichage(int dist[][N],int chemin[][N]) {
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
void itineraire(int i,int j,int chemin[][N]);

int
main() {

  int longueur[N][N]={{0, 2, INF, 4, INF},   //Les longueurs des arcs.
		      {INF, 0, INF, INF, INF}, //longueur[i][j]=INF si l'arc ij n'existe pas
		      {INF, INF, 0, 2, INF},
		      {INF, -3, INF, 0, 2},
		      {2, INF, INF, INF, 0}};
  int dist[N][N];                        //Le tableau des distances.
  int chemin[N][N];                      //Le tableau de la premiere etape du chemin de i a j.
  floydWarshall(longueur, dist, chemin);
  affichage(dist, chemin);
  return EXIT_SUCCESS;
}
