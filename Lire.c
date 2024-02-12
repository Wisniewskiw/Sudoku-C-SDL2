#include <stdio.h>
#include <stdlib.h>
#include "Lire.h"
#include<string.h>


//initialisation des dimensions de sudoku, on va s'en servir tout le temps
int TAILLE=0;
int TAILLE_COTE_L=0;
int TAILLE_COTE_C=0;

//calcule la taille de sudoku à partir d'un fichier

int Taille_ligne(char *nom_fichier){
    int max_col=0;
    FILE * f=fopen(nom_fichier, "r");
    int c=fgetc(f);
    //dans le cas normal on compte jusqua \n
    //dans le cas du fichier special.txt on s'arrete à ;
    while ((char) c!='\n' && c!=EOF &&  (char)c!=';') {
        max_col++;
        c=fgetc(f);
    }
    fclose(f);
    return max_col;
}

//Fonction qui nous permettra de vérifier si un nombre est carré ou non
int racinecarre(int T){

    int i=1;
    while (i*i <T) {
        i++;
    }
    return i;
}

//A partir d'un fichier en format sudoku, renvoie une matrice contenant les valeurs du sudoku
int ** lire_sudoku_fichier(char* nom_fichier){


    //initialisation de constantes et la matrice
    int max_col=0;
    int max_lin=1;
    int count=0;

    TAILLE=Taille_ligne(nom_fichier);
    TAILLE_COTE_C=racinecarre(TAILLE);
    TAILLE_COTE_L=TAILLE_COTE_C;


    int ** tableau_sudoku=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
    int i;
    for( i = 0; i < TAILLE; i++) tableau_sudoku[i] = (int *)malloc(TAILLE * sizeof(int));


    //lire  fichier txt
    FILE * f=fopen(nom_fichier, "r");
    int c=fgetc(f);


    while (c!= EOF) {

        while ((char) c!='\n' && c!=EOF) { // on remplit le tableau avec les conditions:
            if (max_col>TAILLE ||max_lin>TAILLE) { //trop de lignes ou collones= fail

                printf("Fichier txt mal ecrit \n");exit(0);
            }


            tableau_sudoku[max_lin-1][count]= c-48;// on remplit ASCII en int
            if (c-'0'>9) {
                tableau_sudoku[max_lin-1][count]= c-55; //pour les sukodus plus grand A->10 B->11 etc
            }

            count++;
            c=fgetc(f);

        }
        if (max_col<count) {
            max_col=count;
        }
        count=0;
        max_lin++;


        c=fgetc(f);


    }


    fclose(f);
    return tableau_sudoku;  // la matrice sudoku
}




int verifier_contraintes(int **sudoku){// vérifie les contraintes du sudoku (il peut contenir des 0)

    //vérification des lignes avec l'aide d'un tableau de booléen
    int i,j;
    for ( i=0; i<TAILLE; i++) {
        int *flag = calloc(TAILLE+1, sizeof(int));//0 partout le tableau de verification
        // 1 si un chiffre est utilisé dans une ligne
        for ( j=0; j<TAILLE; j++) {
            if (flag[sudoku[i][j]]==1 && sudoku[i][j]!=0) {
                return 0;//si il était deja present => échec
            }
            flag[sudoku[i][j]]=1;
        }
        free(flag);
    }


    //colonnes
    for ( i=0; i<TAILLE; i++) {
        int *flag = calloc(TAILLE+1, sizeof(int));
        for ( j=0; j<TAILLE; j++) {
            if (flag[sudoku[j][i]]==1 && sudoku[j][i]!=0) {
                return 0;
            }
            flag[sudoku[j][i]]=1;
        }
        free(flag);
    }


    //blocs
    for(i = 0; i < TAILLE; i += TAILLE_COTE_C){
        for( j = 0; j < TAILLE; j+= TAILLE_COTE_L){
            int *flag = calloc(TAILLE+1, sizeof(int));
            int cote_i,cote_j;
            for(cote_i = 0; cote_i < TAILLE_COTE_C; cote_i++){
                for(cote_j = 0; cote_j < TAILLE_COTE_L; cote_j++){

                    if(flag[sudoku[i+cote_i][j+cote_j]]==1 && sudoku[i+cote_i][j+cote_j]!=0)
                    {return 0;}

                    flag[sudoku[i+cote_i][j+cote_j]]=1;
                }
            }
            free(flag);

        }
    }

    return 1;

}





//imprime le sudoku dans une manière personalisée (avec les tirets)

void print_tableau_sudoku(int ** sudoku){
    if(verifier_contraintes(sudoku)==1){
        //vérifie si les contraintes sont respectées, sinon juste un print et le programme ne fait rien

        int i,j,k;
        for (k=1; k<TAILLE; k++) {
            printf("----");
        }
        printf("\n");
        for (i=0; i<TAILLE; i++) {
            printf("|");
            for (j=0; j<TAILLE; j++) {

                if (sudoku[i][j]<10) {
                    printf(" %c ",(char)(sudoku[i][j]+48));//on change int en char
                }
                else
                    printf(" %c ",(char)(sudoku[i][j]+55));//si c'est plus grand que 10 on vaut  des lettres

                if ((j+1)%TAILLE_COTE_L==0) {
                    printf("|");
                }

            }
            printf("\n");
            if ((i+1)%TAILLE_COTE_C==0) {
                for (k=1; k<TAILLE; k++) {
                    printf("----");
                }
                printf("\n");

            }
        }

    }
    else printf("Les contraintes ne sont pas satisfaites\n");

}



//imprime le tableau pour la version standard

void print_tableau_sudoku_version_evaluation(int ** sudoku){
    if(verifier_contraintes(sudoku)==1){//vŽrifie si les contraintes sont respectées

        int i,j;


        for (i=0; i<TAILLE; i++) {

            for (j=0; j<TAILLE; j++) {

                if (sudoku[i][j]<10) {
                    printf("%c",(char)(sudoku[i][j]+48));
                }
                else
                    printf("%c",(char)(sudoku[i][j]+55));



            }
            printf("\n");
        }

    }
    else printf("Les contraintes ne sont pas satisfaites\n");

}




//Trouve le nombre de zeros dans une grille de sudoku
int combien_zeros(int** sudoku){
    int out=0;
    int i , j;
    for ( i=0; i<TAILLE; i++) {
        for (j=0; j<TAILLE; j++) {
            if (sudoku[i][j]==0) {
                out++;
            }
        }
    }
    return out;
}

//fonction pour concatener deux strings
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}



