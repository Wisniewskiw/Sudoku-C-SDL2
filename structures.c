#include <stdio.h>
#include <stdlib.h>
#include "Lire.h"
#include "structures.h"
#include <limits.h>






// C'est dans ce fichier que la base de notre programme se trouve : la structure noeud



//Début de la construction
//L'idée est d'attacher à la racine (l'header) une liste qui nous aidera a repérer les lignes

noeud * initialisation_grille2()
{
    int nombre_lignes=TAILLE*TAILLE*TAILLE;  //nombre de lignes dans la grille de contraintes
    int nombre_colonnes=4*TAILLE*TAILLE;    //nombre de colonnes dans la grille de contraintes



    //--------
    noeud *header=(noeud*)malloc(sizeof(noeud)); //la racine, le point de départ
    header->noeud_haut=header;
    header->noeud_gauche=header;
    header->noeud_droite=header;
    header->noeud_bas=header;





    //-----------

    noeud **LL=(noeud **)malloc(sizeof(noeud*)*nombre_lignes);//La liste de lignes
    noeud **CC=(noeud **)malloc(sizeof( noeud*)*nombre_colonnes );//La liste de colonnes

    int i,j;
    for ( i=0; i<nombre_lignes; i++) {
        LL[i]=(noeud*) malloc(sizeof(noeud));

    }
    for ( j=0; j<nombre_colonnes; j++) {
        CC[j]=(noeud*) malloc(sizeof(noeud));

    }

    //il faut une liste doublement chainée donc on fait les liens

    //première colonne
    CC[0]->un=0;
    CC[0]->kol=0;

    CC[0]->noeud_gauche=header;
    CC[0]->noeud_bas=CC[0];
    CC[0]->noeud_haut=CC[0];
    header->noeud_droite=CC[0];



    //les autres colonnes
    int l;
    for ( l=1; l<nombre_colonnes-1; l++) {
        CC[l]->kol=l;                               CC[l]->un=0;

        CC[l]->noeud_gauche=CC[l-1];
        CC[l]->noeud_gauche->noeud_droite=CC[l];

        CC[l]->noeud_bas=CC[l];
        CC[l]->noeud_haut=CC[l];
    }

    //la dernière colonne
    CC[nombre_colonnes-1]->kol=nombre_colonnes-1;
    CC[nombre_colonnes-1]->un=0;

    CC[nombre_colonnes-1]->noeud_gauche=CC[nombre_colonnes-2];
    CC[nombre_colonnes-1]->noeud_gauche->noeud_droite=CC[nombre_colonnes-1];

    CC[nombre_colonnes-1]->noeud_bas=CC[nombre_colonnes-1];
    CC[nombre_colonnes-1]->noeud_haut=CC[nombre_colonnes-1];
    CC[nombre_colonnes-1]->noeud_droite=header;
    header->noeud_gauche=CC[nombre_colonnes-1];


    //la même chose pour former les lignes

    LL[0]->lin=0;

    LL[0]->noeud_haut=header;

    LL[0]->noeud_droite=LL[0];
    LL[0]->noeud_gauche=LL[0];
    header->noeud_bas=LL[0];



    for ( l=1; l<nombre_lignes-1; l++) {
        LL[l]->lin=l;

        LL[l]->noeud_haut=LL[l-1];
        LL[l]->noeud_haut->noeud_bas =LL[l];

        LL[l]->noeud_droite=LL[l];
        LL[l]->noeud_gauche=LL[l];
    }

    LL[nombre_lignes-1]->lin=nombre_lignes-1;


    LL[nombre_lignes-1]->noeud_haut=LL[nombre_lignes-2];
    LL[nombre_lignes-1]->noeud_haut->noeud_bas=LL[nombre_lignes-1];

    LL[nombre_lignes-1]->noeud_gauche=LL[nombre_lignes-1];
    LL[nombre_lignes-1]->noeud_droite=LL[nombre_lignes-1];
    LL[nombre_lignes-1]->noeud_bas=header;
    header->noeud_haut=LL[nombre_lignes-1];


    return header;// on retourne la racine

}



//le programme pour insérer un noeud grâce à sa position (ligne, colonne)
void inserer_noeud2(noeud * H,int ligno,int colo){

    noeud *bonne_colo= H->noeud_droite;//on commence à la première colonne

    //trouver la bonne colonne
    while (bonne_colo->kol !=colo) {
        bonne_colo=bonne_colo->noeud_droite;
    }
    //update de 1
    bonne_colo->un=bonne_colo->un +1;

    //allocation new noeud
    noeud * new=(noeud *)malloc(sizeof(noeud));

    //update des informations
    new->lin=ligno;
    new->kol=colo;
    new->pere=bonne_colo;

    //on cherche la bonne ligne cette fois en "descendant" dans la colonne
    noeud *bonne_col=bonne_colo;
    while (bonne_col->noeud_bas!=bonne_colo
           && bonne_col->noeud_bas->lin<ligno)
    {
        bonne_col=bonne_col->noeud_bas;
    }

    // on fait les liens en haut et en bas maintenant qu'on a la bonne place

    new->noeud_haut=bonne_col;
    new->noeud_bas=bonne_col->noeud_bas;

    bonne_col->noeud_bas->noeud_haut=new;
    bonne_col->noeud_bas=new;



    //maintenant on refait le même principe pour placer dans la ligne
    noeud* bonne_lin=H->noeud_bas;

    while (bonne_lin->lin!= ligno) {//on cherche la bonne ligne
        bonne_lin= bonne_lin->noeud_bas;
    }

    noeud * bonne_lin_col=bonne_lin;

    //on cherche la bonne colonne en "avancant" sur la ligne
    while (bonne_lin_col->noeud_droite !=bonne_lin && bonne_lin_col->noeud_droite->kol<colo) {
        bonne_lin_col=bonne_lin_col->noeud_droite;
    }


    //on insert en faisaint les liiens à droite à gauche
    new->noeud_gauche=bonne_lin_col;
    new->noeud_droite=bonne_lin_col->noeud_droite;
    bonne_lin_col->noeud_droite->noeud_gauche=new;
    bonne_lin_col->noeud_droite=new;

}



//Choisir la colonne avec le moins de 1

noeud * colonne_nombre_min_1( noeud* header){
    int max=INT_MAX; //initialisation de minimum, on prend le plus grand entier

    noeud* i,*col;
    //col=NULL;
    for (i=header->noeud_droite; i!=header;i=i->noeud_droite ) {
        if (i->un<max) {
            max=i->un;
            col=i;
        }
    }

    return col; // retourne la colonne
}




void enlever_noeud_horizontale(noeud *node){ //enleve un noeud dans une ligne
    node->noeud_gauche->noeud_droite=node->noeud_droite;
    node->noeud_droite->noeud_gauche=node->noeud_gauche;
}


void restorer_noeud_horizontale(noeud *node){ // le remettre
    node->noeud_gauche->noeud_droite=node;
    node->noeud_droite->noeud_gauche=node;
}

void enlever_noeud_verticale(noeud *node){ // enlever noeud dans une colonne
    node->noeud_haut->noeud_bas=node->noeud_bas;
    node->noeud_bas->noeud_haut=node->noeud_haut;

}


void restorer_noeud_verticale(noeud *node){ //le remettre
    node->noeud_haut->noeud_bas=node;
    node->noeud_bas->noeud_haut=node;

}


void couvrir_colonne2(noeud *colonne){//couvre tout la colonne
    noeud *i,*j;
    enlever_noeud_horizontale(colonne);
    i=colonne->noeud_bas;
    while (i!=colonne) {
        j=i->noeud_droite;
        while (j!=i) {
            enlever_noeud_verticale(j);
            j->pere->un= j->pere->un -1;
            j=j->noeud_droite;
        }
        i=i->noeud_bas;
    }

}





void decouvrir_colonne2(noeud *colonne){//remet la colonne
    noeud *i,*j;

    for (i=colonne->noeud_haut; i!=colonne; i=i->noeud_haut) {
        for (j=i->noeud_gauche; j!=i; j=j->noeud_gauche) {
            (j->pere->un)++;
            restorer_noeud_verticale(j);
        }
    }
    restorer_noeud_horizontale(colonne);
}





//le programme qui va nous permettre d'afficher une solution
void   print_solution2(noeud *solution[])
{
    int i,k;
    printf("\n");

    int ** tableau_sudoku=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
    for(i = 0; i < TAILLE; i++) tableau_sudoku[i] = (int *)malloc(TAILLE * sizeof(int));

    int linia,kolumna,numer;
    for (k = 0; k < TAILLE*TAILLE && solution[k] != NULL; k++) {
        linia = (solution[k]->lin)/(TAILLE*TAILLE);
        kolumna = (solution[k]->lin - linia* TAILLE*TAILLE)/TAILLE;
        numer = (solution[k]->lin)%TAILLE + 1;
        tableau_sudoku[linia][kolumna] = numer;
    }// ici grâce au numéro de la ligne dans la solution on peut en déduire la ligne, colonne et valeur dans le sudoku


    print_tableau_sudoku(tableau_sudoku);//on l'affiche (avec des tirets pour cette version)
    printf("\n");
}


//même principe, la seule différence est le print
void   print_solution2_evaluation(noeud *solution[])
{
    int i,k;
    int ** tableau_sudoku=(int **)malloc(TAILLE * sizeof(int*));//malloc du tableau
    for(i = 0; i < TAILLE; i++) tableau_sudoku[i] = (int *)malloc(TAILLE * sizeof(int));

    int linia,kolumna,numer;
    for ( k = 0; k < TAILLE*TAILLE && solution[k] != NULL; k++) {
        linia = (solution[k]->lin)/(TAILLE*TAILLE);
        kolumna = (solution[k]->lin - linia* TAILLE*TAILLE)/TAILLE;
        numer = (solution[k]->lin)%TAILLE + 1;
        tableau_sudoku[linia][kolumna] = numer;
    }


    print_tableau_sudoku_version_evaluation(tableau_sudoku);//on l'affiche (sans tirets) comme demandé dans l'énoncé
    printf("\n");
}





int combien2=0;//le nombre de solutions

int cherche_solution2(noeud * h,int i, noeud* solution[],int imprimer){



    if (h->noeud_droite == h){combien2++;//si on a atteint la fin, on a une solution donc on incrémente
        if (imprimer) {
            printf("Solution nr %d \n\n",combien2);
            print_solution2(solution);// si on a l'option imprimer, on les affiche
        }
        return combien2;




    }

    noeud * c=colonne_nombre_min_1(h);// on trouve la colonne avec le moins de 1

    couvrir_colonne2(c); //on la couvre

    noeud * row,*new1,*new2;


    for (row=c->noeud_bas; row!=c; row=row->noeud_bas) {
        solution[i]=row;    //on rajoute la ligne à la solution
        for (new1=row->noeud_droite; new1!=row; new1=new1->noeud_droite) {
            couvrir_colonne2(new1->pere); //on couvre toutes les colonnes qui contiennent un noeud dans la ligne
        }
        cherche_solution2(h, i+1, solution,imprimer);// on fait la récurrence et on incrémente i pour determiner la prochaine ligne de la solution

        for (new2=row->noeud_gauche; new2!=row; new2=new2->noeud_gauche) {
            decouvrir_colonne2(new2->pere);//une fois que la récurrence est fini, on remet toutes les colonnes précédemment enlver
        }
        //la boucle recommence et choisit une autre ligne, ce qui nous permet d'avoir toutes les solutions
    }
    decouvrir_colonne2(c);//on découvre la première colonne
    return combien2;

}


//exactement le même programme, la seule différence est dans le print
int cherche_solution2_evaluation(noeud * h,int i, noeud* solution[],int imprimer){



    if (h->noeud_droite == h){combien2++;
        if (imprimer==1) {
            print_solution2_evaluation(solution);//on imprime la solution sous la forme demandé dans l'énoncé
        }
        return combien2;
    }

    noeud * c=colonne_nombre_min_1(h);
    couvrir_colonne2(c);
    noeud * row,*new1,*new2;


    for (row=c->noeud_bas; row!=c; row=row->noeud_bas) {
        solution[i]=row;
        for (new1=row->noeud_droite; new1!=row; new1=new1->noeud_droite) {
            couvrir_colonne2(new1->pere);
        }
        cherche_solution2_evaluation(h, i+1, solution,imprimer);

        for (new2=row->noeud_gauche; new2!=row; new2=new2->noeud_gauche) {
            decouvrir_colonne2(new2->pere);
        }
    }
    decouvrir_colonne2(c);
    return combien2;
}



//permet de créer une solution mais on sait qu'elle contiendra TAILLE*TAILLE lignes (vide pour l'instant)
noeud ** initialisation_solution(){
    int i;
    noeud **solution= (noeud **) malloc(sizeof(noeud*)* TAILLE*TAILLE);
    for (i=0; i<TAILLE*TAILLE; i++) {
        solution[i]=NULL;
    }
    return solution;
}



//le solveur qui renvoie sous la forme avec des tirets
void solveur2(int ** tableau3,int imprimer){

    if (imprimer==1) {
        print_tableau_sudoku(tableau3);
    }

    noeud * h=initialisation_grille2();//on initialise la grille
    noeud ** solution=initialisation_solution();//on initialise la solution
    h=genhelp(tableau3);//on crée la matrice de contrainte grâce au programme ci-dessous

    cherche_solution2(h, 0, solution,imprimer);//on cherche les solutions


}




//le solveur qui renvoie sous la forme demandé dans l'énoncé (même principe)
void solveur2_evaluation(int ** tableau3){

    noeud * h=initialisation_grille2();
    noeud ** solution=initialisation_solution();
    h=genhelp(tableau3);

    cherche_solution2_evaluation(h, 0, solution,1);




}





// initialisation de la grille de contrainte

noeud* genhelp(int** tableau3){


    noeud * h=initialisation_grille2();
    int i,j,k;

    for ( i=0; i<TAILLE; i++) {
        for ( j=0; j<TAILLE; j++) {
            if (tableau3[i][j]==0) {//si le sudoku contient un zéro, alors on ajoute un nombre TAILLE de lignes de contraintes
                for ( k=0; k<TAILLE; k++) {
                    inserer_noeud2(h, TAILLE*TAILLE*i+TAILLE*j+k, TAILLE*i+j);//contrainte sur avoir une valeur dans la case

                    inserer_noeud2(h, TAILLE*TAILLE*i+TAILLE*j+k, TAILLE*TAILLE+TAILLE*i+k);//contrainte sur la ligne

                    inserer_noeud2(h, TAILLE*TAILLE*i+TAILLE*j+k, TAILLE*TAILLE*2+TAILLE*j+k);//contrainte sur la colonne

                    inserer_noeud2(h, TAILLE*TAILLE*i+TAILLE*j+k, TAILLE*TAILLE*3+ TAILLE*(TAILLE_COTE_C*(i/TAILLE_COTE_C)+j/TAILLE_COTE_L)+k);//contrainte sur le bloc
                }
            }


            else    //si il contient une valeur, on ajoute une seule ligne de contrainte, sinon même principe
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
    //on efface toutes les têtes de lignes puisque on n'en a plus besoin à présent
    return h;

}

//fonction qui vérifie si il y a au moins une solution à une matrice de contrainte
int cherche_solution_generateur(noeud * h){



    if (h->noeud_droite == h){
        return 1;   //si on a réussi à couvrir toutes les colonnes, c'est bon, il existe une solution




    }

    noeud * c=colonne_nombre_min_1(h);

    couvrir_colonne2(c);

    noeud * row,*new1,*new2;


    for (row=c->noeud_bas; row!=c; row=row->noeud_bas) {
        for (new1=row->noeud_droite; new1!=row; new1=new1->noeud_droite) {
            couvrir_colonne2(new1->pere);
        }
        if  (cherche_solution_generateur(h)==1) return 1;

        for (new2=row->noeud_gauche; new2!=row; new2=new2->noeud_gauche) {
            decouvrir_colonne2(new2->pere);
        }
    }
    decouvrir_colonne2(c);
    return 0;


}





