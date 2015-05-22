#include "../../include/Niveaux/Niveau2.h"


void initializeLvl2(Personnage tabPerso[], Bloc tabBlocs[], Bloc tabBlocsFinaux[], int * nb_perso,int * nb_bloc){
	 
 /* Initialisation des personnages */
  *nb_bloc=6;
  *nb_perso=2;


  tabPerso[0] = Personnage2D(PointXY(2,2),TailleXY(15,15),ColorRGB(255, 0, 127),0);
  tabPerso[1] = Personnage2D(PointXY(60,2),TailleXY(15,30),ColorRGB(255, 102, 0),1);


  /* Initialisation des tabBlocs du niveau */
  tabBlocs[0] = Bloc2D(PointXY(-100,20.),TailleXY(35,20),ColorRGB(121,190,219)); 
  tabBlocs[1] = Bloc2D(PointXY(10,40),TailleXY(30,30),ColorRGB(121,190,219));
  tabBlocs[2] = Bloc2D(PointXY(60,50),TailleXY(20,20),ColorRGB(121,190,219));
  tabBlocs[3] = Bloc2D(PointXY(-40,-10),TailleXY(20,20),ColorRGB(121,190,219));
  tabBlocs[4] = Bloc2D(PointXY(-10,-50),TailleXY(150,20),ColorRGB(121,190,219));
  tabBlocs[5] = Bloc2D(PointXY(30,-10),TailleXY(20,20),ColorRGB(121,190,219));

  tabBlocsFinaux[0] = Bloc2D(PointXY(-95,40),TailleXY(15,15),ColorRGB(255, 0, 127));


}