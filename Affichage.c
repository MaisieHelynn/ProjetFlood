#include <stdlib.h>
#include <stdio.h>
#include "Lot_A.h"


char couleurs[6] = {'R', 'V', 'B', 'J', 'G', 'M'};

void barre(int n){
	int i;
	printf("     +");
	for (i=0; i<n; i++){
		printf("---+");
	}
	printf("\n");
}



void aff(plateau P){
  
  printf("\n\n\n");
  printf("\n");
  int i;
  int j;
  int n=P.taille;
  for (i=0; i<n; i++){
  	barre(n);
  	printf("     ");
  	for (j=0; j<n; j++){
  		int a=P.contenu[i][j];
  		printf("|%2c ", couleurs[a]);
  		}
  		printf("|");
  		printf("\n");
  	}
  	barre(n);
  	printf("\n\n\n");
  }
