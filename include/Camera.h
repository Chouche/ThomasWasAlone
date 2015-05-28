#ifndef CAMERA_H_
#define CAMERA_H_

#include "Personnage.h"
#include "Bloc.h"
#include "../include/Collision.h"

int MooveCameraLeft(Personnage perso,Bloc blocs[],int nb_bloc);
int MooveCameraRight(Personnage perso,Bloc blocs[],int nb_bloc);
#endif