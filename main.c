#include <SDL/SDL.h>
#include "Lot_A.h"
#include "Lot_B.h"
#include "solveur_omega.h"
#include "ipi2_interface.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
  couleur c;
  int n;
  int tour_max;
  char res;
  plateau jeu;
  plateau tache;
	FILE* fi = fopen("sauvegarde_partie.txt", "r");
  if (fi != NULL){
    printf (" Voulez-vous reprendre la partie sauvegardée?\n OUI : taper o\n NON : taper n\n");
    scanf("%c",&res);
    if (res == 'o') {
      jeu = reprise(10, 6);
      tache = new(jeu.taille);
	  n = jeu.taille;
    }
    else {
      initialisation(&n, &tour_max);
      jeu = aleatoire(n, 6);
      tache = new(n);
    }
  }
  else {
    initialisation(&n, &tour_max);
    jeu = aleatoire(n, 6);
    tache = new(n);
  }
  
  tour_max = -1;
  pile_couleur pc= new_pile_couleur(n*n);
  int limite = 0;
  solveur_opti(jeu, &tour_max, &pc, tache, &limite);
  int tour = 0;
  int vict = victoire(jeu);
  SDL_Surface *ecran = NULL;
  ecran=SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("interface graphique", NULL);
  fillScreen(ecran, 0,0,0);
  while (tour < tour_max && !vict) {
    system("clear");
    aff(jeu);
    printf("\nTour : %d sur %d\n\n", tour, tour_max);
    affiche_plateau(ecran,jeu);

    /* ici ***
    //if (etape(&jeu, &tache)) {
    //tour++;
    //}
	*/
    c=read_couleur(ecran);
	if ((c.r==-1)||(c.g==-1)){
		printf("Abandon de la partie\n");
		tour=tour_max+1;
		if (c.g==-1){
			sauvegarder(&jeu);
			printf("Partie sauvegardée\n");
		}
	}
    else if ((c.r==0)&&(c.g==0)&&(c.b==0)){
	/* la couleur est noire (entre 2 case) */
      printf("veuillez cliquer sur une couleur");
    }
    else{
      if(colorie_tache_graphic(&jeu, &tache, c)==1){
      tour++;}
      else {printf("c'était déjà cette couleur");}
    }
    vict = victoire(jeu);
  }
  if (vict) {
    system("clear");
    aff(jeu);
    printf("Vous avez gagné en %d coups !\n", tour);
  }
  else {
    aff(jeu);
	if (c.g!=-1){
		printf("Perdu...\n");
	}
  }
  supprime(&jeu);
  supprime(&tache);
  supprime_pile(&pc);
  if(fi != NULL){
	  fclose(fi);
  }
  return(0);
};
