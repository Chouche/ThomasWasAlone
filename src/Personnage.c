#include "../include/Personnage.h"
#include "../include/Dessin.h"




Personnage Personnage2D(Point2D position, Taille2D taille, Color3f color, int id) {
    Personnage p;
    p.position = position;
    p.taille = taille;
    p.color = color;
    p.id = id;
    return p;
}


void DessinPersonnageCarre(Personnage perso){
	
	dessinCarre(1,perso.color.r,perso.color.g,perso.color.b,perso.position.x,perso.position.y,perso.taille.x,perso.taille.y);
}

