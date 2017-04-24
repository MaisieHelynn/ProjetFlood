#include "Lot_A.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	/* TESTS PLATEAU */
  plateau p_2 = reprise(1,1);
  affiche(p_2);
  plateau P=aleatoire(3,4);
  affiche(P);
	/* TESTS COULEURS */
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
