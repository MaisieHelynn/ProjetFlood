/*!
* \file  ipi2_interface.c
* \brief Lot D du Flood
* \date 21 Mai 2017
* \author {AMSELLEM Elyne, CHOLLET Simon, JAMOUS Remi, MEHENNI Sylia}
*/


#include <SDL/SDL.h>
#include "Lot_A.h"
#include "Lot_B.h"

#include <stdio.h>
#include <stdlib.h>



/*----------------------------------------------------------------------------------*/
/*!
* \brief la ligne de commande sous linux : gcc ipi2_interface.c Lot_A.c Lot_B.c -o interface -Wall -Wextra -lSDL    -> et ca marche(avec la librarie sdl)
* \brief compilation sous Linux : gcc -o exSDL exSDL.c -lSDL
* \brief compilation sur Mac : gcc -o test -I/Library/Frameworks/SDL.framework/Headers ipi2_interface.c Lot_A.c Lot_B.c SDLmain.m -framework SDL -framework Cocoa
*/
/*----------------------------------------------------------------------------------*/




struct couleur {
  int r;
  int g;
  int b;
};

typedef struct couleur couleur;

/*----------------------------------------------------------------------------------*/
/*!
* \fn couleur determine_couleur(int n)
* \param Nécessite un entier n>1 qui sera associé à une couleur
* \return un objet de type couleur
* \brief pour le moment il n'y a que 6 couleurs
*/
/*----------------------------------------------------------------------------------*/
couleur determine_couleur(int n){
  couleur c;
  c.r=255;
  c.g=255;
  c.b=255;
  switch (n) {
  case 0:
    c.r=255;
    c.g=0;
    c.b=0;
    break;
  case 1:
    c.r=0;
    c.g=255;
    c.b=0;
    break;
  case 2:
    c.r=0;
    c.g=0;
    c.b=255;
    break;
  case 3:
    c.r=255;
    c.g=255;
    c.b=0;
    break;
  case 4:
    c.r=100;
    c.g=100;
    c.b=100;
    break;
  case 5:
    c.r=100;
    c.g=50;
    c.b=0;
    break;
  }
  return c;
}

/*----------------------------------------------------------------------------------*/
/*!
* \fn void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b)
* \param écran SDL, 2 entiers pour les coordonnées du point supérieur gauche du carré à tracer, int pour la taille du carré, 3 int pour les couleurs
* \return none
* \brief px, py coordonnées haut, gauche du pixel
*/
/*----------------------------------------------------------------------------------*/
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) {
    SDL_Rect rect;
    rect.x=px;
    rect.y=py;
    rect.h=rect.w=size;
    SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, r, g, b));
}

/*----------------------------------------------------------------------------------*/
/*!
* \fn void affiche_carre(SDL_Surface *ecran, int x, int y, plateau p, int div)
* \param écran SDL, 2 entiers pour la position, int pour diviser la taille des cases selon le nb de cases, un plateau de jeu
* \return none
* \brief div permet d'adapter la taille des cases du jeu en fonction du nombre de cases demandé par l'utilisateur
*/
/*----------------------------------------------------------------------------------*/
void affiche_carre(SDL_Surface *ecran, int x, int y, plateau p, int div){
  int i = p.contenu[x][y];
  couleur c = determine_couleur(i);
  drawRectangle(ecran, ((8+(64+8)*y)/div), ((8+(64+8)*x)/div), (64/div), c.r, c.g, c.b);
}

/*----------------------------------------------------------------------------------*/
/*!
* \fn void affiche_plateau(SDL_Surface *ecran, plateau p)
* \param écran SDL, un plateau de jeu
* \return none
*/
/*----------------------------------------------------------------------------------*/
void affiche_plateau(SDL_Surface *ecran, plateau p){
  int taille=p.taille;
  int x;
  int y;
  int div;
  if (taille < 9) div =1;
  else if (taille < 17) div =2;
  else if (taille < 33) div =4;
  else div =8;
  for (x=0; x<taille; x++){
    for (y=0; y<taille; y++){
      affiche_carre(ecran, x, y, p, div);
    }
  }
  SDL_Flip(ecran);
}

/*----------------------------------------------------------------------------------*/
/*!
* \fn void fillScreen(SDL_Surface *ecran, int r, int g, int b)
* \param écran SDL, 3 int pour les couleurs
* \return none
* \brief fonction fournie
*/
/*----------------------------------------------------------------------------------*/
void fillScreen(SDL_Surface *ecran, int r, int g, int b) {
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}


/*----------------------------------------------------------------------------------*/
/*!
* \fn couleur read_couleur(SDL_Surface *ecran){
* \param écran SDL
* \return une couleur, après une conversion de l'entier contenu dans la matrice de jeu
* \brief si la fenetre est fermee : r=-1, si on appuie sur q ou echap : g=-1
*/
/*----------------------------------------------------------------------------------*/
couleur read_couleur(SDL_Surface *ecran){
  couleur res;
  res.r=0;
  res.g=0;
  res.b=0;
  SDL_Event event;
  SDL_WaitEvent(&event);
  switch(event.type) {
  case SDL_QUIT:
    res.r=-1;
    break;
  case SDL_KEYDOWN: /* gestion des évènements clavier*/
    switch (event.key.keysym.sym) {
    case SDLK_q:
    case SDLK_ESCAPE:
      res.r=-1;
      break;
	  case SDLK_s:
	  res.g=-1;
	  break;
    default :
      break;
    }
	break;
  case SDL_MOUSEBUTTONDOWN:
    if (event.button.button == SDL_BUTTON_LEFT) {
      int x,y;
      x = event.button.x ;
      y = event.button.y ;
      int bpp = ecran->format->BytesPerPixel;
      /* Here p is the address to the pixel we want to retrieve */
      Uint8 *p = (Uint8 *)ecran->pixels + y*ecran->pitch + x*bpp;
      /* should be p[0], p[1], p[2] ...*/
      fprintf(stderr,"%d %d -> %d %d %d\n",y, x, p[1], p[2], p[3]);
      res.r=p[1];
      res.g=p[2];
      res.b=p[3];
    }
  default :
    break;
  }
  return res;
}

/*----------------------------------------------------------------------------------*/
/*!
* \fn int colorie_tache_graphic(plateau *p, plateau *t, couleur c )
* \param 2 plateaux pour le jeu et la tache, un objet de type couleur
* \return un bool (entier O si false, autre chose que 0 si true)
* \brief permet de convertir l'objet couleur en entier afin de faire appel à la fonction colorie_tache
*/
/*----------------------------------------------------------------------------------*/
int colorie_tache_graphic(plateau *p, plateau *t, couleur c ){
  int co;
  if((c.r==255)&&(c.g==0)&&(c.b==0)){co=0;}
  if((c.r==0)&&(c.g==255)&&(c.b==0)){co=1;}
  if((c.r==0)&&(c.g==0)&&(c.b==255)){co=2;}
  if((c.r==255)&&(c.g==255)&&(c.b==0)){co=3;}
  if((c.r==100)&&(c.g==100)&&(c.b==100)){co=4;}
  if((c.r==100)&&(c.g==50)&&(c.b==0)){co=5;}
  if (co==(p->contenu[0][0])){
	  return (1==0);
  } // la nouvelle couleur correspond a la couleur de la tache actuelle
  else {
  	colorie_tache(p, t, co);
  return (0==0);
  }
}
