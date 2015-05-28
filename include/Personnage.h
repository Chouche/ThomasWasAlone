#ifndef PERSONNAGE_H_
#define PERSONNAGE_H_

#include "Point2D.h"
#include "Color3f.h"
#include "Taille2D.h"

typedef struct {
    Point2D position;
    Taille2D taille;
    Color3f color;
    int id;
    float t;
    Point2D positionDep;
} Personnage;

Personnage Personnage2D(Point2D position, Taille2D taille, Color3f color, int id, float t,Point2D positionDep) ;

void DessinPersonnageCarre(Personnage perso);

#endif