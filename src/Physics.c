#include "../include/Physics.h"

void MooveRight(Personnage * perso){
	perso->position.x=perso->position.x+1;
}

int Collision(Personnage perso, Bloc bloc ){
	if(perso.position.x >=  bloc.position.x
					&& perso.position.x < bloc.position.x + bloc.taille.x
					&& perso.position.y >= bloc.position.y
					&& perso.position.y  <= bloc.position.y + bloc.taille.y
					){
		return 1;
	}
	else{
		return 0;
	}

}