#include "../include/Bloc.h"
#include "../include/Dessin.h"




Bloc Bloc2D(Point2D position, Taille2D taille, Color3f color, int id) {
    Bloc b;
    b.position = position;
    b.taille = taille;
    b.color = color;
    b.id = id;
    return b;
}


void DessinBlocCarre(Bloc bloc, int filled){
	dessinCarre(filled,bloc.color.r,bloc.color.g,bloc.color.b,bloc.position.x,bloc.position.y,bloc.taille.x,bloc.taille.y);
}

