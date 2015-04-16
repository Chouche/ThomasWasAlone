#ifndef BLOC_H_
#define BLOC_H_

#include "Point2D.h"
#include "Color3f.h"
#include "Taille2D.h"

typedef struct {
    Point2D position;
    Taille2D taille;
    Color3f color;
} Bloc;

Bloc Bloc2D(Point2D position, Taille2D taille, Color3f color) ;

void DessinBlocCarre(Bloc bloc);

#endif