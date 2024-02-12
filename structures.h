#ifndef sdl2_testing_structures_h
#define sdl2_testing_structures_h
extern int  combien2;//le nombre de solutions, on le remet toujours à zéros avant de commencer à résoudre

struct noeud {
    struct noeud *noeud_gauche, *noeud_droite, *noeud_haut, *noeud_bas;
    int lin,kol; //coordonnées lignes et colonnes
    int un; //nombre de un
    struct noeud* pere;//pour savoir dans quelle colonne on se trouve
};

typedef struct noeud noeud;

void enlever_noeud_horizontale(noeud *node);

void enlever_noeud_verticale(noeud *node);

void restorer_noeud_horizontale(noeud *node);
void restorer_noeud_verticale(noeud *node);

noeud ** initialisation_solution(void);


noeud * initialisation_grille2(void);
void inserer_noeud2(noeud * H,int ligno,int colo);
void solveur2(int ** tableau3,int imprimer);


int cherche_solution2(noeud * H,int i, noeud* solution[],int imprimer);

void decouvrir_colonne2(noeud *colonne);
void couvrir_colonne2(noeud *colonne);
noeud * colonne_nombre_min_1( noeud* header);


void   print_solution2(noeud *solution[]);
noeud* genhelp(int** tableau3);
int cherche_solution_generateur(noeud * h);
int cherche_solution2_evaluation(noeud * h,int i, noeud* solution[],int imprimer);
void   print_solution2_evaluation(noeud *solution[]);
void solveur2_evaluation(int ** tableau3);



#endif
