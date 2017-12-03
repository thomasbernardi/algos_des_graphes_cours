#include <iostream>
#include <vector>

using namespace std;

const int N=5;
const int INF=9999;                      //La valeur infinie.

void floydWarshall(int longueur[][N],int dist[][N],int chemin[][N]);
void affichage(int dist[][N],int chemin[][N]);
void itineraire(int i,int j,int chemin[][N]);

int
main()
{

  int longueur[N][N]={{0,2,INF,4,INF},   //Les longueurs des arcs.
		      {INF,0,2,INF,INF}, //longueur[i][j]=INF si l'arc ij n'existe pas
		      {INF,INF,0,2,INF},
		      {INF,-3,INF,0,2},
		      {2,INF,INF,INF,0}};
  int dist[N][N];                        //Le tableau des distances.
  int chemin[N][N];                      //Le tableau de la premiere etape du chemin de i a j.
  floydWarshall(longueur,dist,chemin);
  affichage(dist,chemin);
  return EXIT_SUCCESS;
}
