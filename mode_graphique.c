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
#include "mode_graphique.h"

int out[9][9];      //besoin pour la solution
char cwd[1024];     //le dossier courant


//legere modification de la fonction de resolution
int cherche_solution2_evaluation_jeu(noeud * h,int i, noeud* solution[],int imprimer){
    if (h->noeud_droite == h){combien2++;
        // faut separer la resolution de la preparation de links
        if (imprimer==1) {
            int k;
            int linia,kolumna,numer;
            for ( k = 0; k < TAILLE*TAILLE && solution[k] != NULL; k++) {
                linia = (solution[k]->lin)/(TAILLE*TAILLE);
                kolumna = (solution[k]->lin - linia* TAILLE*TAILLE)/TAILLE;
                numer = (solution[k]->lin)%TAILLE + 1;
                out[linia][kolumna] = numer;
            }
            return 1;
        }
    }

    noeud * c=colonne_nombre_min_1(h);
    couvrir_colonne2(c);
    noeud * row,*new1,*new2;
    for (row=c->noeud_bas; row!=c; row=row->noeud_bas) {
        solution[i]=row;
        for (new1=row->noeud_droite; new1!=row; new1=new1->noeud_droite) {
            couvrir_colonne2(new1->pere);
        }
        cherche_solution2_evaluation_jeu(h, i+1, solution,imprimer);

        for (new2=row->noeud_gauche; new2!=row; new2=new2->noeud_gauche) {
            decouvrir_colonne2(new2->pere);
        }
    }
    decouvrir_colonne2(c);
    
    return 0;
}



void solveur2_evaluation_jeu(int ** tableau3){

    int i,j,k;
    noeud * h=initialisation_grille2();
    noeud ** solution=initialisation_solution();
    for ( i=0; i<TAILLE; i++) {
        for ( j=0; j<TAILLE; j++) {
            if (tableau3[i][j]==0) {
                for ( k=0; k<TAILLE; k++) {
                    inserer_noeud2(h, TAILLE*TAILLE*i+TAILLE*j+k, TAILLE*i+j);

                    inserer_noeud2(h, TAILLE*TAILLE*i+TAILLE*j+k, TAILLE*TAILLE+TAILLE*i+k);

                    inserer_noeud2(h, TAILLE*TAILLE*i+TAILLE*j+k, TAILLE*TAILLE*2+TAILLE*j+k);

                    inserer_noeud2(h, TAILLE*TAILLE*i+TAILLE*j+k, TAILLE*TAILLE*3+ TAILLE*(TAILLE_COTE_C*(i/TAILLE_COTE_C)+j/TAILLE_COTE_L)+k);
                }
            }


            else
            {
                inserer_noeud2(h, TAILLE*TAILLE*i+TAILLE*j+tableau3[i][j]-1, TAILLE*i+j);

                inserer_noeud2(h, TAILLE*TAILLE*i+TAILLE*j+tableau3[i][j]-1, TAILLE*TAILLE+TAILLE*i+tableau3[i][j]-1);

                inserer_noeud2(h, TAILLE*TAILLE*i+TAILLE*j+tableau3[i][j]-1, TAILLE*TAILLE*2+TAILLE*j+tableau3[i][j]-1);

                inserer_noeud2(h, TAILLE*TAILLE*i+TAILLE*j+tableau3[i][j]-1, TAILLE*TAILLE*3+ TAILLE*(TAILLE_COTE_C*(i/TAILLE_COTE_C)+j/TAILLE_COTE_L)+tableau3[i][j]-1);
            }
        }
    }


    noeud* efface;
    for (efface=h->noeud_bas; efface!=h; efface=efface->noeud_bas) {
        enlever_noeud_horizontale(efface);
    }

    cherche_solution2_evaluation_jeu(h, 0, solution,1);

}

// FIN de la modification de solution


// ca va generer certains  textures
void loadGame(GameState *game)
{
    int i;
    SDL_Surface *starSurface = NULL;


    starSurface = IMG_Load(concat(cwd,"/Images/boardback.png"));
    (game->star6) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);



    game->stars[5].x = 0;
    game->stars[5].y = 0;

      //initialisation  on va mettre le start  et exit
    starSurface = IMG_Load(concat(cwd,"/Images/2.png"));
    if(starSurface == NULL)
    {
        printf("Cannot find!\n\n");
        SDL_Quit();
        exit(1);
    }


    game->star = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    for(i = 0; i < 1; i++)
    {
        game->stars[i].x = 120;
        game->stars[i].y = 180;
    }

    starSurface = IMG_Load(concat(cwd,"/Images/3.png"));
    (game->star2) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    for( i = 1; i < 2; i++)
    {
        game->stars[i].x = 120;
        game->stars[i].y = 240;
    }


    starSurface = IMG_Load(concat(cwd,"/Images/1.png"));
    (game->star3) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);



    game->stars[2].x = 120;
    game->stars[2].y = 180;

    starSurface = IMG_Load(concat(cwd,"/Images/4.png"));
    (game->star4) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);



    game->stars[3].x = 120;
    game->stars[3].y = 240;



    //la grille de sudoku vide
    starSurface = IMG_Load(concat(cwd,"/Images/5.png"));
    (game->star5) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);



    game->stars[4].x = 20;
    game->stars[4].y = 20;


    //les chiffres rouges et leur position  on calcule le bon placement

    starSurface = IMG_Load(concat(cwd,"/Images/1r.png"));
    (game->one_r) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);



    int j,k;

    for (k=0; k<9; k++) {

        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {
                game->stars[15+3*i+j+9*k].x = 25+41*i+133*(k%3);
                game->stars[15+3*i+j+9*k].y = 25+41*j+133*(k/3);
            }
        }
    }


    starSurface = IMG_Load(concat(cwd,"/Images/2r.png"));
    (game->two_r) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    starSurface = IMG_Load(concat(cwd,"/Images/3r.png"));
    (game->three_r) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);


    starSurface = IMG_Load(concat(cwd,"/Images/4r.png"));
    (game->four_r) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    starSurface = IMG_Load(concat(cwd,"/Images/5r.png"));
    (game->five_r) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    starSurface = IMG_Load(concat(cwd,"/Images/6r.png"));
    (game->six_r) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    starSurface = IMG_Load(concat(cwd,"/Images/7r.png"));
    (game->seven_r) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    starSurface = IMG_Load(concat(cwd,"/Images/8r.png"));
    (game->eight_r) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    starSurface = IMG_Load(concat(cwd,"/Images/9r.png"));
    (game->nine_r) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    int l;

    for (l=1; l<9; l++) {
        for (k=0; k<9; k++) {

            for (i=0; i<3; i++) {
                for (j=0; j<3; j++) {
                    game->stars[81*l+15+3*i+j+9*k].x = 25+41*i+133*(k%3);
                    game->stars[81*l+15+3*i+j+9*k].y = 25+41*j+133*(k/3);
                }
            }
        }

    }



    // on fait pareil pour les chiffres verts  on les place

    starSurface = IMG_Load(concat(cwd,"/Images/1g.png"));
    (game->one_g) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    starSurface = IMG_Load(concat(cwd,"/Images/2g.png"));
    (game->two_g) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    starSurface = IMG_Load(concat(cwd,"/Images/3g.png"));
    (game->three_g) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);


    starSurface = IMG_Load(concat(cwd,"/Images/4g.png"));
    (game->four_g) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    starSurface = IMG_Load(concat(cwd,"/Images/5g.png"));
    (game->five_g) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    starSurface = IMG_Load(concat(cwd,"/Images/6g.png"));
    (game->six_g) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    starSurface = IMG_Load(concat(cwd,"/Images/7g.png"));
    (game->seven_g) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    starSurface = IMG_Load(concat(cwd,"/Images/8g.png"));
    (game->eight_g) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);

    starSurface = IMG_Load(concat(cwd,"/Images/9g.png"));
    (game->nine_g) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);


    // le placement de  bravo et looser

    starSurface = IMG_Load(concat(cwd,"/Images/bravo.png"));
    (game->bravo) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);



    game->stars[999].x = 420;
    game->stars[999].y = 200;


    starSurface = IMG_Load(concat(cwd,"/Images/looser.png"));
    (game->loser) = SDL_CreateTextureFromSurface(game->renderer, starSurface);
    SDL_FreeSurface(starSurface);



    game->stars[998].x = 420;
    game->stars[998].y = 200;
}



// la fonction qui va analyser le  comportement du joueur
int processEvents(SDL_Window *window, GameState *game,int boolean[81],int ** tableau_sudoku,int **sudo)
{
    SDL_Event event;  // evenement
    int done = 0;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)     // selon quest on a plusieurs cas
        {                     
            case SDL_WINDOWEVENT_CLOSE:
            {
                if(window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            }
                break;
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        done = 1;
                        break;
                }
            }
                break;
            case SDL_QUIT:
                //quit out of the game
                done = 1;
                break;
        }
    }

    //les coordonnees de la souris
    int x, y;
    SDL_GetMouseState(&x, &y);
    game->mouse_x=x;
    game->mouse_y=y;


    //on chope la derniere touche pressee sur le clavier

    const Uint8 *state = SDL_GetKeyboardState(NULL);


    // on a besoin de savoir  ce qui se passe au niveau du menu


    if(state[SDL_SCANCODE_UP])
    {
        if (game->up==0) {
            game->up=1;
        }


    }
    if(state[SDL_SCANCODE_DOWN])
    {
        if (game->up==1) {
            game->up=0;
        }

    }

    if(state[SDL_SCANCODE_RETURN] && game->up && game->sudoku)
    {
        game->sudoku=0; //on va jouer: entree sur  play
    }

    if(state[SDL_SCANCODE_RETURN] && game->up==0 && game->sudoku)
    {
        done = 1;               //exit :  entree sur exit
        return done;
    }



    //si on va jouer  et appuyer espace on va afficher le sudoku resolu et le joueur pourra rien faire.

    if(state[SDL_SCANCODE_SPACE] && game->sudoku==0  ){

        game->perdu=1;                          // on a perdu
        solveur2_evaluation_jeu(sudo);          // solution
        int a,b;

        for (a=0; a<TAILLE; a++) {
            for (b=0; b<TAILLE; b++) {
                tableau_sudoku[a][b]=out[a][b]; //on copie la solution

            }

        }



        // dans cette partie on va mettre  partout 1 dans le tableau boolean  pour dire que
        // tout et remplie et  mise a jour de placement de tous les chiffres

        int i,j,k;

        //preparation effacage

        for (k=0; k<9; k++) {

            for (i=0; i<3; i++) {
                for (j=0; j<3; j++) {
                   boolean[3*i+j+9*k]=0;
                    game->place1_in00[3*i+j+9*k]=0;
                    game->place2_in00[3*i+j+9*k]=0;
                    game->place3_in00[3*i+j+9*k]=0;
                    game->place4_in00[3*i+j+9*k]=0;
                    game->place5_in00[3*i+j+9*k]=0;
                    game->place6_in00[3*i+j+9*k]=0;
                    game->place7_in00[3*i+j+9*k]=0;
                    game->place8_in00[3*i+j+9*k]=0;
                    game->place9_in00[3*i+j+9*k]=0;

                }
            }
        }


        //preparation solution

        for (k=0; k<9; k++) {

            for (i=0; i<3; i++) {
                for (j=0; j<3; j++) {


                            boolean[3*i+j+9*k]=1;

                    if (tableau_sudoku[j+3*(k/3)][i+3*(k%3)]==1) {

                        game->place1_in00[3*i+j+9*k]=1;

                    }
                    if (tableau_sudoku[j+3*(k/3)][i+3*(k%3)]==2) {

                        game->place2_in00[3*i+j+9*k]=1;

                    }
                    if (tableau_sudoku[j+3*(k/3)][i+3*(k%3)]==3) {

                        game->place3_in00[3*i+j+9*k]=1;

                    }
                    if (tableau_sudoku[j+3*(k/3)][i+3*(k%3)]==4) {

                        game->place4_in00[3*i+j+9*k]=1;

                    }
                    if (tableau_sudoku[j+3*(k/3)][i+3*(k%3)]==5) {

                        game->place5_in00[3*i+j+9*k]=1;

                    }
                    if (tableau_sudoku[j+3*(k/3)][i+3*(k%3)]==6) {

                        game->place6_in00[3*i+j+9*k]=1;

                    }
                    if (tableau_sudoku[j+3*(k/3)][i+3*(k%3)]==7) {

                        game->place7_in00[3*i+j+9*k]=1;

                    }
                    if (tableau_sudoku[j+3*(k/3)][i+3*(k%3)]==8) {

                        game->place8_in00[3*i+j+9*k]=1;

                    }
                    if (tableau_sudoku[j+3*(k/3)][i+3*(k%3)]==9) {

                        game->place9_in00[3*i+j+9*k]=1;

                    }


                }
            }
        }



    }



    // ici selon le placement de la souris et certains conditions du jeu on  va faire une mise a jour
    // du tableau de sudoku  et placer ou  c'est permis

    // on separe tous les cas pour  tous les  chiffres

    int i,j,k;

    for (k=0; k<9; k++) {


        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {


                // si on a appuye sur 1  on joue et notre souris  est placer sur la grille
                // et on peut placer le  1 ici et 1 n'etait pas place d'avance


                if(state[SDL_SCANCODE_1] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place1_in00[3*i+j+9*k]==0&& boolean[3*i+j+9*k]==0)
                {

                    int ** tableau_sudoku_aux=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
                    int i1,j1;

                    for( i1 = 0; i1 < TAILLE; i1++) tableau_sudoku_aux[i1] = (int *)malloc(TAILLE * sizeof(int));


                    for (i1=0; i1<9; i1++) {
                        for (j1=0; j1<9; j1++) {
                            tableau_sudoku_aux[i1][j1]=tableau_sudoku[i1][j1];
                        }
                    }

                    //on copie le tableau  on met a jour et on regarde si les contraintes
                    //de sudoku sont verifiees

                    tableau_sudoku_aux[j+3*(k/3)][i+3*(k%3)]=1;
                    if (verifier_contraintes(tableau_sudoku_aux)) {
                        // si oui on met a jour le  tableau du sudoku et on place le 1
                        tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=1;
                        game->place1_in00[3*i+j+9*k]=1;
                        game->place2_in00[3*i+j+9*k]=0;
                        game->place3_in00[3*i+j+9*k]=0;
                        game->place4_in00[3*i+j+9*k]=0;
                        game->place5_in00[3*i+j+9*k]=0;
                        game->place6_in00[3*i+j+9*k]=0;
                        game->place7_in00[3*i+j+9*k]=0;
                        game->place8_in00[3*i+j+9*k]=0;
                        game->place9_in00[3*i+j+9*k]=0;


                        // si on a tout rempli  alors succes
                        if (combien_zeros(tableau_sudoku)==0) {
                            game->sukces=1;
                        }




                    }


                    int i2;
                    for (i2=0; i2<TAILLE; i2++) {
                        free(tableau_sudoku_aux[i2]);
                    }
                    // a chaque fois on free le  tab aux



                }

                // on peut egalement effacer notre entre par 0  ca va vider la case et on mise a jour
                if(state[SDL_SCANCODE_0] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place1_in00[3*i+j+9*k]==1 && boolean[3*i+j+9*k]==0)
                {
                    game->place1_in00[3*i+j+9*k]=0;
                    tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=0;



                }







            }
        }
    }



    // on fait  pareil pour le reste de cas  c'est presque la meme chose  avec des changements mineurs



    for (k=0; k<9; k++) {


        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {


                if(state[SDL_SCANCODE_2] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place2_in00[3*i+j+9*k]==0&& boolean[3*i+j+9*k]==0)
                {

                    int ** tableau_sudoku_aux=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
                    int i1,j1;

                    for( i1 = 0; i1 < TAILLE; i1++) tableau_sudoku_aux[i1] = (int *)malloc(TAILLE * sizeof(int));


                    for (i1=0; i1<9; i1++) {
                        for (j1=0; j1<9; j1++) {
                            tableau_sudoku_aux[i1][j1]=tableau_sudoku[i1][j1];
                        }
                    }



                    tableau_sudoku_aux[j+3*(k/3)][i+3*(k%3)]=2;
                    if (verifier_contraintes(tableau_sudoku_aux)) {
                        tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=2;
                        game->place1_in00[3*i+j+9*k]=0;
                        game->place2_in00[3*i+j+9*k]=1;
                        game->place3_in00[3*i+j+9*k]=0;
                        game->place4_in00[3*i+j+9*k]=0;
                        game->place5_in00[3*i+j+9*k]=0;
                        game->place6_in00[3*i+j+9*k]=0;
                        game->place7_in00[3*i+j+9*k]=0;
                        game->place8_in00[3*i+j+9*k]=0;
                        game->place9_in00[3*i+j+9*k]=0;



                        if (combien_zeros(tableau_sudoku_aux)==0) {
                            game->sukces=1;
                        }
                    }


                    int i2;
                    for (i2=0; i2<TAILLE; i2++) {
                        free(tableau_sudoku_aux[i2]);
                    }

                }

                if(state[SDL_SCANCODE_0] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place2_in00[3*i+j+9*k]==1&& boolean[3*i+j+9*k]==0)
                {
                    game->place2_in00[3*i+j+9*k]=0;
                    tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=0;
                }






            }
        }
    }





    for (k=0; k<9; k++) {


        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {


                if(state[SDL_SCANCODE_3] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place3_in00[3*i+j+9*k]==0&& boolean[3*i+j+9*k]==0)
                {



                    int ** tableau_sudoku_aux=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
                    int i1,j1;

                    for( i1 = 0; i1 < TAILLE; i1++) tableau_sudoku_aux[i1] = (int *)malloc(TAILLE * sizeof(int));


                    for (i1=0; i1<9; i1++) {
                        for (j1=0; j1<9; j1++) {
                            tableau_sudoku_aux[i1][j1]=tableau_sudoku[i1][j1];
                        }
                    }



                    tableau_sudoku_aux[j+3*(k/3)][i+3*(k%3)]=3;
                    if (verifier_contraintes(tableau_sudoku_aux)) {
                        tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=3;
                        game->place1_in00[3*i+j+9*k]=0;
                        game->place2_in00[3*i+j+9*k]=0;
                        game->place3_in00[3*i+j+9*k]=1;
                        game->place4_in00[3*i+j+9*k]=0;
                        game->place5_in00[3*i+j+9*k]=0;
                        game->place6_in00[3*i+j+9*k]=0;
                        game->place7_in00[3*i+j+9*k]=0;
                        game->place8_in00[3*i+j+9*k]=0;
                        game->place9_in00[3*i+j+9*k]=0;



                        if (combien_zeros(tableau_sudoku_aux)==0) {
                            game->sukces=1;
                        }
                    }


                    int i2;
                    for (i2=0; i2<TAILLE; i2++) {
                        free(tableau_sudoku_aux[i2]);
                    }


                }

                if(state[SDL_SCANCODE_0] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place3_in00[3*i+j+9*k]==1&& boolean[3*i+j+9*k]==0)
                {
                    game->place3_in00[3*i+j+9*k]=0;
                    tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=0;
                }






            }
        }
    }








    for (k=0; k<9; k++) {


        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {


                if(state[SDL_SCANCODE_4] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place4_in00[3*i+j+9*k]==0&& boolean[3*i+j+9*k]==0)
                {

                    int ** tableau_sudoku_aux=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
                    int i1,j1;

                    for( i1 = 0; i1 < TAILLE; i1++) tableau_sudoku_aux[i1] = (int *)malloc(TAILLE * sizeof(int));


                    for (i1=0; i1<9; i1++) {
                        for (j1=0; j1<9; j1++) {
                            tableau_sudoku_aux[i1][j1]=tableau_sudoku[i1][j1];
                        }
                    }



                    tableau_sudoku_aux[j+3*(k/3)][i+3*(k%3)]=4;
                    if (verifier_contraintes(tableau_sudoku_aux)) {
                        tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=4;
                        game->place1_in00[3*i+j+9*k]=0;
                        game->place2_in00[3*i+j+9*k]=0;
                        game->place3_in00[3*i+j+9*k]=0;
                        game->place4_in00[3*i+j+9*k]=1;
                        game->place5_in00[3*i+j+9*k]=0;
                        game->place6_in00[3*i+j+9*k]=0;
                        game->place7_in00[3*i+j+9*k]=0;
                        game->place8_in00[3*i+j+9*k]=0;
                        game->place9_in00[3*i+j+9*k]=0;



                        if (combien_zeros(tableau_sudoku_aux)==0) {
                            game->sukces=1;
                        }
                    }

                    int i2;
                    for (i2=0; i2<TAILLE; i2++) {
                        free(tableau_sudoku_aux[i2]);
                    }

                }

                if(state[SDL_SCANCODE_0] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place4_in00[3*i+j+9*k]==1&& boolean[3*i+j+9*k]==0)
                {
                    game->place4_in00[3*i+j+9*k]=0;
                    tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=0;
                }






            }
        }
    }






    for (k=0; k<9; k++) {


        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {


                if(state[SDL_SCANCODE_5] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place5_in00[3*i+j+9*k]==0&& boolean[3*i+j+9*k]==0)
                {

                    int ** tableau_sudoku_aux=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
                    int i1,j1;

                    for( i1 = 0; i1 < TAILLE; i1++) tableau_sudoku_aux[i1] = (int *)malloc(TAILLE * sizeof(int));


                    for (i1=0; i1<9; i1++) {
                        for (j1=0; j1<9; j1++) {
                            tableau_sudoku_aux[i1][j1]=tableau_sudoku[i1][j1];
                        }
                    }



                    tableau_sudoku_aux[j+3*(k/3)][i+3*(k%3)]=5;
                    if (verifier_contraintes(tableau_sudoku_aux)) {
                        tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=5;
                        game->place1_in00[3*i+j+9*k]=0;
                        game->place2_in00[3*i+j+9*k]=0;
                        game->place3_in00[3*i+j+9*k]=0;
                        game->place4_in00[3*i+j+9*k]=0;
                        game->place5_in00[3*i+j+9*k]=1;
                        game->place6_in00[3*i+j+9*k]=0;
                        game->place7_in00[3*i+j+9*k]=0;
                        game->place8_in00[3*i+j+9*k]=0;
                        game->place9_in00[3*i+j+9*k]=0;


                                                if (combien_zeros(tableau_sudoku_aux)==0) {
                            game->sukces=1;
                        }

                    }

                    int i2;
                    for (i2=0; i2<TAILLE; i2++) {
                        free(tableau_sudoku_aux[i2]);
                    }

                }

                if(state[SDL_SCANCODE_0] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place5_in00[3*i+j+9*k]==1&& boolean[3*i+j+9*k]==0)
                {
                    game->place5_in00[3*i+j+9*k]=0;
                    tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=0;
                }






            }
        }
    }





    for (k=0; k<9; k++) {


        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {


                if(state[SDL_SCANCODE_6] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place6_in00[3*i+j+9*k]==0&& boolean[3*i+j+9*k]==0)
                {

                    int ** tableau_sudoku_aux=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
                    int i1,j1;

                    for( i1 = 0; i1 < TAILLE; i1++) tableau_sudoku_aux[i1] = (int *)malloc(TAILLE * sizeof(int));


                    for (i1=0; i1<9; i1++) {
                        for (j1=0; j1<9; j1++) {
                            tableau_sudoku_aux[i1][j1]=tableau_sudoku[i1][j1];
                        }
                    }



                    tableau_sudoku_aux[j+3*(k/3)][i+3*(k%3)]=6;
                    if (verifier_contraintes(tableau_sudoku_aux)) {
                        tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=6;
                        game->place1_in00[3*i+j+9*k]=0;
                        game->place2_in00[3*i+j+9*k]=0;
                        game->place3_in00[3*i+j+9*k]=0;
                        game->place4_in00[3*i+j+9*k]=0;
                        game->place5_in00[3*i+j+9*k]=0;
                        game->place6_in00[3*i+j+9*k]=1;
                        game->place7_in00[3*i+j+9*k]=0;
                        game->place8_in00[3*i+j+9*k]=0;
                        game->place9_in00[3*i+j+9*k]=0;



                        if (combien_zeros(tableau_sudoku_aux)==0) {
                            game->sukces=1;
                        }

                    }
                    int i2;
                    for (i2=0; i2<TAILLE; i2++) {
                        free(tableau_sudoku_aux[i2]);
                    }

                    ;
                }

                if(state[SDL_SCANCODE_0] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place6_in00[3*i+j+9*k]==1&& boolean[3*i+j+9*k]==0)
                {
                    game->place6_in00[3*i+j+9*k]=0;
                    tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=0;
                }






            }
        }
    }





    for (k=0; k<9; k++) {


        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {


                if(state[SDL_SCANCODE_7] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place7_in00[3*i+j+9*k]==0&& boolean[3*i+j+9*k]==0)
                {

                    int ** tableau_sudoku_aux=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
                    int i1,j1;

                    for( i1 = 0; i1 < TAILLE; i1++) tableau_sudoku_aux[i1] = (int *)malloc(TAILLE * sizeof(int));


                    for (i1=0; i1<9; i1++) {
                        for (j1=0; j1<9; j1++) {
                            tableau_sudoku_aux[i1][j1]=tableau_sudoku[i1][j1];
                        }
                    }



                    tableau_sudoku_aux[j+3*(k/3)][i+3*(k%3)]=7;
                    if (verifier_contraintes(tableau_sudoku_aux)) {
                        tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=7;
                        game->place1_in00[3*i+j+9*k]=0;
                        game->place2_in00[3*i+j+9*k]=0;
                        game->place3_in00[3*i+j+9*k]=0;
                        game->place4_in00[3*i+j+9*k]=0;
                        game->place5_in00[3*i+j+9*k]=0;
                        game->place6_in00[3*i+j+9*k]=0;
                        game->place7_in00[3*i+j+9*k]=1;
                        game->place8_in00[3*i+j+9*k]=0;
                        game->place9_in00[3*i+j+9*k]=0;


                        if (combien_zeros(tableau_sudoku_aux)==0) {
                            game->sukces=1;
                        }

                    }
                    int i2;
                    for (i2=0; i2<TAILLE; i2++) {
                        free(tableau_sudoku_aux[i2]);
                    }

                }

                if(state[SDL_SCANCODE_0] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place7_in00[3*i+j+9*k]==1&& boolean[3*i+j+9*k]==0)
                {
                    game->place7_in00[3*i+j+9*k]=0;
                    tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=0;
                }






            }
        }
    }




    for (k=0; k<9; k++) {


        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {

                if(state[SDL_SCANCODE_8] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place8_in00[3*i+j+9*k]==0&& boolean[3*i+j+9*k]==0)
                {

                    int ** tableau_sudoku_aux=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
                    int i1,j1;

                    for( i1 = 0; i1 < TAILLE; i1++) tableau_sudoku_aux[i1] = (int *)malloc(TAILLE * sizeof(int));


                    for (i1=0; i1<9; i1++) {
                        for (j1=0; j1<9; j1++) {
                            tableau_sudoku_aux[i1][j1]=tableau_sudoku[i1][j1];
                        }
                    }



                    tableau_sudoku_aux[j+3*(k/3)][i+3*(k%3)]=8;
                    if (verifier_contraintes(tableau_sudoku_aux)) {
                        tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=8;                        game->place1_in00[3*i+j+9*k]=0;
                        game->place2_in00[3*i+j+9*k]=0;
                        game->place3_in00[3*i+j+9*k]=0;
                        game->place4_in00[3*i+j+9*k]=0;
                        game->place5_in00[3*i+j+9*k]=0;
                        game->place6_in00[3*i+j+9*k]=0;
                        game->place7_in00[3*i+j+9*k]=0;
                        game->place8_in00[3*i+j+9*k]=1;
                        game->place9_in00[3*i+j+9*k]=0;


                        if (combien_zeros(tableau_sudoku_aux)==0) {
                            game->sukces=1;
                        }

                    }

                    int i2;
                    for (i2=0; i2<TAILLE; i2++) {
                        free(tableau_sudoku_aux[i2]);
                    }
                }

                if(state[SDL_SCANCODE_0] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place8_in00[3*i+j+9*k]==1&& boolean[3*i+j+9*k]==0)
                {
                    game->place8_in00[3*i+j+9*k]=0;
                    tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=0;
                }






            }
        }
    }







    for (k=0; k<9; k++) {


        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {


                if(state[SDL_SCANCODE_9] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place9_in00[3*i+j+9*k]==0&& boolean[3*i+j+9*k]==0)
                {

                    int ** tableau_sudoku_aux=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
                    int i1,j1;

                    for( i1 = 0; i1 < TAILLE; i1++) tableau_sudoku_aux[i1] = (int *)malloc(TAILLE * sizeof(int));


                    for (i1=0; i1<9; i1++) {
                        for (j1=0; j1<9; j1++) {
                            tableau_sudoku_aux[i1][j1]=tableau_sudoku[i1][j1];
                        }
                    }



                    tableau_sudoku_aux[j+3*(k/3)][i+3*(k%3)]=9;
                    if (verifier_contraintes(tableau_sudoku_aux)) {
                        tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=9;
                        game->place1_in00[3*i+j+9*k]=0;
                        game->place2_in00[3*i+j+9*k]=0;
                        game->place3_in00[3*i+j+9*k]=0;
                        game->place4_in00[3*i+j+9*k]=0;
                        game->place5_in00[3*i+j+9*k]=0;
                        game->place6_in00[3*i+j+9*k]=0;
                        game->place7_in00[3*i+j+9*k]=0;
                        game->place8_in00[3*i+j+9*k]=0;
                        game->place9_in00[3*i+j+9*k]=1;



                        if (combien_zeros(tableau_sudoku_aux)==0) {
                            game->sukces=1;
                        }
                    }

                    int i2;
                    for (i2=0; i2<TAILLE; i2++) {
                        free(tableau_sudoku_aux[i2]);
                    }

                }

                if(state[SDL_SCANCODE_0] && game->sudoku==0 && game->mouse_x >25+41*i+133*(k%3) && game->mouse_y >25+41*j+133*(k/3) && game->mouse_x <66+41*i+133*(k%3) && game->mouse_y <66+41*j+133*(k/3) && game->place9_in00[3*i+j+9*k]==1&& boolean[3*i+j+9*k]==0)
                {
                    game->place9_in00[3*i+j+9*k]=0;
                    tableau_sudoku[j+3*(k/3)][i+3*(k%3)]=0;
                }






            }
        }
    }




    // return done


    return done;
}



// la partie render
void doRender(SDL_Renderer *renderer, GameState *game,int boolean[81])
{



    if (game->sudoku==1) {

        //met le couler  fond
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Rect starRect = { game->stars[5].x, game->stars[5].y, 640, 480 };
        SDL_RenderCopy(renderer, game->star6, NULL, &starRect);







        // la on va dessiner  le start exit

        if (game->up==1) {
            SDL_Rect starRect = { game->stars[0].x, game->stars[0].y, 400, 64 };
            SDL_RenderCopy(renderer, game->star, NULL, &starRect);

            SDL_Rect starRect2 = { game->stars[1].x, game->stars[1].y, 400, 64 };
            SDL_RenderCopy(renderer, game->star2, NULL, &starRect2);

        }
        else{

            SDL_Rect starRect = { game->stars[2].x, game->stars[2].y, 400, 64 };
            SDL_RenderCopy(renderer, game->star3, NULL, &starRect);

            SDL_Rect starRect2 = { game->stars[3].x, game->stars[3].y, 400, 64 };
            SDL_RenderCopy(renderer, game->star4, NULL, &starRect2);




        }



    }




    if (game->sudoku==0)

    {// si on joue  a sudoku on va dessiner la grille



        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);




        SDL_Rect starRect0 = { game->stars[5].x, game->stars[5].y, 640, 480 };
        SDL_RenderCopy(renderer, game->star6, NULL, &starRect0);


        SDL_Rect starRect = { game->stars[4].x, game->stars[4].y, 400, 400 };
        SDL_RenderCopy(renderer, game->star5, NULL, &starRect);







        //on va dessiner  les chiffres rouges et verts
        // vert si  sudoku etait  libre  sinon rouge 
        //on traite les 9 cas

        int i,j,k;


        for (k=0; k<9; k++) {



            for (i=0; i<3; i++) {
                for (j=0; j<3; j++) {
                    if (game->place1_in00[3*i+j+9*k]==1) {
                        SDL_Rect starRect2 = { game->stars[15+3*i+j+9*k].x, game->stars[15+3*i+j+9*k].y, 40, 40 };

                        if (boolean[3*i+j+9*k]==0) {
                            SDL_RenderCopy(renderer, game->one_g, NULL, &starRect2);
                        }
                        if (boolean[3*i+j+9*k]==1) SDL_RenderCopy(renderer, game->one_r, NULL, &starRect2);
                    }

                }
            }

        }





        for (k=0; k<9; k++) {



            for (i=0; i<3; i++) {
                for (j=0; j<3; j++) {
                    if (game->place2_in00[3*i+j+9*k]==1) {
                        SDL_Rect starRect2 = { game->stars[81+15+3*i+j+9*k].x, game->stars[81+15+3*i+j+9*k].y, 40, 40 };

                        if (boolean[3*i+j+9*k]==0) {
                            SDL_RenderCopy(renderer, game->two_g, NULL, &starRect2);
                        }
                        if (boolean[3*i+j+9*k]==1)  SDL_RenderCopy(renderer, game->two_r, NULL, &starRect2);


                    }

                }
            }

        }


        for (k=0; k<9; k++) {



            for (i=0; i<3; i++) {
                for (j=0; j<3; j++) {
                    if (game->place3_in00[3*i+j+9*k]==1) {
                        SDL_Rect starRect2 = { game->stars[81*2+15+3*i+j+9*k].x, game->stars[81*2+15+3*i+j+9*k].y, 40, 40 };
                        if (boolean[3*i+j+9*k]==0) {
                            SDL_RenderCopy(renderer, game->three_g, NULL, &starRect2);
                        }
                        if (boolean[3*i+j+9*k]==1)  SDL_RenderCopy(renderer, game->three_r, NULL, &starRect2);
                    }

                }
            }

        }




        for (k=0; k<9; k++) {



            for (i=0; i<3; i++) {
                for (j=0; j<3; j++) {
                    if (game->place4_in00[3*i+j+9*k]==1) {
                        SDL_Rect starRect2 = { game->stars[81*3+15+3*i+j+9*k].x, game->stars[81*3+15+3*i+j+9*k].y, 40, 40 };
                        if (boolean[3*i+j+9*k]==0) {
                            SDL_RenderCopy(renderer, game->four_g, NULL, &starRect2);
                        }
                        if (boolean[3*i+j+9*k]==1)  SDL_RenderCopy(renderer, game->four_r, NULL, &starRect2);
                    }

                }
            }

        }



        for (k=0; k<9; k++) {



            for (i=0; i<3; i++) {
                for (j=0; j<3; j++) {
                    if (game->place5_in00[3*i+j+9*k]==1) {
                        SDL_Rect starRect2 = { game->stars[81*4+15+3*i+j+9*k].x, game->stars[81*4+15+3*i+j+9*k].y, 40, 40 };
                        if (boolean[3*i+j+9*k]==0) {
                            SDL_RenderCopy(renderer, game->five_g, NULL, &starRect2);
                        }
                        if (boolean[3*i+j+9*k]==1)  SDL_RenderCopy(renderer, game->five_r, NULL, &starRect2);
                    }

                }
            }

        }


        for (k=0; k<9; k++) {



            for (i=0; i<3; i++) {
                for (j=0; j<3; j++) {
                    if (game->place6_in00[3*i+j+9*k]==1) {
                        SDL_Rect starRect2 = { game->stars[81*5+15+3*i+j+9*k].x, game->stars[81*5+15+3*i+j+9*k].y, 40, 40 };
                        if (boolean[3*i+j+9*k]==0) {
                            SDL_RenderCopy(renderer, game->six_g, NULL, &starRect2);
                        }
                        if (boolean[3*i+j+9*k]==1)  SDL_RenderCopy(renderer, game->six_r, NULL, &starRect2);

                    }

                }
            }

        }


        for (k=0; k<9; k++) {



            for (i=0; i<3; i++) {
                for (j=0; j<3; j++) {
                    if (game->place7_in00[3*i+j+9*k]==1) {
                        SDL_Rect starRect2 = { game->stars[81*6+15+3*i+j+9*k].x, game->stars[81*6+15+3*i+j+9*k].y, 40, 40 };
                        if (boolean[3*i+j+9*k]==0) {
                            SDL_RenderCopy(renderer, game->seven_g, NULL, &starRect2);
                        }
                        if (boolean[3*i+j+9*k]==1)  SDL_RenderCopy(renderer, game->seven_r, NULL, &starRect2);

                    }

                }
            }

        }



        for (k=0; k<9; k++) {



            for (i=0; i<3; i++) {
                for (j=0; j<3; j++) {
                    if (game->place8_in00[3*i+j+9*k]==1) {
                        SDL_Rect starRect2 = { game->stars[81*7+15+3*i+j+9*k].x, game->stars[81*7+15+3*i+j+9*k].y, 40, 40 };
                        if (boolean[3*i+j+9*k]==0) {
                            SDL_RenderCopy(renderer, game->eight_g, NULL, &starRect2);
                        }
                        if (boolean[3*i+j+9*k]==1)  SDL_RenderCopy(renderer, game->eight_r, NULL, &starRect2);
                    }

                }
            }

        }


        for (k=0; k<9; k++) {



            for (i=0; i<3; i++) {
                for (j=0; j<3; j++) {
                    if (game->place9_in00[3*i+j+9*k]==1) {
                        SDL_Rect starRect2 = { game->stars[81*8+15+3*i+j+9*k].x, game->stars[81*8+15+3*i+j+9*k].y, 40, 40 };
                        if (boolean[3*i+j+9*k]==0) {
                            SDL_RenderCopy(renderer, game->nine_g, NULL, &starRect2);
                        }
                        if (boolean[3*i+j+9*k]==1)  SDL_RenderCopy(renderer, game->nine_r, NULL, &starRect2);

                    }

                }
            }

        }
        if (game->sukces==1) {
            SDL_Rect starRect = { game->stars[999].x, game->stars[999].y, 200, 220 };
            SDL_RenderCopy(renderer, game->bravo, NULL, &starRect);


        }
        if (game->perdu==1) {
            SDL_Rect starRect = { game->stars[998].x, game->stars[998].y, 200, 220 };
            SDL_RenderCopy(renderer, game->loser, NULL, &starRect);


        }






    }


    SDL_RenderPresent(renderer);





}





