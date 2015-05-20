#include "../include/MoovePerso.h"

void MooveRight(Personnage * perso){
	perso->position.x=perso->position.x+1;
}

void MooveLeft(Personnage * perso){
	perso->position.x=perso->position.x-1;
}

//Fonction pour lrs test
void MooveUp(Personnage * perso){
	perso->position.y=perso->position.y+1;
}

//Fonction pour lrs test
void MooveDown(Personnage * perso){
	perso->position.y=perso->position.y-1;
}
