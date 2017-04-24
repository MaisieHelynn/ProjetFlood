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
/* @requires : Nécessite un entier n >0 qui sera la taille du plateau
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
/* @requires : Nécessite un entier n >0  (taille du plateau), et un nombre de couleurs >0
   @assigns : Attribue n^2 cases mémoires pour les cases 
   @ensures : Crée un plateau contenant des couleurs aléatoires */
/*----------------------------------------------------------------------------------*/

plateau aleatoire(int n, int couleurs){
  /* srand(time(NULL)); /* Réinitialise la fonction rand() en fonction de l'heure pour assurer le caractère aléatoire */
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
   @ensures : Rien  */
/*----------------------------------------------------------------------------------*/

void changement_couleur(plateau P, int i, int j, int couleur){
  P.contenu[i][j]=couleur;
}

/*----------------------------------------------------------------------------------*/
/* @requires : Nécessite un plateau
   @assigns : Rien
   @ensures : Affiche le plateau */
/*----------------------------------------------------------------------------------*/

void affiche(plateau P){
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
    printf("\n");  
}


/*----------------------------------------------------------------------------------*/
/* @requires : Nécessite un plateau
   @assigns : libère l'espace mémoire
   @ensures : rien */
/*----------------------------------------------------------------------------------*/
void supprime(plateau P){
  int n=P.taille;
  int i;
  for (i=0;i<n;i++){
    free((int*)P.contenu[i]);
  }
  free((int**)P.contenu);
}
  
/*----------------------------------------------------------------------------------*/
/* @requires : Nécessite un plateau
   @assigns : Sauvegarde le plateau dans un fichier : la première ligne correspond à la taille,
ATTENTION : si une sauvegarde était présente elle sera écrasée, le fichier sera créer si besoin
   le plateau est toujours en mémoire
   @ensures : */
/*----------------------------------------------------------------------------------*/
void sauvegarder(plateau p){
  FILE* fi = fopen( "sauvegarde_partie.txt", "w+" );
  if (fi == NULL)
    { printf (" la sauvegarde n'a pas fonctionnée ");}
  else
    { int n= p.taille;
      fprintf(fi, "%i\n", n); /* on stock la taille du plateau*/
      int i;
      int j;
      for (i=0; i<n; i++){
	for (j=0;j<n;j++){
	  fprintf(fi,"%i\n",p.contenu[i][j]); /* on ecrit un caractère par ligne ( ça permettra une lecture plus facile: une ligne correspond à un entier, on a pas à ce soucier des entiers à plusieurs chiffres ) */
	};
      };  
      fclose(fi);
    };
};


/*----------------------------------------------------------------------------------*/
/* @requires : de préférence un fichier sauvegarde_partie.txt, s'il n'y en a pas la fonction renvera un plateau aléatoire de taille n avec m couleurs
   Remarque : la sauvegarde doit correspondre a un plateau de taille et de nombre de couleurs inférieur à 100 
   @assigns : Récupère le plateau sauvegardé dans un fichier sans le modifier
   @ensures : le plateau enregistré ( si présent ) ou un plateau aléatoire s'il n'y avait pas de fichier ou un probleme */
/*----------------------------------------------------------------------------------*/

plateau reprise(int n, int m){
  FILE* fi = fopen( "sauvegarde_partie.txt", "r" );
  if (fi == NULL)
    { printf (" Aucun fichier de sauvegarde trouvé ");
      return aleatoire(n, m);
    }
  else
    { char str[4];/* on suppose que la taille et le nombre de couleurs ne dépassent pas 99 , il faut prévoir 2 caracteres suplémentaires pour le \n de fin de ligne */
      if(fgets(str, 4, fi)==NULL) {
	printf(" Il y a un probleme avec le fichier de sauvegarde");/* la taille du plateau n'a pas pu etre lue */
	return aleatoire(n, m);
      }
      else{
	int taille= atoi(str);
	plateau p =new(taille);
	int i;
	int j;
	int tmp;
	for (i=0; i<taille; i++){
	  for (j=0; j<taille; j++){
	    if (fgets(str, 4, fi) != NULL) {
	      tmp=atoi(str); /* mais si c'est pas un entier ? */
	      changement_couleur(p, i, j, tmp);
	    }
	    else {
	      printf(" Il y a un probleme avec le fichier de sauvegarde");
	      supprime(p); /* on libère la mémoire qu'on occupait car on va renvoyer un autre plateau */
	      return aleatoire(n, m);
	    }
	  }
	}
	return p;
      }      
    }
}
	
	      
  

/* Pour faire des tests */

int main(){
  plateau p_2 = reprise(1,1);
  affiche(p_2);
  plateau P=aleatoire(3,4);
  affiche(P);
  changement_couleur(P,2,1,18);
  affiche(P);
  sauvegarder(P);
  supprime(P);
  affiche(P);/* ca affiche n'importe quoi -> normal car la memoire de P a été libérée */
  plateau t=reprise(0,0);
  affiche(t);
  return(0);
};
