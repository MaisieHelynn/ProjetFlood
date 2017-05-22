#ifndef solveur_omega
#define SOLVEUR_OMEGA


struct pile_couleur {
  int taille;
  int *element;
};

typedef struct pile_couleur pile_couleur;

pile_couleur new_pile_couleur(int n);
int est_vide(pile_couleur pc);
int depile(pile_couleur *pc);
void empile(pile_couleur *pc, int element);
void supprime_pile(pile_couleur *pc);
void trouve(pile_couleur *pc);
int comparaison_plateau(plateau p1, plateau p2);
int somme(plateau p);
void tri(int tab[], int res[]);
void solveur_opti(plateau copie, int *nb_coups, pile_couleur *pc, plateau copie_tache);

#endif
