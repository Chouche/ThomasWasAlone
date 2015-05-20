#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Personnage.h"
#include "Color3f.h"
#include "Taille2D.h"
#include "Bloc.h"


void Gravity(Personnage * perso,int t, float v_init);
void Fall(Personnage * perso,int t);

#endif