#ifndef COLLISION_H_
#define COLLISION_H_

#include "Personnage.h"
#include "Color3f.h"
#include "Taille2D.h"
#include "Bloc.h"
#include <stdio.h>
#include <math.h>



int CollisionHD(Personnage perso, Bloc bloc );
int CollisionHG(Personnage perso, Bloc bloc );
int CollisionBD(Personnage perso, Bloc bloc );
int CollisionBG(Personnage perso, Bloc bloc );
int PosCollision(Personnage perso);

float DistanceAB(float x1, float y1, float x2, float y2);
#endif