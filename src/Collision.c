#include "../include/Collision.h"
/*
void InitializeCollision(int* collisionHG, int* collisionBG, int* collisionHD, int* collisionBD, int nb_bloc) {
	int i;

	for(i = 0; i < nb_bloc; i++){
      collisionHG[i] = 0;
      collisionHD[i] = 0;
      collisionBG[i] = 0;
      collisionBD[i] = 0;
    }

}*/

int CollisionBG(Personnage perso, Bloc bloc ){

	int gauche;
	if(perso.position.x >=  bloc.position.x
					&& perso.position.x-1 < bloc.position.x + bloc.taille.x
					&& perso.position.y-0.5 >= bloc.position.y
					&& perso.position.y-0.5  <= bloc.position.y + bloc.taille.y
					){
		
			//Si droite = 1, le bloc est à Gauche
			if(DistanceAB(bloc.position.x,bloc.position.y+bloc.taille.y,perso.position.x,perso.position.y) > DistanceAB(bloc.position.x,bloc.position.y+bloc.taille.y,bloc.position.x+bloc.taille.x,bloc.position.y+bloc.taille.y))
				gauche = 1;

			//Si le droite = 2, le bloc est en Bas
			else gauche = 2;

			return gauche;
	}
	else{
		
		if (perso.position.x==bloc.position.x+bloc.taille.x && perso.position.y+(perso.taille.y/3) > bloc.position.y && perso.position.y+(perso.taille.y/3) < bloc.position.y+bloc.taille.y)
		{
			gauche = 1;
		}
		
		else
		{
			gauche = 0;

		}	
		return gauche;
	}
	
					
}

int CollisionBD(Personnage perso, Bloc bloc ){

int droite;	
if(perso.position.x+perso.taille.x >=  bloc.position.x
					&& perso.position.x+perso.taille.x-1 < bloc.position.x + bloc.taille.x
					&& perso.position.y-0.5 >= bloc.position.y
					&& perso.position.y-0.5  <= bloc.position.y + bloc.taille.y
					){

			//Si droite = 1, le bloc e*xcd74st à droite
			if(DistanceAB(bloc.position.x+bloc.taille.x,bloc.position.y+bloc.taille.y,perso.position.x+perso.taille.x,perso.position.y) > DistanceAB(bloc.position.x,bloc.position.y+bloc.taille.y,bloc.position.x+bloc.taille.x,bloc.position.y+bloc.taille.y))
				droite= 1;
			//Si le droite = 2, le bloc est en Bas
			else droite = 2;

			return droite;

	}

	else{
		
		if (perso.position.x+perso.taille.x==bloc.position.x && perso.position.y+(perso.taille.y/3) > bloc.position.y && perso.position.y+(perso.taille.y/3) < bloc.position.y+bloc.taille.y)
		{
			droite = 1;
		}
		else
		{
			droite = 0;
		}
		
		return droite;
	}
}

int CollisionHG(Personnage perso, Bloc bloc ){

int gauche;
if(perso.position.x-1 >=  bloc.position.x
					&& perso.position.x-1 < bloc.position.x + bloc.taille.x
					&& perso.position.y+perso.taille.y+0.5 >= bloc.position.y
					&& perso.position.y+perso.taille.y+0.5  <= bloc.position.y + bloc.taille.y
					){

			//Si gauche = 1, le bloc est à Gauche
			if(DistanceAB(bloc.position.x,bloc.position.y,perso.position.x,perso.position.y+perso.taille.y) > DistanceAB(bloc.position.x+bloc.taille.x,bloc.position.y,bloc.position.x,bloc.position.y))
				gauche= 1;
			//Si le gauche = 2, le bloc est en haut
			else gauche = 2;

			return gauche;
	}
	else{
		if (perso.position.x==bloc.position.x+bloc.taille.x && perso.position.y+(perso.taille.y*2/3) > bloc.position.y && perso.position.y+(perso.taille.y*2/3) < bloc.position.y+bloc.taille.y)
		{
			return 1;
		}
		return 0;
	}
}


int CollisionHD(Personnage perso, Bloc bloc ){

	int droite;
	if(perso.position.x+perso.taille.x >=  bloc.position.x
						&& perso.position.x+perso.taille.x < bloc.position.x + bloc.taille.x
						&& perso.position.y+perso.taille.y+0.5 >= bloc.position.y
					 	&& perso.position.y+perso.taille.y+0.5  <= bloc.position.y + bloc.taille.y
						){


			//Si droite = 1, le bloc est à droite
			if(DistanceAB(bloc.position.x+bloc.taille.x,bloc.position.y,perso.position.x+perso.taille.x,perso.position.y+perso.taille.y) > DistanceAB(bloc.position.x+bloc.taille.x,bloc.position.y,bloc.position.x,bloc.position.y))
				droite= 1;
			//Si le droite = 2, le bloc est en haut
			else droite = 2;

			return droite;

	}

	else{
		if (perso.position.x+perso.taille.x==bloc.position.x && perso.position.y+(perso.taille.y*2/3) > bloc.position.y && perso.position.y+(perso.taille.y*2/3) < bloc.position.y+bloc.taille.y)
		{
			return 1;
		}
		return 0;
	}
}
/*
void RechercheCollision(Personnage henry, Bloc* blocs, int* collisionHG, int* collisionBG, int* collisionHD, int* collisionBD, int nb_bloc) {
	int i;

	for(i = 0; i < nb_bloc; i++) {
      collisionHG[i] = CollisionHG(henry,blocs[i]);
      collisionHD[i] = CollisionHD(henry,blocs[i]);
      collisionBG[i] = CollisionBG(henry,blocs[i]);
      collisionBD[i] = CollisionBD(henry,blocs[i]);
    }
}*/

float DistanceAB(float x1, float y1, float x2,float y2 )
{

	float dx,dy,d;
	dx = x2 - x1;
	dy = y2 - y1;
	d = sqrt(dx*dx + dy*dy);

	return d;
}

int PosCollision(Personnage perso){
	int pos;
	pos=perso.position.x;

	return pos;
}