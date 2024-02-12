#include <stdio.h>
#include <stdlib.h>
#include "Lire.h"
#include "interactif.h"
#include "brute_force.h"
#include "structures.h"
#include <sys/time.h>
#include "database_test.h"

// fonction qui vérifie si il n'y a plus de zéros dans la grille

int fini_de_remplir(int**sudoku){
    int i,j;
    for (i=0; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            if (sudoku[i][j]==0) {
                return 0;
            }
        }
    }

    return 1;
}


//vérifie si le sudoku (rempli par l'utilisateur) est une solution (les contraintes de lignes colonnes et bloc)
int est_solution(int** sudoku){

    int i,j;


    for (i=0; i<TAILLE; i++) {
        int *verifie = calloc(TAILLE+1, sizeof(int));//0 partout
        for ( j=0; j<TAILLE; j++) {
            if (verifie[sudoku[i][j]]==1 ) {//si il y deux fois la même valeur dans une ligne, retourne 0, sudoku pas bon
                return 0;
            }
            verifie[sudoku[i][j]]=1;
        }
        free(verifie);
    }


    //colonnes
    for (i=0; i<TAILLE; i++) {
        int *verifie= calloc(TAILLE+1, sizeof(int));//0 partout
        for (j=0; j<TAILLE; j++) {
            if (verifie[sudoku[j][i]]==1 ) {//si il y deux fois la même valeur dans une colonne, retourne 0
                return 0;
            }
            verifie[sudoku[j][i]]=1;
        }
        free(verifie);
    }


    //bloc

    for( i = 0; i < TAILLE; i += TAILLE_COTE_L){
        for( j = 0; j < TAILLE; j+= TAILLE_COTE_C){
            int *verifie = calloc(TAILLE+1, sizeof(int));//0 partout
            int cote_i ,cote_j;
            for( cote_i = 0; cote_i < TAILLE_COTE_L; cote_i++){
                for( cote_j = 0; cote_j < TAILLE_COTE_C; cote_j++){

                    if(verifie[sudoku[i+cote_i][j+cote_j]]==1 )//si il y deux fois la même valeur dans un bloc, retourne 0
                    {return 0;}

                    verifie[sudoku[i+cote_i][j+cote_j]]=1;
                }
            }
            free(verifie);

        }
    }

    return 1;

}

//La fonction qui gère le mode interactif :


void    mode_interactif(){

    printf("BIENVENUE DANS LE MODE INTERACTIF\n\n");
    printf("Vous voulez entrer un sudoku vous meme tapez 1\n Sinon un sudoku aleatoire va etre genere\n");
    int ** tableau;
    int test;
    if (scanf(" %d",&test)==0) {
        printf("Pas de caractere ! \n");
        exit(0);
    }
    printf("\n");

    //selon l'entr√©e de l'utilisateur :

    if (test==1) {

        //le joueur va rentrer les chiffres, on prépare le tableau vide
        int i,a,b;
        tableau=(int **)malloc(TAILLE * sizeof(int*));
        for( i = 0; i < TAILLE; i++) tableau[i] = (int *)malloc(TAILLE * sizeof(int));

        for ( a=0; a<TAILLE; a++) {
            for ( b=0; b<TAILLE; b++) {

                tableau[a][b]=0;

            }
        }

        printf("Le mode REMPLISSAGE commence\n\n");
        //on va remplir jusqu'à ce que l'utilisateur souhaite arrêter
        int j=0;
        i=0;
        int valeur=0;
        while (i!=111 || j!=111) {
            printf("Veuillez entrez une ligne et colonne sinon tapez 111 pour finir\n");
            printf("Entrez la ligne :");


            if ( scanf(" %d",&i)==0) {
                printf("Pas de caractere ! \n");
                exit(0);
            }

           printf("\n");

            while ((i<1 ||i>TAILLE_COTE_C*TAILLE_COTE_L) && i!=111) {
                printf("Reessayez avec une ligne entre 1 et %d, ou 111 pour annuler :\n",TAILLE_COTE_C*TAILLE_COTE_L);
                if ( scanf(" %d",&i)==0) {
                    printf("Pas de caractee ! \n");
                    exit(0);
                }
            }
            if(i==111) {

                break;
            }
            printf("Entrez la colonne :");
            if ( scanf(" %d",&j)==0) {
                printf("Pas de caractere ! \n");
                exit(0);
            }
            printf("\n");
            while ((j<1 ||j>TAILLE_COTE_C*TAILLE_COTE_L) && j!=111) {
                printf("Reessayez avec une colonne entre 1 et %d : ",TAILLE_COTE_C*TAILLE_COTE_L);
                if ( scanf(" %d",&j)==0) {
                    printf("Pas de caractere ! \n");
                    exit(0);
                }
            }
            if (j==111){
                break;
            }
            printf("Entrez la valeur de la case (%d ,%d) ou 111 pour annuler\n",i,j);
            if ( scanf(" %d",&valeur)==0) {
                printf("Pas de caractère ! \n");
                exit(0);
            }

            while ((valeur<1 ||valeur>TAILLE_COTE_C*TAILLE_COTE_L) && valeur!=111) {
                printf("Reessayez entrez la valeur(entre 1-%d) de la case (%d ,%d) ou 111 pour annuler: ",TAILLE_COTE_C*TAILLE_COTE_L,i,j);
                if ( scanf(" %d",&valeur)==0) {
                    printf("Pas de caractere ! \n");
                    exit(0);
                }
            }
            if(valeur==111){
                break;
            }
            tableau[i-1][j-1]=valeur;
            print_tableau_sudoku(tableau);
            if(verifier_contraintes(tableau)==0) {tableau[i-1][j-1]=0;}
        }


    }
    else
    {
        // sinon on genere un sudoku alea

        tableau=genere_sudoku2(1,0);// 1 pour imprimer avec trous, et 0 pour ne pas avoir le sudoku complet et donc la solution


    }

    //Maintenant que le sudoku est rempli selon les souhaits de l'utilisateur
    //On lui propose de le résoudre ou juste de le sauvegarder
    int choix;
    printf("Si vous voulez resoudre ce sudoku tapez 1 \nLe sauvegarder dans un fichier tapez 2\nSinon le mode interactif s'arrete\n" );
    scanf(" %d",&choix);
    if (choix==2){
        char  path[256];
        printf("Donnez le path ou sauvegarder\n");
        scanf(" %s",path);printf("\n");
        save(path,tableau);}
    if (choix==1){

        // on prépare un tableau auxiliaire (que des 0 ou 1 où on va stocker les endroits que le joueur ne peut pas modifier)
        // et un autre tableau contenant le sudoku original si l'utilisateur veut abandonner pour retourner toutes les solutions
        int i,a,b;

        int ** tableau_aux=(int **)malloc(TAILLE * sizeof(int*));
        for( i = 0; i < TAILLE; i++) tableau_aux[i] = (int *)malloc(TAILLE * sizeof(int));


        int ** tableau_aux2=(int **)malloc(TAILLE * sizeof(int*));
        for( i = 0; i < TAILLE; i++) tableau_aux2[i] = (int *)malloc(TAILLE * sizeof(int));

        for ( a=0; a<TAILLE; a++) {
            for ( b=0; b<TAILLE; b++) {
                if (tableau[a][b]==0) {//si c'est un trou, on met des zéros
                    tableau_aux[a][b]=0;
                    tableau_aux2[a][b]=0;
                }
                else  {tableau_aux[a][b]=1;tableau_aux2[a][b]=tableau[a][b];}
            }
        }


        // si le sudoku rentré n'a pas de solution échec
        if (test==1 ) {
            noeud *h;
            h=genhelp(tableau);
            int  help2= cherche_solution_generateur(h);
            if (help2!=1) {
                printf( "Ce sudoku n'a pas de solution, dommage\n");exit(0);
            }

        }

        printf("Le mode RESOLUTION commence\n");
        printf("Essayez de resoudre ce sudoku vous meme (sinon tapez 111) \n \n");
        printf("BONNE CHANCE\n\n");

        //la résolution commence


        print_tableau_sudoku(tableau);

        // tant qu'on n'a pas fini de remplir ou on a remplit mais pas bien on continue de demander des entrées

        while (fini_de_remplir(tableau)==0|| (fini_de_remplir(tableau)==1 && est_solution(tableau)==0)) {

            int i,j;
            printf("Veuillez entrez une ligne et colonne sinon tapez 111 a tout moment pour finir\n");
            printf("Entrez la ligne :");

            if ( scanf(" %d",&i)==0) {// on vérifie bien que l'utilisateur rentre au moins un nombre
                printf("Pas de caractere ! \n");
                exit(0);
            }

            printf("\n");

            if (i==111 ) {
                int w;
                printf("Tapez 1 pour avoir toutes les solutions disponibles a partir de cette grille\nTapez 2 pour celle de la grille obtenue apres le mode remplissage\n");
                printf("Sinon tapez 0 pour arreter le mode interactif.");
                scanf(" %d",&w);printf("\n");
                if(w==1){//si il choisit d'avoir les solutions de la grille en cours de remplissage on prend tableau
                    combien2=0;
                    solveur2(tableau,1);
                    return;}
                if(w==2){//si il choisit d'avoir les solutions de la grille de départ, on prend le tableau_aux_2
                    combien2=0;
                    solveur2(tableau_aux2, 1);
                    return;}
                else{return;}
            }


            printf("Entrez la colonne :");

            if ( scanf(" %d",&j)==0) {
                printf("Pas de caractere ! \n");
                exit(0);
            }


            printf("\n");
            if (j==111) {
                int w;
                printf("Tapez 1 toutes les solutions disponibles a partir de cette grille\nTapez 2 pour celle de la grille obtenue apres le mode remplissage\n");
                printf("Sinon tapez 0 pour arreter le mode interactif.");
                scanf(" %d",&w);printf("\n");
                if(w==1){//si il choisit d'avoir les solutions de la grille en cours de remplissage on prend tableau
                    combien2=0;
                    solveur2(tableau, 1);
                    return;}
                if(w==2){//si il choisit d'avoir les solutions de la grille de départ, on prend le tableau_aux_2
                    combien2=0;
                    solveur2(tableau_aux2, 1);
                    return;}
                else{return;}
            }

            if (tableau_aux[i-1][j-1]==1) {//si la case était pré-remplie, on recommence
                continue;
            }
            printf("Entrez la valeur de la case (%d ,%d)\n",i,j);
            int valeur;
            if ( scanf(" %d",&valeur)==0) {
                printf("Pas de caractere ! \n");
                exit(0);
            }

            if (j==111) {
                int w;
                printf("Tapez 1 toutes les solutions disponibles a partir de cette grille?\nTapez 2 pour celle de la grille obtenue apres le mode remplissage\n");
                printf("Sinon tapez 0 pour arreter le mode interactif.");
                scanf(" %d",&w);printf("\n");
                if(w==1){//si il choisit d'avoir les solutions de la grille en cours de remplissage on prend tableau
                    combien2=0;
                    solveur2(tableau, 1);
                    return;}
                if(w==2){//si il choisit d'avoir les solutions de la grille de départ, on prend le tableau_aux_2
                    combien2=0;
                    solveur2(tableau_aux2, 1);
                    return;}
                else{return;}
            }

            while (valeur<1 ||valeur>TAILLE_COTE_C*TAILLE_COTE_L) {

                printf("Reessayez entrez la valeur(entre 1-%d) de la case (%d ,%d) \n",TAILLE_COTE_C*TAILLE_COTE_L,i,j);

                if ( scanf(" %d",&valeur)==0) {
                    printf("Pas de caractere ! \n");
                    exit(0);
                }
                printf("%d",valeur);
            }


            tableau[i-1][j-1]=valeur;//après toutes ces vérifications, on peut enfin rentrer la valeur
            //sauf qu'il faut d'abord vérifié que les contraintes sont bien satisfaites
            if(verifier_contraintes(tableau)==0) {
                tableau[i-1][j-1]=0;
                printf("Il faut que votre valeur satisfasse les contrainte d'un sudoku\n");
                print_tableau_sudoku(tableau);

            }
            else{print_tableau_sudoku(tableau);}
        }
        printf("\n Bravo !!!!!!!!!!!!!!!\n");//si la boucle se finit sans qu'on en sorte avant, alors le sudoku est résolu
        return;}

    else {return;}

}


// la fonction qui sauvegarde la grille dans un fichier  de notre choix
void save(char * fichier,int ** t){
    FILE *f = fopen(fichier, "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }


    int i,j;
    for ( i=0; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            if (t[i][j]<10) {
                fprintf(f, "%c", t[i][j] +'0');//int en char
            }

            else  fprintf(f, "%c", t[i][j] +'7');//au dessus de 10 on le met en lettre majuscule
        }
        if (i<TAILLE) {
            fprintf(f, "\n");
        }
    }


    fclose(f);
}








