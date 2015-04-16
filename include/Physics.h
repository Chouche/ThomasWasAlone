#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Personnage.h"
#include "Color3f.h"
#include "Taille2D.h"
#include "Bloc.h"

void MooveRight(Personnage * perso);
int Collision(Personnage perso, Bloc bloc );


#endif