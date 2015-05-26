#include "../include/Niveau.h"

#define TAILLE_MAX 100

void initializeLvl(Personnage tabPerso[], Bloc tabBlocs[], Bloc tabBlocsFinaux[], int * nb_perso,int * nb_bloc,char* f){

  FILE* fichier = NULL;
  char chaine[TAILLE_MAX] = "";
  int i=0;
  char* str1;
  float px,py,tx,ty,r,g,b;
  int id;

  fichier = fopen(f, "r+");

  if (fichier != NULL) {
    

    fgets(chaine, TAILLE_MAX, fichier);

    str1 = strtok(chaine,"\n");
    *nb_perso = atoi(str1);

      printf("str:%s\n",str1 );
    fgets(chaine, TAILLE_MAX, fichier);
    str1 = strtok(chaine,"\n");
    *nb_bloc = atoi(str1);

    fgets(chaine, TAILLE_MAX, fichier);
    str1 = strtok(chaine, "\n");
    for(i = 0; i<*nb_perso; i++) {
      recupParametres(&px,&py,&tx,&ty,&r,&g,&b,&id,str1);
      tabPerso[i] = Personnage2D(PointXY(px,py),TailleXY(tx,ty),ColorRGB(r, g, b),i,0.0);
      fgets(chaine, sizeof(chaine), fichier);
      str1 = strtok(chaine,"\n");
    }

    str1 = strtok(chaine,"\n");
    for(i = 0; i<*nb_bloc; i++) {
      recupParametres(&px,&py,&tx,&ty,&r,&g,&b,&id,str1);
      tabBlocs[i] = Bloc2D(PointXY(px,py),TailleXY(tx,ty),ColorRGB(r, g, b),id);
      fgets(chaine, sizeof(chaine), fichier);
      str1 = strtok(chaine,"\n");
    }
    
    str1 = strtok(chaine, "\n");
    for(i = 0; i<*nb_perso; i++) {
      recupParametres(&px,&py,&tx,&ty,&r,&g,&b,&id,str1);
      tabBlocsFinaux[i] = Bloc2D(PointXY(px,py),TailleXY(tx,ty),ColorRGB(r, g, b),id);
      fgets(chaine, sizeof(chaine), fichier);
      str1 = strtok(chaine,"\n");
    }
  }
  else
  {
      printf("Impossible d'ouvrir le fichier list.txt");
  }
}

void recupParametres(float* px, float* py, float* tx, float* ty, float* r, float* g, float* b,int* id, char* str1){
    char* str;

    str1 = strtok(str1,",");
    *px = atof(str1); str1 = strtok(NULL, ","); 
    *py = atof(str1); str1 = strtok(NULL, ","); 
    *tx = atof(str1); str1 = strtok(NULL, ","); 
    *ty = atof(str1); str1 = strtok(NULL, ","); 
    *r = atof(str1); str1 = strtok(NULL, ",");
    *g = atof(str1); str1 = strtok(NULL, ",");
    *b = atof(str1); str1 = strtok(NULL, ",");
    *id= atof(str1); 

}