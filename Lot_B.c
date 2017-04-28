/*!
* \file  Lot_B.c
* \brief Lot B du Flood
* \date 02 Mai 2017
* \author {AMSELLEM Elyne, CHOLLET Simon, JAMOUS Remi, MEHENNI Sylia}
*/

#include "Lot_A.h"
#include <stdio.h>
#include <stdlib.h>

void initialisation(int* n, int* tour_max) {
	int ret = 0;
	*n = -1;
	printf("Veuillez rentrer la taille du plateau de jeu :\n");
	ret = scanf("%d", n);
	
	while (*n < 1 || *n > 100) {
		if (ret != 1) {
			while(getchar() != '\n');
			printf("Ce n'est pas un nombre, veuillez rentrer la taille du plateau de jeu :\n");
		}
		else {
			printf("Ce n'est pas un nombre valide, veuillez rentrer un nombre entre 1 et 100 :\n");
		}
		ret = scanf("%d", n);
	}
	printf("Le plateau est de taille %d.\n", *n);
	
	ret = 0;
	*tour_max = -1;
	printf("Veuillez le nombre de tours maximum :\n");
	ret = scanf("%d", tour_max);
	
	while (*tour_max < 1 || *tour_max > 1000) {
		if (ret != 1) {
			while(getchar() != '\n');
			printf("Ce n'est pas un nombre, veuillez rentrer le nombre de tours maximum :\n");
		}
		else {
			printf("Ce n'est pas un nombre valide, veuillez rentrer un nombre entre 1 et 1000 :\n");
		}
		ret = scanf("%d", tour_max);
	}
	printf("Le plateau est de taille %d.\n", *tour_max);
}