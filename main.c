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

char cwd[1024];

int main(int argc, char *argv[]){
    getcwd(cwd, sizeof(cwd)); //j'ai besoin du dossier parent
    int choix;

    //CONSTRUCTION DE MENU

    //si un seul argument qui est un path pour un fichier sudoku alors on imprime la solution comme demandé dans l'énoncé
    if (argc==2) {
        char* path=(char*) argv[1];
        int ** tableau=lire_sudoku_fichier(path);
        solveur2_evaluation(tableau);
        return 0;
    }

    else{int menu=1;
        while (menu==1){
            printf("BIENVENUE DANS LE MENU \n");
            printf("Choix d'options:\n");

            if (argc>2){printf("0.Resoudre les sudokus rentres en parametre\n");}//si plusieurs sudokus en entrée, nouvelle option
            printf("1.Test de temps pour la methode DLX pour database de 2364 sudokus\n");
            printf("2.Test de temps pour la methode DLX pour database de 6343 sudokus\n");
            printf("3.Brute force vs DLX \n");
            printf("4.Mode interactif\n");
            printf("5.Creer un sudoku carre avec une unique solution\n");
            printf("6.Sudoku irregulier  \n");
            printf("7.Version graphique (jeu)\n");
            printf("Votre choix ?:\n");
            if ( scanf("%d",&choix)==0) {
                    printf("Pas de caractere ! \n");
                    exit(0);
                }
            printf("\n");

            if (argc>2 && choix==0) {  //si on a plusieurs sudoku en entrée, on les résoud à la suite
                int i;
                for (i=1; i<argc; i++) {
                    printf("%s\n",argv[i]);
                    combien2=0;
                    char* path=(char*) argv[i];
                    int ** tableau=lire_sudoku_fichier(path);
                    solveur2(tableau,1);
                }
                return 0;
            }
            
           
                      
            
            
            
            
            if (choix==1) {
                //on teste le temps moyen sur 2364 sudokus enregistrés dans le fichiers
                TAILLE=9;
                TAILLE_COTE_C=3;
                TAILLE_COTE_L=3;
                char * nom_fichier= concat(cwd,"/sudoku_txt/top2365.txt");
                time_test(nom_fichier);//le programme qui calcule le temps
            }
            if (choix==2) {//on test le temps moyen sur 6343 sudokus enregistré dans le fichier
                TAILLE=9;
                TAILLE_COTE_C=3;
                TAILLE_COTE_L=3;
                char * nom_fichier2= concat(cwd,"/sudoku_txt/special.txt");
                time_test(nom_fichier2);
            }
            if (choix==3) {//comparaison sur un exemple entre brute force et DLX
                char* path=concat(cwd,"/sudoku_txt/test.txt");
                int ** tableau=lire_sudoku_fichier(path);
                struct timeval start, stop;
                double secs = 0;
                gettimeofday(&start, NULL);

                //Brute force met du temps sur cet exemple, mais cela depend évidemment des sudokus

                print_tableau_sudoku(tableau);
                brute_force(tableau, 0,1);

                gettimeofday(&stop, NULL);
                secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

                struct timeval start2, stop2;
                double secs2 = 0;

                gettimeofday(&start2, NULL);
                solveur2(tableau,1)   ;
                gettimeofday(&stop2, NULL);
                secs2 = (double)(stop2.tv_usec - start2.tv_usec) / 1000000 + (double)(stop2.tv_sec - start2.tv_sec);

                printf("Time taken brute %f\n",secs);
                printf("Time taken DLX %f\n",secs2);
            }

            if (choix==4) {//mode interactif, on ne travaille que avec des sudokus 9x9
                TAILLE=9;
                TAILLE_COTE_C=3;
                TAILLE_COTE_L=3;
                mode_interactif();
            }

            if (choix==5) {//création d'un sudoku aléatoire
                int choix2;
                printf("Votre choix de la taille de la grille ?:\n");
                if ( scanf(" %d",&choix2)==0) {//pour s'assurer que l'utilisateur ne rentre pas de caractere
                    printf("Pas de caractere ! \n");
                    exit(0);
                }
                printf("\n");
                int test=racinecarre(choix2);
                //on va vérifier que la taille rentrée est bien un carré
                while (test*test!=choix2){printf("La taille d'un sudoku doit etre un carre (ex: 4,9,16...)\n");
                    printf("Votre choix de la taille de la grille ?:\n");
                    if (scanf(" %d",&choix2)==0) {
                        printf("Pas de caractere ! \n");
                        exit(0);
                    }
                    test=racinecarre(choix2);}
                TAILLE=choix2;
                TAILLE_COTE_C=test;
                TAILLE_COTE_L=test;
                printf("Tapez 1 si vous voulez le sudoku complet, sinon il y aura juste le sudoku avec trous :\n");
                int complet;
                if (scanf("%d",&complet)==0) {
                    printf("Pas de caractere ! \n");
                    exit(0);
                    }
                printf("\n");
                int **t;
                if (complet==1){//ici on génère le programme avec les options pour imprimer
                    t= genere_sudoku2(1,complet);}
                else{t= genere_sudoku2(1,0);}
                int choix3;
                printf("Voulez vous sauvegarder  la grille ? Si oui tapez 1:\n");
                scanf("%d",&choix3);printf("\n");
                if (choix3==1) {
                    char  path[256];
                    printf("Donnez le path ou sauvegarder\n");
                    scanf("%s",path);printf("\n");
                    save(path,t);
                }

            }
            

            if (choix==6)
            {
                //SOUS MENU

                printf("6.1)Exemple sudoku 2x5\n");
                printf("6.2)Resoudre un sudoku irregulier stocke dans un fichier\n");
                printf("6.3)Creer un sudoku  irregulier avec une unique solution \n");
                printf("6.4)Mode interactif sudoku irregulier \n");



                int choix5;
                printf("Votre choix  ?:\n");
                if ( scanf("%d",&choix5)==0) {
                    printf("Pas de caractere ! \n");
                    exit(0);
                }
                printf("\n");


                if (choix5==1) {

                    char *path7=concat(cwd,"/sudoku_txt/2x5.txt");
                    int ** sudoku=lire_sudoku_fichier(path7);
                    TAILLE_COTE_C=2;
                    TAILLE_COTE_L=5;
                    TAILLE=TAILLE_COTE_C*TAILLE_COTE_L;
                    solveur2(sudoku,1);
                }

                if (choix5==2) {
                    char  path2[256];
                    printf("Donnez le path ou se trouve le fichier\n");
                    scanf("%s",path2);printf("\n");
                    int ** sudoku=lire_sudoku_fichier(path2);
                    printf("Donnez le nombre de lignes du petit bloc \n");
                    scanf("%d",&TAILLE_COTE_C);printf("\n");
                    printf("Donnez le nombre de colonnes du petit bloc \n");
                    scanf("%d",&TAILLE_COTE_L);printf("\n");

                    if (TAILLE_COTE_C*TAILLE_COTE_L!=TAILLE || verifier_contraintes(sudoku)==0) {
                        printf("Probleme de sudoku ou de dimensions \n");
                        return 0;
                    }
                    solveur2(sudoku,1);
                }

                if (choix5==3) {

                    printf("Donnez le nombre de lignes du petit bloc \n");
                    if ( scanf(" %d",&TAILLE_COTE_C)==0) {
                    printf("Pas de caractere ! \n");
                    exit(0);
                    }
                    printf("\n");
                    printf("Donnez le nombre de colonnes du petit bloc\n");
                    if (scanf(" %d",&TAILLE_COTE_L)==0) {
                    printf("Pas de caractere ! \n");
                    exit(0);
                    }
                    printf("\n");
                    TAILLE=TAILLE_COTE_C*TAILLE_COTE_L;
                    printf("Tapez 1 si vous voulez le sudoku complet, sinon il y aura juste le sudoku avec trous :\n");
                    int complet;
                    if (scanf("%d",&complet)==0) {
                        printf("Pas de caractere ! \n");
                        exit(0);
                    }
                    printf("\n");
                    int **t;
                    if (complet==1){
                        t= genere_sudoku2(1,complet);}
                    else{t= genere_sudoku2(1,0);}
                    int choix3;
                    printf("Voulez vous sauvegarder  la grille ? Si oui Tapez 1:\n");
                    scanf("%d",&choix3);printf("\n");
                    if (choix3==1) {
                        char  path3[256];
                        printf("Donnez le path ou sauvegarder\n");
                        scanf("%s",path3);printf("\n");
                        save(path3,t);
                    }

                }

                if (choix5==4) {//le mode interactif avec des sudokus irréguliers
                    printf("Donnez le nombre de lignes du petit bloc \n");
                    if ( scanf(" %d",&TAILLE_COTE_C)==0) {
                        printf("Pas de caractere ! \n");
                        exit(0);
                    }
                    printf("\n");
                    printf("Donnez le nombre de colonnes du petit bloc\n");
                    if (scanf(" %d",&TAILLE_COTE_L)==0) {
                        printf("Pas de caractere ! \n");
                        exit(0);
                    }
                    printf("\n");
                    TAILLE=TAILLE_COTE_C*TAILLE_COTE_L;
                    mode_interactif();
                }
            }

      
            
            if (choix==7){// Le jeu de sudoku on se contente de generer un sudoku aleatoire et de jouer
    
                GameState gameState;                            //Jeu structure speciale
                SDL_Window *window = NULL;                    // Declaration de la fenetre
                SDL_Renderer *renderer = NULL;                // Declaration de renderer
                
                SDL_Init(SDL_INIT_VIDEO);              // Initialisation SDL2
                
                srandom((int)time(NULL));
                
                //Creation de  la fenetre:
                window = SDL_CreateWindow("Sudoku par X.Bitsch & W.Wisniewski ",   // titre
                                          SDL_WINDOWPOS_UNDEFINED,           //  x position
                                          SDL_WINDOWPOS_UNDEFINED,           //  y position
                                          640,                               // largeur, in pixels
                                          480,                               // hauteur, in pixels
                                          0
                                          );
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                gameState.renderer = renderer;                              //initialisation des constantes
                
                gameState.sudoku=1;                                         //besoin de savoir si on
                gameState.up=1;                                             // a gagne, perdu
                gameState.sukces=0;
                gameState.perdu=0;
                int i,j,k;
                
                
                //initialisation de placement de chiffres
                for (i=0; i<81; i++) {
                    gameState.place1_in00[i]=0;                            
                }
                
                
                for (i=0; i<81; i++) {
                    gameState.place2_in00[i]=0;
                }
                for (i=0; i<81; i++) {
                    gameState.place3_in00[i]=0;
                }
                for (i=0; i<81; i++) {
                    gameState.place4_in00[i]=0;
                }
                for (i=0; i<81; i++) {
                    gameState.place5_in00[i]=0;
                }
                for (i=0; i<81; i++) {
                    gameState.place6_in00[i]=0;
                }
                for (i=0; i<81; i++) {
                    gameState.place7_in00[i]=0;
                }
                for (i=0; i<81; i++) {
                    gameState.place8_in00[i]=0;
                }
                for (i=0; i<81; i++) {
                    gameState.place9_in00[i]=0;
                }
                
                
                
                
                // on considere que les sudokus sont 9x9
                
                TAILLE=9;
                TAILLE_COTE_C=3;
                TAILLE_COTE_L=3;
                
                // la liste de sudokus difficiles
                
                
                char * difficile= concat(cwd,"/sudoku_txt/special.txt");
                int **sudo=alea_sudoku_difficile(difficile);
                
                
                int boolean[81];
                
                int ** tableau_sudoku=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
                
                for( i = 0; i < TAILLE; i++) tableau_sudoku[i] = (int *)malloc(TAILLE * sizeof(int));
                
                
                //copie de la sudoku alea  on a besoin du sudoku originale dans le cas ou le joueur veut
                // voir la solution
                for (i=0; i<9; i++) {
                    for (j=0; j<9; j++) {
                        tableau_sudoku[i][j]=sudo[i][j];
                    }
                }
                
                
                
                // on  initialise les placements des chiffres que on ne peut pas changer
                // le  tableau bool nous aide
                for (k=0; k<9; k++) {
                    
                    
                    for (i=0; i<3; i++) {
                        for (j=0; j<3; j++) {
                            if (sudo[j+3*(k/3)][i+3*(k%3)]==0) {
                                boolean[3*i+j+9*k]=0;
                            }
                            if (sudo[j+3*(k/3)][i+3*(k%3)]==1) {
                                boolean[3*i+j+9*k]=1;
                                gameState.place1_in00[3*i+j+9*k]=1;
                            }
                            
                            if (sudo[j+3*(k/3)][i+3*(k%3)]==2) {
                                boolean[3*i+j+9*k]=1;
                                gameState.place2_in00[3*i+j+9*k]=1;
                            }
                            
                            if (sudo[j+3*(k/3)][i+3*(k%3)]==3) {
                                boolean[3*i+j+9*k]=1;
                                gameState.place3_in00[3*i+j+9*k]=1;
                            }
                            
                            if (sudo[j+3*(k/3)][i+3*(k%3)]==4) {
                                boolean[3*i+j+9*k]=1;
                                gameState.place4_in00[3*i+j+9*k]=1;
                            }
                            
                            if (sudo[j+3*(k/3)][i+3*(k%3)]==5) {
                                boolean[3*i+j+9*k]=1;
                                gameState.place5_in00[3*i+j+9*k]=1;            }
                            
                            if (sudo[j+3*(k/3)][i+3*(k%3)]==6) {
                                boolean[3*i+j+9*k]=1;
                                gameState.place6_in00[3*i+j+9*k]=1;
                            }
                            
                            if (sudo[j+3*(k/3)][i+3*(k%3)]==7) {
                                boolean[3*i+j+9*k]=1;
                                gameState.place7_in00[3*i+j+9*k]=1;            }
                            
                            if (sudo[j+3*(k/3)][i+3*(k%3)]==8) {
                                boolean[3*i+j+9*k]=1;
                                gameState.place8_in00[3*i+j+9*k]=1;
                            }
                            
                            if (sudo[j+3*(k/3)][i+3*(k%3)]==9) {
                                boolean[3*i+j+9*k]=1;
                                gameState.place9_in00[3*i+j+9*k]=1;
                            }
                            
                        }
                    }
                }
                
                
                //ici on initialise le jeu  on fait render
                loadGame(&gameState);
                
                // condition d'aret
                int done = 0;
                
                //boucle
                while(!done)
                {
                    //on regarde les evenements
                    done = processEvents(window, &gameState,boolean,tableau_sudoku,sudo);
                    
                    //Affichage
                    doRender(renderer, &gameState,boolean);
                    
                }
                
                // terminer la fenetre
                SDL_DestroyWindow(window);
                SDL_DestroyRenderer(renderer);
                
                // exit
                SDL_Quit();
                return 0;
            }
        
            printf("\n\nTapez 1 si vous voulez revenir au menu, sinon le programme s'arrete\n");
            if ( scanf(" %d",&menu)==0) {
                    printf("Pas de caractere ! \n");
                    exit(0);
                }
            printf("\n");
            combien2=0;
        }

    }
    
    
    
    
    return 0;
}

















