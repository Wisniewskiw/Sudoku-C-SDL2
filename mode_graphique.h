#ifndef sdl2_testing_mode_graphique_h
#define sdl2_testing_mode_graphique_h


#include "SDL.h"
#include "SDL_image.h"

#include <time.h>
#include "Lire.h"
#include <stdio.h>
#include <stdlib.h>

#include "Lire.h"
#include "interactif.h"
#include "brute_force.h"
#include "structures.h"
#include <sys/time.h>
#include "database_test.h"


#include <unistd.h>

#include <errno.h>

#include <stdlib.h>
#include <string.h>

//structure  coordonees de objets sur l'ecran
typedef struct
{
    int x, y;
} Star;


//structure jeu
typedef struct
{


    //on a besoin d'une liste de coordones
    Star stars[1000];

    //Images le menu start exit avec des couleurs differentes
    SDL_Texture *star;
    SDL_Texture *star2;
    SDL_Texture *star3;
    SDL_Texture *star4;
    SDL_Texture *star5;
     SDL_Texture *star6;

    //Images de chiffres rouges que on ne peut pas modifier
    SDL_Texture *one_r;
    SDL_Texture *two_r;
    SDL_Texture *three_r;
    SDL_Texture *four_r;
    SDL_Texture *five_r;
    SDL_Texture *six_r;
    SDL_Texture *seven_r;
    SDL_Texture *eight_r;
    SDL_Texture *nine_r;
    SDL_Texture *blanc;


    //images chiffres verts  que  le jouer place
    SDL_Texture *one_g;
    SDL_Texture *two_g;
    SDL_Texture *three_g;
    SDL_Texture *four_g;
    SDL_Texture *five_g;
    SDL_Texture *six_g;
    SDL_Texture *seven_g;
    SDL_Texture *eight_g;
    SDL_Texture *nine_g;


    //images  pour afficher si on a gagne ou perdu
    SDL_Texture *loser;
    SDL_Texture *bravo;

    SDL_Renderer *renderer;
    int up;                         //besoin dans le menu au debut
    int sudoku;                     // on affiche  la grille vide sudoku
    int mouse_x;                    //coordones de la souris
    int mouse_y;
    int place1_in00[81];            //  le placements de  chifres  listes booleans
    int place2_in00[81];
    int place3_in00[81];
    int place4_in00[81];
    int place5_in00[81];
    int place6_in00[81];
    int place7_in00[81];
    int place8_in00[81];
    int place9_in00[81];
    int sukces;
    int perdu;


} GameState;

void loadGame(GameState *game);
int processEvents(SDL_Window *window, GameState *game,int boolean[81],int ** tableau_sudoku,int ** sudo);                                   //traite ce qui se passe
void doRender(SDL_Renderer *renderer, GameState *game,int boolean[81]);// render

#endif
