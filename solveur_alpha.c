/*!
* \file  solveur_alpha.c
* \brief Solveur
* \date 15 Mai 2017
* \author {AMSELLEM Elyne, CHOLLET Simon, JAMOUS Remi, MEHENNI Sylia}
*/

#include "Lot_A.h"
#include "Lot_B.h"
#include <stdio.h>
#include <stdlib.h>

/*----------------------------------------------------------------------------------*/
/*! 
* \struct pile_couleur
* \brief 0 faux et !=0 vrai en c */
*/
/*----------------------------------------------------------------------------------*/

 struct pile_couleur {
   int taille;
   int *element;
 };

typedef struct pile_couleur pile_couleur;

pile_couleur new_pile_couleur(int n) {
  pile_couleur pc;
  pc.taille=-1;
  pc.element=malloc(sizeof(int)*n);
  return pc;
}

/*----------------------------------------------------------------------------------*/
/*! 
* \fn est_vide(pile_couleur pc)
* \param Nécessite une pile pc
* \return Vrai si la pile est vide, Faux sinon
*/
/*----------------------------------------------------------------------------------*/

int est_vide(pile_couleur pc) {
  return(pc.taille==-1);
}

/*----------------------------------------------------------------------------------*/
/*! 
* \fn depile(pile_couleur *pc)
* \param Nécessite une pile *pc
* \return Enlève le sommet de la pile
*/
/*----------------------------------------------------------------------------------*/

/* rappel : on suppose pile non vide */
int depile(pile_couleur *pc)  {/* pile* p : elt de type pointeur vers pile
pile *p: type et pointeur  (implique )*/
  pc->taille=pc->taille-1;
  return(pc->element[pc->taille+1]);
}

/*----------------------------------------------------------------------------------*/
/*! 
* \fn empile(pile_couleur *pc, int element)
* \param Nécessite une pile *pc et un élément
* \return Rien : Ajoute l'élément au sommet de la pile
*/
/*----------------------------------------------------------------------------------*/

/* on suppose que la pile en argument n'est pas pleine */
void empile(pile_couleur *pc, int element) {
  pc->taille=pc->taille+1;
  pc->element[pc->taille]=element;
}

/*----------------------------------------------------------------------------------*/
/*! 
* \fn supprime_pile(pile_couleur *pc)
* \param Nécessite une pile *pc
* \return Rien : Supprime la pile (libère l'espace mémoire alloué)
*/
/*----------------------------------------------------------------------------------*/

void supprime_pile(pile_couleur *pc) {
  free((int*)pc->element);
}

/*----------------------------------------------------------------------------------*/
/*! 
* \fn trouve(pile_couleur *pc)
* \param Nécessite une pile *pc
* \return Rien :  trouve une solution au problème
*/
/*----------------------------------------------------------------------------------*/

void trouve(pile_couleur *pc) {
  char couleurs[6];
  couleurs[0]='r';
  couleurs[1]='v';
  couleurs[2]='b';
  couleurs[3]='j';
  couleurs[4]='g';
  couleurs[5]='m';
  int tmp;
  pile_couleur stock;
  stock = new_pile_couleur(pc->taille+1);
  while(!est_vide(*pc)) {
    empile(&stock, depile(pc));
  }
  printf("On a trouvé une solution\n");
  while(!est_vide(stock)) {
    tmp=depile(&stock);
    printf("%c ",couleurs[tmp]);
    empile(pc, tmp);
  }
  printf("\n\n");
  supprime_pile(&stock);
}

/*----------------------------------------------------------------------------------*/
/*! 
* \fn comparaison_plateau(plateau p1, plateau p2)
* \param Nécessite deux plateaux
* \return Renvoie Vrai si les deux plateaux sont égaux, Faux sinon
*/
/*----------------------------------------------------------------------------------*/

int comparaison_plateau(plateau p1, plateau p2) {
  int n = p1.taille;
  int i;
  int j;
  for (i=0;i<n;i++) {
    for(j=0;j<n;j++) {
      if ((p1.contenu[i][j] != p2.contenu[i][j])) {
        return (0==1);
      }
    }
  }
  return (1==1);
}

/*----------------------------------------------------------------------------------*/
/*! 
* \fn solveur_beta(plateau copie, int *nb_coups, pile_couleur *pc, plateau copie_tache)
* \param un plateau, un entier (nombre de coups), une pile et une tache colorée
* \return Rien : Solveur
*/
/*----------------------------------------------------------------------------------*/

void solveur_beta(plateau copie, int *nb_coups, pile_couleur *pc, plateau copie_tache) {
  int t = pc->taille;
  if (victoire(copie)) {
	  trouve(pc);
	  *nb_coups=pc->taille;
  }
  else {
	  if(*nb_coups==-1 || t+1 < (*nb_coups)) {
    	  int i;
    	  plateau nouveau = new(copie.taille);
    	  plateau nouvelle_tache = new(copie.taille);
		for (i=0;i<6;i++) {
      		int j;
      	  	int k;
      		for (j=0; j<nouveau.taille;j++) {
        		for (k=0; k<nouveau.taille;k++) {
         			 nouveau.contenu[j][k] = copie.contenu[j][k];
        		}
	     	}
			for (j=0; j<nouveau.taille;j++) {
	       		for (k=0; k<nouveau.taille;k++) {
					nouvelle_tache.contenu[j][k] = copie_tache.contenu[j][k];
				}
			}
	     	colorie_tache(&nouveau, &nouvelle_tache, i);
	     	colorie_tache(&nouveau, &nouvelle_tache, i);
	     	if(!comparaison_plateau(nouvelle_tache, copie_tache)) {
	       		empile(pc, i);
	         	solveur_beta(nouveau, nb_coups, pc, nouvelle_tache);
				depile(pc);
			}
	     }
		 supprime(&nouveau);
    	 supprime(&nouvelle_tache);
	}
  }
}

int main() {
  int n = 4;
  plateau jeu = aleatoire(n, 6);
  plateau tache = new(n);
  pile_couleur pc;
  tache.contenu[0][0] = 1;
  pc = new_pile_couleur(n*n);
  int nb_coups=-1;
  aff(jeu);
  solveur_beta(jeu, &nb_coups, &pc, tache);
  supprime(&jeu);
  supprime(&tache);
  supprime_pile(&pc);
  return(0);
}
