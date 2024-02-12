#ifndef sdl2_testing_Lire_h
#define sdl2_testing_Lire_h
extern int TAILLE ;
extern int TAILLE_COTE_L;
extern int TAILLE_COTE_C;

int ** lire_sudoku_fichier(char* );
int verifier_contraintes(int **);
void print_tableau_sudoku(int ** );
int combien_zeros(int** );
int racinecarre(int T);


int Taille_ligne(char *nom_fichier);
void print_tableau_sudoku_version_evaluation(int ** sudoku);
char* concat(const char *s1, const char *s2);


#endif
