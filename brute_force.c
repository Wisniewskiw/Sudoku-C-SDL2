#include <stdio.h>
#include <stdlib.h>

#include "Lire.h"
#include "interactif.h"
#include "brute_force.h"

int SOLUTIONS = 0;//combien de solutions
int ITERATIONS = 0;//combien d'itérations

//METHODE BRUTE FORCE BACKTRACKING
void brute_force(int **sudoku,int recurrance,int imprimer){

    int ligne,colonne;

    if (recurrance==TAILLE*TAILLE) {
        SOLUTIONS++;                        //si on arrive à la dernière case on incrémante de 1 le nombre de solutions
        printf("Solution nr %d\n",SOLUTIONS);
        if (imprimer==1) print_tableau_sudoku(sudoku);
    }
    else
    {
        ligne=recurrance/TAILLE;            //numéro de la ligne dans la récurrence
        colonne=recurrance % TAILLE;        //numéro de la colonne dans la récurrence
        if (sudoku[ligne][colonne]!=0) {
            brute_force(sudoku,recurrance+1,imprimer); //si la case  est remplie on continue
        }
        else
        {

            int i;
            for (i=1; i<TAILLE+1; i++) { // on teste les possibilitÈs
                sudoku[ligne][colonne]=i;

                if (verifier_contraintes(sudoku)==0) {
                    sudoku[ligne][colonne]=0;continue; //si contrainte non satisfaite on continue
                }
                if (verifier_contraintes(sudoku)==1) {
                    brute_force(sudoku, recurrance+1,imprimer); //on reprends a la case suivante
                    sudoku[ligne][colonne]=0;// on reprends pour les autres solutions
                }

            }
        }






    }


}
