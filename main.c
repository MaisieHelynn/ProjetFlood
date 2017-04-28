#include "Lot_A.h"
#include "Lot_B.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	int n;
	int tour_max;
	initialisation(&n, &tour_max);
	plateau jeu = aleatoire(n, 6);
	plateau tache = new(n);
	int tour = 0;
	int vict = victoire(jeu);
	while (tour < tour_max && !vict) {
		system("clear");
		aff(jeu);
		printf("\nTour : %d sur %d\n\n", tour, tour_max);
		if (etape(&jeu, &tache)) {
			tour++;
		}
		vict = victoire(jeu);
	}
	if (vict) {
		system("clear");
		aff(jeu);
		printf("Vous avez gagné en %d coups !\n", tour);
	}
	else {
		system("clear");
		aff(jeu);		
		printf("Perdu...\n");
	}
	supprime(&jeu);
	supprime(&tache);
	return(0);
};
