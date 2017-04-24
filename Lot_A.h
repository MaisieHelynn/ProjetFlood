#ifndef LOTA
#define LOTA

struct plateau{
  int taille;  /* n = taille de la matrice */
  int **contenu; /* Représente le contenu d'une case */
};

typedef struct plateau plateau;

struct coordonnees{ /* n = taille de la matrice */
  int **contenu; /* Représente le contenu d'une case */
};

typedef struct coordonnees coordonnees;

plateau new(int n);

coordonnees new_coordonnees();

plateau aleatoire(int n, int couleurs);

void changement_couleur(plateau P, int i, int j, int couleur);

void affiche(plateau P);

int aff_coord(coordonnees C);

coordonnees voisins(plateau P, int x, int y);

coordonnees connexe(plateau P, int x, int y);

void supprime(plateau P);

void sup_coord(coordonnees C);

void sauvegarder(plateau p);

plateau reprise(int n, int m);

int victoire(plateau P);

#endif