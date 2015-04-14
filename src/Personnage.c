#include "../include/Personnage.h"
#include "../include/Dessin.h"


Personnage Personnage2D(Point2D position, Taille2D taille, Color3f color) {
    Personnage p;
    p.position = position;
    p.taille = taille;
    p.color = color;
    return p;
}

void DessinPersonnageCarre(Personnage perso){
	
	float PositionX=perso.position.x;
	float PositionY=perso.position.y;
	float tailleX=perso.taille.x;
	float tailleY=perso.taille.y;
	float red=perso.color.r;
	float green=perso.color.g;
	float blue=perso.color.b;

	dessinCarre(1,red,green,blue,PositionX,PositionY,tailleX,tailleY);
}