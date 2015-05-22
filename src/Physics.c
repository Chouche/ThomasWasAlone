#include "../include/Physics.h"
#include <math.h>
#include "../include/Collision.h"

static const double g=9.2;




void Gravity(Personnage * perso,double t,float v_init){

	double v_y = sin(M_PI/2)*v_init;

  perso->position.y=perso->position.y+((v_y*t)-((g*t*t)/2000));

}


void Physics(Personnage * perso, int nb_bloc, Bloc blocs[],double * t,int * up, int currentPerso)
{
	
	 int i=0,colDown=0;

  /* GRAVITE */
  for(i=0; i<nb_bloc; i++ ) {
    if(CollisionBG(*perso,blocs[i]) == 2  || CollisionBD(*perso,blocs[i]) == 2 ){
      
      colDown = 1;
      *t=0.;
    } 
    else colDown= 0;
    if (*up==1)
    {
      colDown=1;
    }
  }

    // Permet de tomber 
  if(colDown == 0 && *up!=1) {

      *t += 1.5;
      Gravity(perso, *t,0);

      for(i=0; i<nb_bloc; i++ ) { 
        
       if(CollisionBG(*perso,blocs[i]) == 2 || CollisionBD(*perso,blocs[i]) == 2)
       {
          perso->position.y = blocs[i].position.y+blocs[i].taille.y;
          *t=0.;
       }  
         
      }
  } 
    
  // Permet de sauter 
  if((colDown == 1) && (*up == 1) && (perso->id == currentPerso)) {

    *t += 2;
    perso->position.y = perso->position.y+5;

    Gravity(perso, *t,0.001);

    for(i=0; i<nb_bloc; i++ ) { 

     if(CollisionBG(*perso,blocs[i]) == 2 || CollisionBD(*perso,blocs[i]) == 2)
     {
        perso->position.y = blocs[i].position.y+blocs[i].taille.y;
        *up=0;
     }  
      
     if(CollisionHG(*perso,blocs[i]) == 2 || CollisionHD(*perso,blocs[i]) == 2)
     {
      perso->position.y = blocs[i].position.y-perso->taille.y;
      *up=0;
      *t=0.;
     }  
    }
  } 
}

int Dead(Personnage * perso)
{
	if(perso->position.y < -2000)
	{
		perso->position.y=2;
		perso->position.x=2;
		return 1;
	}	
	else return 0;
}
