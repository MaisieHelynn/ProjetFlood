#ifndef LOT_A
#define LOT_A

struct plateau{
  int taille;  /* n = taille de la matrice */
  int **contenu; /* Représente le contenu d'une case */
};

typedef struct plateau plateau;

plateau new(int n);

plateau aleatoire(int n, int couleurs);

void changement_couleur(plateau P, int i, int j, int couleur);

void affiche(plateau P);

void supprime(plateau P);

void sauvegarder(plateau p);

plateau reprise(int n, int m);

struct pile{
  int taille;  /* taille de la pile : =-1 si la pile est vide  */
  int *x; /* pile des abscisses*/
  int *y; /* pile des ordonnées */
};

typedef struct pile pile;

pile new_pile (int n);

void supprime_pi(pile pi);

void ajout(pile pi, int x, int y);

plateau tache(plateau p, plateau t);

int victoire(plateau P);

void colorie_tache(plateau p, plateau t, int c );

#endif
