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
/* On définit le type coordonnees représenté par une matrice de taille 4x2 */
/*----------------------------------------------------------------------------------*/

struct coordonnees{ /* n = taille de la matrice */
  int **contenu; /* Représente le contenu d'une case */
};

typedef struct coordonnees coordonnees;

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
/* @requires : Rien
   @assigns : Attribue n^2 cases mémoires pour les cases 
   @ensures : Crée une matrice de taille 4*2 ne contenant que des 0 */
/*----------------------------------------------------------------------------------*/

coordonnees new_coordonnees(){
  coordonnees C;
  C.contenu = malloc(sizeof(int *) *4); /* On crée la première dimension de la matrice */
  int i;
  for (i=0; i<4; i++){
  C.contenu[i] = calloc(2, sizeof(int)); /* On crée la deuxième dimension de la matrice */
  }
  return(C);
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
/* @requires : Nécessite une matrice de coordonnées
   @assigns : Rien
   @ensures : Affiche la matrice */
/*----------------------------------------------------------------------------------*/

int aff_coord(coordonnees C){
  int i;
  int j;
  for (i=0; i<4; i++){
    for (j=0;j<2;j++){
      int c=C.contenu[i][j];
      printf("%i ",c);
    };
    printf("\n");
  };
  printf("\n");
  return(0);
}

/*----------------------------------------------------------------------------------*/
/* @requires : Nécessite un plateau et une case (x,y)
   @assigns : Rien
   @ensures : Renvoie les coordonnées des cases voisines de (x,y) si elles existent, 
              les remplace par le couple (-1,-1) sinon. La matrice est remplie dans 
              l'ordre suivant : Haut, Gauche, Bas, Droite, en numérotant les lignes
              et colonnes telles qu'on le ferait dans une matrice (ie. l'origine est
              en haut à gauche et on incrémente vers le bas et vers la droite). Dans 
              le couple (a,b), a représente le numéro de ligne, et b celui de colonne. */
/*----------------------------------------------------------------------------------*/

coordonnees voisins(plateau P, int x, int y){
  int n=P.taille;
  coordonnees C=new_coordonnees();
  int i;
  int h=x-1;
  int g=y-1;
  int b=x+1;
  int d=y+1;
  for (i=0;i<4;i++){
    C.contenu[i][0]=-1;
    C.contenu[i][1]=-1;
  }
  if(h>=0){
    C.contenu[0][0]=h;
    C.contenu[0][1]=y;
  }
  if(g>=0){
    C.contenu[1][0]=x;
    C.contenu[1][1]=g;
  }
  if(b<n){
    C.contenu[2][0]=b;
    C.contenu[2][1]=y;
  }
  if(d<n){
    C.contenu[3][0]=x;
    C.contenu[3][1]=d;
  }
return C;
}

/*----------------------------------------------------------------------------------*/
/* @requires : Nécessite un plateau et une case (x,y)
   @assigns : Rien
   @ensures : Renvoie les coordonnées des cases voisines de (x,y) qui sont de même couleur,
              et les remplace par (-1,-1) sinon */
/*----------------------------------------------------------------------------------*/

coordonnees connexe(plateau P, int x, int y){
  coordonnees C=voisins(P,x,y);
  int couleur=P.contenu[x][y];
  int i;
  for (i=0;i<4;i++){
    int a=C.contenu[i][0];
    int b=C.contenu[i][1];
    if (a!=-1 && P.contenu[a][b] != couleur){
      C.contenu[i][0]=-1;
      C.contenu[i][1]=-1;
    }
  }
  return C;
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
/* @requires : Nécessite une matrice de coordonnées
   @assigns : libère l'espace mémoire
   @ensures : rien */
/*----------------------------------------------------------------------------------*/

void sup_coord(coordonnees C){
	int i;
	for (i=0; i<4;i++){
		free((int *)C.contenu[i]);
	}
	free((int**)C.contenu);
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
      else
				{
					int taille= atoi(str);
					plateau p =new(taille);
					int i;
					int j;
					int tmp;
					for (i=0; i<taille; i++){
					  for (j=0; j<taille; j++){
							if (fgets(str, 4, fi) != NULL) {
								tmp=atoi(str); /* mais si c'est pas un entier ? */
		    				if ((tmp==0) && (*str != '0')){
									printf(" Il y a un probleme avec le fichier de sauvegarde"); /* le caractère n'était pas un entier*/
	      					supprime(p); /* on libère la mémoire qu'on occupait car on va renvoyer un autre plateau */
	      					return aleatoire(n, m);
								}
								else{
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
}

/*----------------------------------------------------------------------------------*/
/*structure de pile pour detecter la tache*/
/*----------------------------------------------------------------------------------*/
struct pile_co{
  int taille;  /* taille de la pile : =-1 si la pile est vide  */
  int *x; /* pile des abscisses*/
	int *y; /* pile des ordonnées */
};

typedef struct pile_co pile;

/*----------------------------------------------------------------------------------*/
/* @requires : un entier n>0
   @assigns : Alloue n cases mémoires pour la pile ATTENTION: la pile devra etre de taille suffisemment grande
   @ensures : La ("double")pile */
/*----------------------------------------------------------------------------------*/
pile new_pile (int n){
	pile p;
	pile.taille=-1;
	p.x =malloc(sizeof(int) *n);
	p.y =malloc(sizeof(int) *n);
}

/*----------------------------------------------------------------------------------*/
/* @requires : une pile pi
   @assigns : libere la memoire d'une pile
   @ensures : Rien*/
/*----------------------------------------------------------------------------------*/
void supprime_pi(pile pi){
	free((int*)pi.x);
	free((int*)pi.y);
}

/*----------------------------------------------------------------------------------*/
/* @requires : une pile pi et 2 entiers correspondants aux coordonées
   @assigns : ajoute le couple d'element et incrémente la taille de la pile
   @ensures : Rien*/
/*----------------------------------------------------------------------------------*/
void ajout(pile pi, int x, int y){
	pi.taille=pi.taille+1;
	pi.x[pi.taille]=x;
	pi.y[pi.taille]=y;
}
	
/*----------------------------------------------------------------------------------*/
/* @requires : p un plateau correspondant au plateau de jeu et t un autre plateau qui correspond a l'ancienne tache (t[i][j]==1 si ce point appartient a la tache et 0 sinon)
   @assigns : Alloue la memoire pour une pile puis la detruit; modifie la matrice de la tache
   @ensures : La nouvelle tache  */
/*----------------------------------------------------------------------------------*/
plateau tache(plateau p, plateau t){
	couleur=p[0][0];
	n=p.taille;
	pi=new_pile(n*n);
	ajout(pi,1,1);
	while (pi.taille > -1){
		/* on recupere le premier element de la pile */
		abs=pi.x[pi.taille];
		ord=pi.y[pi.taille];
		pi.taille=pi.taille - 1;
		/* on l'ajoute a la tache */
		t[abs][ord]=1;
		/* a droite */
		if(abs<(n-1))
		{ 
			if ((couleur==p[abs+1][ord]) && (t[abs+1][ord]==0))
			{ ajout(pi, abs+1, ord)
			}
		}
		/* a gauche */
		if(abs>1)
		{ 
			if ((couleur==p[abs+-1][ord]) && (t[abs-1][ord]==0))
			{ ajout(pi, abs-1, ord)
			}
		}
		/* en haut */
		if(ord>0)
		{ 
			if ((couleur==p[abs][ord-1]) && (t[abs][ord-1]==0))
			{ ajout(pi, abs, ord-1)
			}
		}
		/* en bas */
		if(ord<(n-1))
		{ 
			if ((couleur==p[abs][ord+1]) && (t[abs][ord+1]==0))
			{ ajout(pi, abs, ord+1)
			}
		}
	}
	supprime_pi(pi);
	return t;
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
	/* TESTS PLATEAU */
  plateau p_2 = reprise(1,1);
  affiche(p_2);
  plateau P=aleatoire(3,4);
  affiche(P);
	/* TESTS VOISINS ET COULEURS */
  coordonnees V=voisins(P,1,1);
  aff_coord(V);
  coordonnees C=connexe(P,1,1);
  aff_coord(C);
  changement_couleur(P,2,1,18);
  affiche(P);
	/* TESTS VICTOIRE */
  if (victoire(P)) {
    printf("Gagné !\n");
  }
  else {
    printf("Pas gagné...\n");
  }
  /* tableau de 1*1 case, donc sûr de gagner */
  printf("%s", (victoire(aleatoire(1,6))) ? "Gagné !" : "Pas gagné...");
	
	/* TESTS INITIALISATION FICHIER + SAUVEGARDE + SUPPRESSION */
  sauvegarder(P);
  supprime(P);
  affiche(P);/* ca affiche n'importe quoi -> normal car la memoire de P a été libérée */
  plateau t=reprise(0,0);
  affiche(t);
  return(0);
};
