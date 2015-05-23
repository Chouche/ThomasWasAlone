#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Personnage.h"
#include "Color3f.h"
#include "Taille2D.h"
#include "Bloc.h"


void Gravity(Personnage * perso,float t, float v_init);
int Dead(Personnage * perso);
void Physics( Personnage * perso, int nb_bloc, Bloc blocs[],float * t, int * up, int currentPerso );


#endif