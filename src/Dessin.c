#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../include/Dessin.h"
#include "../include/include.h"

void dessinCarre(int Filled, float r, float g, float b , float positionX, float positionY,float tailleX, float tailleY ){
  glColor3ub(r, g, b);
  if(Filled==1) glBegin(GL_QUADS);
  else glBegin(GL_LINE_LOOP);
    glVertex2f(positionX, positionY);
    glVertex2f(positionX+tailleX, positionY);
    glVertex2f(positionX+tailleX, positionY+tailleY);
    glVertex2f(positionX, positionY+tailleY);
  glEnd();
}

void dessinCercle(int nbsubdivision, int Filled){
  int i;
  if(Filled==1) glBegin(GL_TRIANGLE_FAN);
  else glBegin(GL_LINE_LOOP);
    for(i=0; i<nbsubdivision; i++){
      glVertex2f(cos(2*M_PI*i/nbsubdivision), sin(2*M_PI*i/nbsubdivision));
    }
  glEnd();
}