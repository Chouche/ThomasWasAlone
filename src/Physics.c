#include "../include/Physics.h"
#include <math.h>

static const double g=9.2;
static const float v_init = 0.15;



void Jump(Personnage * perso,int t,int direction, int angle_init){

	double v_x = cos(angle_init)*direction*v_init;
	double v_y = sin(angle_init)*v_init;

	perso->position.x=perso->position.x+(v_x*t);
	perso->position.y=perso->position.y+((v_y*t)-((g*t*t)/2000));

	
}

void Fall(Personnage * perso,int t){
	perso->position.y=perso->position.y-((g*t*t)/2000);
}