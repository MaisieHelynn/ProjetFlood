#ifndef IPI2_INTERFACE
#define IPI2_INTERFACE

struct couleur {
  int r;
  int g;
  int b;
};

typedef struct couleur couleur;

couleur determine_couleur(int n);
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b);
void affiche_carre(SDL_Surface *ecran, int x, int y, plateau p, int div);
void affiche_plateau(SDL_Surface *ecran, plateau p);
void fillScreen(SDL_Surface *ecran, int r, int g, int b);
couleur read_couleur(SDL_Surface *ecran);
int colorie_tache_graphic(plateau *p, plateau *t, couleur c);

#endif