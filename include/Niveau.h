#ifndef NIVEAU_H_
#define NIVEAU_H_

#include "Personnage.h"
#include "Bloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void initializeLvl(Personnage tabPerso[], Bloc tabBlocs[], Bloc tabBlocsFinaux[], int * nb_perso,int * nb_bloc,char* f);
void recupParametres(float* px, float* py, float* tx, float* ty, float* r, float* g, float* b,int* id, char* str1);
	
#endif