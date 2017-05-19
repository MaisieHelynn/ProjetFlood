#include <SDL/SDL.h>
#include "Lot_A.h"
#include "Lot_B.h"

#include <stdio.h>
#include <stdlib.h>


int main(){
  SDL_Surface *ecran = NULL;
  couleur c;
  int n;
  int tour_max;
  initialisation(&n, &tour_max);
  plateau jeu = aleatoire(n, 6);
  plateau tache = new(n);
  int tour = 0;
  int vict = victoire(jeu);
  ecran=SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("interface graphique", NULL);
  fillScreen(ecran, 0,0,0);
  while (tour < tour_max && !vict) {
    system("clear");
    aff(jeu);
    affiche_plateau(ecran,jeu);

    printf("\nTour : %d sur %d\n\n", tour, tour_max);
    /* ici ********************/
    //if (etape(&jeu, &tache)) {
    //tour++;
    //}
    c=read_couleur(ecran);
    if ((c.r==-1)||(c.g==-1)){
      printf("Abandon de la partie");
      tour=tour_max+1;
    }
    //if (c.r==-1){
    //sauvegarde(jeu, tour, tour_max);     il faut modifier sauvegarder et read couleur
    //printf("partie sauvegardée");
    //

    else if ((c.r==0)&&(c.g==0)&&(c.b==0)){
      // la couleur est noire (entre 2 case)
      printf("veuillez cliquer sur une couleur");
    }
    else{
      if(colorie_tache_graphic(&jeu, &tache, c)==1){
      tour++;}
      else {printf("c'était déjà cette couleur");}
    }

    /**************************/
    vict = victoire(jeu);
  }
  if (vict) {
    system("clear");
    aff(jeu);
    printf("Vous avez gagné en %d coups !\n", tour);
  }
  else {
    //system("clear");
    aff(jeu);
    printf("Perdu...\n");
  }
  supprime(&jeu);
  supprime(&tache);
  return(0);
};
