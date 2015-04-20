#include "../include/Physics.h"
#include <math.h>

static const double g=9.2;
static const float v_init = 0.5;
static const double pi= M_PI ;
static const double angle_init = M_PI/3;




void Jump(Personnage * perso,int t){

	double v_x = cos(angle_init)*v_init;
	double v_y = sin(angle_init)*v_init;

	perso->position.x=(v_x*t);
	perso->position.y=((v_y*t)-((g*t*t)/2000));

	
}