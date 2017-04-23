#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*----------------------------------------------------------------------------------*/
/* On définit le type plateau représenté par une matrice à deux dimensions */
/*----------------------------------------------------------------------------------*/

struct plateau{
  int taille;  /* n = taille de la matrice */
  int **contenu; /* Représente le contenu d'une case */
};

typedef struct plateau plateau;

/*----------------------------------------------------------------------------------*/
/* @requires : Nécessite un entier n qui sera la taille du plateau
   @assigns : Attribue n^2 cases mémoires pour les cases 
   @ensures : Crée une matrice de taille n ne contenant que des 0 */
/*----------------------------------------------------------------------------------*/

plateau new(int n){
  plateau P;
  P.taille=n;
  P.contenu = malloc(sizeof(int *) *n); /* On crée la première dimension de la matrice */
  int i;
  for (i=0; i<n; i++){
  P.contenu[i] = calloc(n, sizeof(int)); /* On crée la deuxième dimension de la matrice */
  }
  return(P);
}

/*----------------------------------------------------------------------------------*/
/* @requires : Nécessite un entier n (taille du plateau), et un nombre de couleurs
   @assigns : Attribue n^2 cases mémoires pour les cases 
   @ensures : Crée un plateau contenant des couleurs aléatoires */
/*----------------------------------------------------------------------------------*/

plateau aleatoire(int n, int couleurs){
  srand(time(NULL)); /* Réinitialise la fonction rand() en fonction de l'heure pour assurer le caractère aléatoire */
  plateau P =new(n);
  int i;
  int j;
  for (i=0; i<n; i++){
    for (j=0;j<n;j++){
      int r=rand(); /* renvoie un nombre aléatoire (très grand...) */
      P.contenu[i][j]=r -((r/couleurs) * couleurs); /* On veut que les aléatoires renvoyés soient inférieurs à couleurs, 
                                                    donc on renvoie le reste de la division euclidienne de r par couleurs */
    };
  };
    return(P);
}

/*----------------------------------------------------------------------------------*/
/* @requires : Nécessite un plateau, une case ([i][j]) et une nouvelle couleur
   @assigns : Modifie une case mémoire du plateau
   @ensures : Renvoie la plateau avec la case [i][j] modifiée */
/*----------------------------------------------------------------------------------*/

plateau changement_couleur(plateau P, int i, int j, int couleur){
  P.contenu[i][j]=couleur;
  return(P);
}

/*----------------------------------------------------------------------------------*/
/* @requires : Nécessite un plateau
   @assigns : Rien
   @ensures : Affiche le plateau */
/*----------------------------------------------------------------------------------*/

int affiche(plateau P){
  int i;
  int j;
  int n=P.taille;
  for (i=0; i<n; i++){
    for (j=0;j<n;j++){
      int c=P.contenu[i][j];
      printf("%i ",c);
    };
    printf("\n");
  };
  return(0);
}

/*----------------------------------------------------------------------------------*/
/* @requires : Nécessite un plateau
   @assigns : Rien
   @ensures : Renvoie TRUE (=1) si le plateau est d'une couleur unique, FALSE (=0) sinon */
/*----------------------------------------------------------------------------------*/

int victoire(plateau P){
	int cond = (0==0);
	int n = P.taille;
	int couleur = P.contenu[0][0];
	int i;
	int j;
	i = 0;
	while (cond && i < n) {
		j = 0;
		while (cond && j < n) {
			if (couleur != P.contenu[i][j]) {
				cond = (0==1);
			}
			j++;
		}
		i++;
	}
	return cond;
}

/* Pour faire des tests */

int main(){
  plateau P=aleatoire(3,4);
  affiche(P);
  changement_couleur(P,2,1,7);
  affiche(P);
  if (victoire(P)) {
    printf("Gagné !\n");
  }
  else {
    printf("Pas gagné...\n");
  }
  /* tableau de 1*1 case, donc sûr de gagner */
  printf("%s", (victoire(aleatoire(1,6))) ? "Gagné !" : "Pas gagné...");
  return(0);
};

