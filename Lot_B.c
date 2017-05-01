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
	printf("Veuillez entrer la taille du plateau de jeu :\n");
	ret = scanf("%d", n);
	
	while (*n < 1 || *n > 100) {
		if (ret != 1) {
			while(getchar() != '\n');
			printf("Ce n'est pas un nombre, veuillez entrer la taille du plateau de jeu :\n");
		}
		else {
			printf("Ce n'est pas un nombre valide, veuillez entrer un nombre entre 1 et 100 :\n");
		}
		ret = scanf("%d", n);
	}
	printf("Le plateau est de taille %d.\n", *n);
	
	ret = 0;
	*tour_max = -1;
	printf("Veuillez entrer le nombre de coups maximum :\n");
	ret = scanf("%d", tour_max);
	
	while (*tour_max < 1 || *tour_max > 1000) {
		if (ret != 1) {
			while(getchar() != '\n');
			printf("Ce n'est pas un nombre, veuillez entrer le nombre de coups maximum :\n");
		}
		else {
			printf("Ce n'est pas un nombre valide, veuillez entrer un nombre entre 1 et 1000 :\n");
		}
		ret = scanf("%d", tour_max);
	}
	printf("Le plateau est de taille %d.\n", *tour_max);
}

char couleurs[6] = {'R', 'V', 'B', 'J', 'G', 'M'};

void barre(int n){
	int i;
	printf("+");
	for (i=0; i<n; i++){
		printf("---+");
	}
	printf("\n");
}

void aff(plateau P){
	printf("\n");
	int i;
	int j;
	int n=P.taille;
	for (i=0; i<n; i++){
		barre(n);
		for (j=0; j<n; j++){
			int a=P.contenu[i][j];
			printf("|%2c ", couleurs[a]);
		}
			printf("|");
			printf("\n");
	}
	barre(n);
	printf("\n");
}

int etape(plateau *P, plateau *T) {
  char c;
  int couleur = -1;
  char buffer[2]; /* 2 car 1 caractère PLUS le \0 des chaînes */
  printf("Choisir une couleur :\n(B) pour bleu\n(R) pour rouge\n(G) pour gris\n(M) pour marron\n(J) pour jaune\n(V) pour vert\n");
  scanf("%1s", buffer);
  c=buffer[0];
  switch (c) {
    case 'B':
    case 'b':
    couleur=2;
    break;
    case 'V':
    case 'v':
    couleur=1;
    break;
    case 'R':
    case 'r':
    couleur=0;
    break;
    case 'G':
    case 'g':
    couleur=4;
    break;
    case 'J':
    case 'j':
    couleur=3;
    break;
    case 'M':
    case 'm':
    couleur=5;
    break;
    default: printf("Ce n'est pas une couleur valable.");
    break;
  }
  if(couleur > -1 && P->contenu[0][0] != couleur) {
	  colorie_tache(P,T,couleur);
	  return (1==1);
  }
  else {
	  return (1==0);
  }
  return(1==0);
}
