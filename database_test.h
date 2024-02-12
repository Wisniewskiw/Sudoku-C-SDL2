#ifndef sdl2_testing_database_test_h
#define sdl2_testing_database_test_h



#include <stdio.h>
#include <stdlib.h>

#include "Lire.h"
#include "interactif.h"
#include "brute_force.h"
#include "structures.h"
#include <sys/time.h>


void time_test(char * nom_fichier);
void shuffle(int *array, int n);
int ** genere_sudoku2(int, int);

int ** alea_sudoku_difficile(char * nom_fichier);


#endif
