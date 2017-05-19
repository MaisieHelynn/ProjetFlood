#include <SDL/SDL.h>
#include "Lot_A.h"
#include "Lot_B.h"

#include <stdio.h>
#include <stdlib.h>

// la ligne de commande sous linux : gcc ipi2_interface.c Lot_A.c Lot_B.c -o interface -Wall -Wextra -lSDL    -> et ca marche(avec la librarie sdl)


/*
 compilation sous Linux : gcc -o exSDL exSDL.c -lSDL
 compilation sur Mac : gcc -o test -I/Library/Frameworks/SDL.framework/Headers ipi2_interface.c Lot_A.c Lot_B.c SDLmain.m -framework SDL -framework Cocoa
*/

int autoDraw=0;

struct couleur {
  int r;
  int g;
  int b;
};

typedef struct couleur couleur;

/*pour le moment il n'y a que 6 couleurs*/
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


/* px, py coordonnées haut, gauche du pixel*/
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) {
    SDL_Rect rect;
    rect.x=px;
    rect.y=py;
    rect.h=rect.w=size;
    SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, r, g, b));
}


void affiche_carre(SDL_Surface *ecran, int x, int y, plateau p, int div){
  int i = p.contenu[x][y];
  couleur c = determine_couleur(i);
  drawRectangle(ecran, ((8+(64+8)*x)/div), ((8+(64+8)*y)/div), (64/div), c.r, c.g, c.b);
}

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

void fillScreen(SDL_Surface *ecran, int r, int g, int b) {
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}

/* si la fenetre est fermee : r=-1 */
/* si on appuie sur q ou echap : g=-1 */

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
      res.g=-1;
      break;
      // on pourrait rajouter la sauvegarde de la partie avec la touche s
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
  printf("%d %d %d",res.r, res.g, res.b);
  return res;
}
  
int colorie_tache_graphic(plateau *p, plateau *t, couleur c ){
  int co;
  if((c.r==255)&&(c.g==0)&&(c.b==0)){co=0;}
  if((c.r==0)&&(c.g==255)&&(c.b==0)){co=1;}
  if((c.r==0)&&(c.g==0)&&(c.b==255)){co=2;}
  if((c.r==255)&&(c.g==255)&&(c.b==0)){co=3;}
  if((c.r==100)&&(c.g==100)&&(c.b==100)){co=4;}
  if((c.r==100)&&(c.g==50)&&(c.b==0)){co=5;}
  colorie_tache(p, t, co);  
  if (co==(p->contenu[0][0])){return (1==0);}// la nouvelle couleur correspond a la couleur de la tache actuelle
  else {
  colorie_tache(p, t, co);
  return (0==0);
  }
}


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


/*
int main3() {
  int n=3;
  plateau p =aleatoire(n,6);
  plateau tache= new(n);
  int continuer = 1;
  SDL_Surface *ecran = NULL;
  couleur c;
  int vict = victoire(p);
  ecran=SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("interface graphique", NULL);
  
  fillScreen(ecran, 0,0,0);
    
  while (continuer ==1){
    affiche_plateau(ecran,p);
    vict=victoire(p);
    if (vict==1){
      continuer=0;
      printf("victoire \n");
    }
    else {
      c=read_couleur(ecran);
      if ((c.r==-1) || (c.g==-1)){
	continuer=0;
      }
      else {
	colorie_tache_graphic(&p,&tache,c); 
      }
    }
  }
  SDL_Quit( );
  return 0;
}


*/

int main2() {
  plateau p =aleatoire(5,6);
  int continuer = 1;
  SDL_Surface *ecran = NULL;
  SDL_Event event;
  const SDL_VideoInfo* info = NULL;
  /* SDL_Surface *ima=NULL;*/
  
  /* initialisation de la fenêtre d'affichage*/
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    /* Failed, exit. */
    fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
    SDL_Quit( );
  }
  info = SDL_GetVideoInfo( );
  if( !info ) {
    /* This should probably never happen. */
    fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
    SDL_Quit( );
  }
    ecran=SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("exemple SDL", NULL);
    
    fillScreen(ecran, 0,0,0);
    
    while (continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
	    case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN: /* gestion des évènements clavier*/
            	switch (event.key.keysym.sym) {
		case SDLK_m:
		  affiche_plateau(ecran,p);
		  break;
            		case SDLK_d:
                        drawRectangle(ecran, 3, 300, 30, 255, 0, 0);
                        drawRectangle(ecran, 36, 300, 30, 0, 255, 0);
                        drawRectangle(ecran, 69, 300, 30, 0, 0, 255);
                        
                        break;
            		case SDLK_e:
                        fillScreen(ecran, 255,0,255);
						break;
                    case SDLK_r:
                        fillScreen(ecran, 0,0,0);
                        
                        break;
            		case SDLK_ESCAPE:
			  continuer=0; break;
		default:
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
                    drawRectangle(ecran, 3, 3, 30, p[1], p[2], p[3]);
                    drawRectangle(ecran, 36, 3, 30, p[1], p[2], p[3]);
                    drawRectangle(ecran, 69, 3, 30, p[1], p[2], p[3]);

                }
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    autoDraw=1;
                    drawRectangle(ecran, event.button.x, event.button.y, 3, 0, 255, 0);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                autoDraw=0;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    drawRectangle(ecran, event.button.x, event.button.y, 3, 255, 0, 0);
                }
                break;

            case SDL_MOUSEMOTION:
                if (autoDraw)
                    drawRectangle(ecran, event.button.x, event.button.y, 1, 0, 0, 255);
                break;
        }
    }
	SDL_Quit();
    
	return 0;
}
