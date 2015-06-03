#ifndef CREDIT_H_
#define CREDIT_H_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "Bloc.h"
#include "Personnage.h"
#include "Dessin.h"

void DessinPersoPluie(int nb_perso,int nb_pluie, int currentPerso,Personnage tabPerso[],Bloc tabPluie[]);
void MooveYeuxTotoro(int right, int left, float *yt, float *xt, Personnage tabPerso[]);
void DessinYeuxTotoro(float yt, float xt);
#endif