#include "../../include/Niveaux/Niveau1.h"


void initializeLvl1(Personnage tabPerso[], Bloc tabBlocs[],int * nb_perso,int * nb_bloc){
	 
 /* Initialisation des personnages */
  *nb_bloc=6;
  *nb_perso=1;


  tabPerso[0] = Personnage2D(PointXY(2,2),TailleXY(15,15),ColorRGB(255, 0, 127));


  /* Initialisation des tabBlocs du niveau */
  tabBlocs[0] = Bloc2D(PointXY(-50,10.),TailleXY(35,20),ColorRGB(121,190,219)); 
  tabBlocs[1] = Bloc2D(PointXY(50,0),TailleXY(30,30),ColorRGB(121,190,219));
  tabBlocs[2] = Bloc2D(PointXY(50,50),TailleXY(20,20),ColorRGB(121,190,219));
  tabBlocs[3] = Bloc2D(PointXY(-100,-10),TailleXY(20,20),ColorRGB(121,190,219));
  tabBlocs[4] = Bloc2D(PointXY(-10,-50),TailleXY(150,20),ColorRGB(121,190,219));
  tabBlocs[5] = Bloc2D(PointXY(20,-10),TailleXY(20,20),ColorRGB(121,190,219));

}