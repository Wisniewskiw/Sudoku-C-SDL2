#include <stdio.h>
#include <stdlib.h>

#include "Lire.h"
#include "interactif.h"
#include "brute_force.h"
#include "structures.h"
#include <sys/time.h>
#include "database_test.h"
#include <time.h>

//test de temps avec une base de données de sudoku avec l'algo
void time_test(char * nom_fichier){


    int i;

    int ** tableau_sudoku=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
    for( i = 0; i < TAILLE; i++) tableau_sudoku[i] = (int *)malloc(TAILLE * sizeof(int));
    FILE * f=fopen(nom_fichier, "r");



    int c=fgetc(f);
    int combien_sudoku=0;
    float temps1=0;
    //float temps2=0;

    while (c!= EOF) {
        int compte=0;
        combien_sudoku++;
        while ((char) c!='\n' && c!=EOF ) { // on remplit le tableau avec les conditions:
            if ((char) c==';') {
                c=fgetc(f);
                while (c!='\n' && c!=EOF) {
                    c=fgetc(f);
                }

                break;
            }


            tableau_sudoku[compte/TAILLE][compte%TAILLE]= c-48;// on remplit ASCII en int
            if (c=='.') {
                tableau_sudoku[compte/TAILLE][compte%TAILLE]=0;
            }

            compte++;
            c=fgetc(f);

        }
        // on calcule le temps avec la class timeval special

        struct timeval start2, stop2;
        double secs2 = 0;

        gettimeofday(&start2, NULL);

        solveur2(tableau_sudoku,0)   ;

        gettimeofday(&stop2, NULL);
        secs2 = (double)(stop2.tv_usec - start2.tv_usec) / 1000000 + (double)(stop2.tv_sec - start2.tv_sec);

        temps1+=secs2;

        c=fgetc(f);


    }
    printf("Le temps total pour %d sudokus est de %f s.\n",combien_sudoku,temps1);
    printf("Temps moyen de l'algo pour un sudoku est de %f s.\n",temps1/combien_sudoku);



}

//permutation d'un tableau dont j'ai besoin pour creer un sudoku alea
void shuffle(int *array, int n)
{srand((unsigned int)time(NULL));
    if (n > 1)
    {
        int i;
        for (i = 0; i < n - 1; i++)
        {
            int j = i + rand()%(n - i);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}
/*
 pour générer une grille complète aleatoire il faut :
 1) commencer avec un sudoku vide.
 2) tirer au hasard un chiffre et sa place et je vérifie si les
 conditions de sudoku sont respectés.
 3) vérifier qu'il y a toujours au moins  une solution au sudoku.
 4) répèter les 3 premières conditions jusqu'au moment où la grille est remplie.

 pour la rendre avec trous (avec des zeros)
 5) faire à l'envers : tirer une place aléatoirement (grâce à la fonction shuffle) effacer son chiffre
 6) tester l'unicité de la solution
 7) si oui on continue
 8) sinon on remet le chiffre et on continue
 9) on termine quand les 81 positions (permutées évidemment) ont été testées

 */




int ** genere_sudoku2(int imprimer_sudoku_alea,int imprime_complet){
    srand((unsigned int) time(NULL));
    int help2;

    int temp2=0;

    noeud *h;
    int i,j;
    //initialisation du tableau
    int ** sudoku=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
    for( i = 0; i < TAILLE; i++) sudoku[i] = (int *)malloc(TAILLE * sizeof(int));

    for ( i=0; i<TAILLE; i++) {
        for ( j=0; j<TAILLE; j++) {
            sudoku[i][j]=0;
        }
    }

    // permutation aleatoire d'un tableau de 81 entrées

    int * permute2=(int *)malloc(sizeof(int)*TAILLE*TAILLE);


    for (i=0; i<TAILLE*TAILLE; i++) {
        permute2[i]=i;
    }
    //pour l'instant ce tableau contient les chiffres 0 a TAILLE*TAILLE dans l'ordre croissant
    shuffle(permute2, TAILLE*TAILLE);
    //maintenant il contient une permutation de 0 à TAILLE*TAILLE


    // les etapes 2)3)4)
    for (i=0; i<TAILLE; i++) {
        for ( j=0; j<TAILLE; j++) {

            temp2=rand()%TAILLE +1;
            sudoku[permute2[i*TAILLE+j]/TAILLE][permute2[i*TAILLE+j]%TAILLE]=temp2;
            //on a les cases aléatoire (selon permute2) avec un nombre aléatoire (temp2)
            while (verifier_contraintes(sudoku)!=1) {
                //si les contraintes du sudoku ne sont pas vérifiées, on recommence jusqu'à ce qu'elle le soient
                sudoku[permute2[i*TAILLE+j]/TAILLE][permute2[i*TAILLE+j]%TAILLE]=rand()%TAILLE +1;
            }

            h=genhelp(sudoku);//crée la liste chainés de contrainte du sudoku
            help2= cherche_solution_generateur(h);//vérifie qu'il existe toujours au moins une solution au sudoku
            while (help2==0) {//si ce n'est pas le cas on recommence
                temp2=rand()%TAILLE +1;
                sudoku[permute2[i*TAILLE+j]/TAILLE][permute2[i*TAILLE+j]%TAILLE]=temp2;
                while (verifier_contraintes(sudoku)!=1) {
                    sudoku[permute2[i*TAILLE+j]/TAILLE][permute2[i*TAILLE+j]%TAILLE]=rand()%TAILLE +1;
                }
                h=genhelp(sudoku);
                help2= cherche_solution_generateur(h);
            }







        }
    }

    //option imprimer le sudoku complet

    if(imprime_complet)  {
        printf("Le sudoku aleatoire complet est le suivant : \n");

        print_tableau_sudoku(sudoku);}

    //maintenant quasiment le meme algo pour trouver un sudoku avec une unique solution

    int * permute=(int *)malloc(sizeof(int)*TAILLE*TAILLE);


    for (i=0; i<TAILLE*TAILLE; i++) {
        permute[i]=i;
    }
    shuffle(permute, TAILLE*TAILLE);
    //Ici on a un tableau permuté de 0 à TAILLE*TAILLE


    int counter;

    // les etapes 5)6)7)8)
    for (counter=0; counter<TAILLE*TAILLE; counter++) {
        int tmp=sudoku[permute[counter]/TAILLE][permute[counter]%TAILLE];
        sudoku[permute[counter]/TAILLE][permute[counter]%TAILLE]=0;
        h=genhelp(sudoku);
        noeud ** solution=initialisation_solution();
        combien2=0;//on remet le nombre de solutions à zéro
        int check=cherche_solution2(h, 0, solution, 0); //on obtient le nombre de solutions du sudoku

        if (check==1) {//si il n'y a qu'une seule solution on passe à l'itération suivante
            continue;
        }
        sudoku[permute[counter]/TAILLE][permute[counter]%TAILLE]=tmp;//sinon on remet la valeur
    }

    if(imprimer_sudoku_alea){
        printf("Le sudoku avec 0 genere a partir du sudoku aleatoire est le suivant : \n");
        print_tableau_sudoku(sudoku);}
    return sudoku;

}



// choisit un sudoku alea parmi le database des sudokus difficiles (fichier special.txt)
int ** alea_sudoku_difficile(char * nom_fichier){
    srand((unsigned int)time(NULL));
    int quel_sudoku=rand()%6343;
    int i;

    int ** tableau_sudoku=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
    for( i = 0; i < TAILLE; i++) tableau_sudoku[i] = (int *)malloc(TAILLE * sizeof(int));
    FILE * f=fopen(nom_fichier, "r");



    int c=fgetc(f);
    int combien_sudoku=0;

    while (c!= EOF && combien_sudoku<=quel_sudoku) {
        int compte=0;
        combien_sudoku++;
        while ((char) c!='\n' && c!=EOF ) { //on remplit le tableau avec les conditions:
            if ((char) c==';') {
                c=fgetc(f);
                while (c!='\n' && c!=EOF) {
                    c=fgetc(f);
                }

                break;
            }


            tableau_sudoku[compte/TAILLE][compte%TAILLE]= c-48;// on remplit ASCII en int
            if (c=='.') {
                tableau_sudoku[compte/TAILLE][compte%TAILLE]=0;
            }

            compte++;
            c=fgetc(f);

        }
               c=fgetc(f);


    }

    return   tableau_sudoku;

}






