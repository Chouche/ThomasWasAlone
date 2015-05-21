#include "../include/Physics.h"
#include <math.h>

static const double g=9.2;




void Gravity(Personnage * perso,int t,float v_init){

	//double v_x = cos(angle_init)*direction*v_init;
	double v_y = sin(M_PI/2)*v_init;

	//perso->position.x=perso->position.x+(v_x*t);
	perso->position.y=perso->position.y+((v_y*t)-((g*t*t)/2000));

	
}

void Fall(Personnage * perso,int t){
	perso->position.y=perso->position.y-((g*t*t)/2000);
}

int Dead(Personnage * perso)
{
	if(perso->position.y < -2000)
	{
		perso->position.y=2;
		perso->position.x=2;
		return 1;
	}	
}