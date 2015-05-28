#include "../include/MoovePerso.h"

void MooveRight(Personnage * perso){

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
    glTranslatef(-1,0,0);
	perso->position.x=perso->position.x+1;
}

void MooveLeft(Personnage * perso){
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
    glTranslatef(1,0,0);
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
