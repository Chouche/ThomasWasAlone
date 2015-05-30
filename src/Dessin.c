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

void dessinSpectre(float spectrum[], float spectrumJump[], int currentPerso) {

  int i;
  int count = -1;
  int count2 = 0;

  for (i=0; i < 300; i++)
  {
          if(currentPerso == 0) glColor4f(105.0, 0.0, 53.0,0.7);
          if(currentPerso == 1) glColor4f(255.0, 0.0, 0.0,0.7);
          glBegin(GL_LINES);
          glVertex3f(count, 0.0, 0.0);
          glVertex3f(count, spectrum[i]*pow(13,3) + spectrumJump[i]*pow(13,3), 0);
          glEnd();

          glBegin(GL_LINES);
          glVertex3f(count2, 0.0, 0.0);
          glVertex3f(count2, spectrum[i]*pow(13,3) + spectrumJump[i]*pow(13,3), 0);
          glEnd();

          glBegin(GL_LINES);
          glVertex3f(count,0.0, 0.0);
          glVertex3f(count,-spectrum[i]*pow(13,3) - spectrumJump[i]*pow(13,3), 0);
          glEnd();

          glBegin(GL_LINES);
          glVertex3f(count2,0.0, 0.0);
          glVertex3f(count2,-spectrum[i]*pow(13,3) - spectrumJump[i]*pow(13,3), 0);
          glEnd();

          count ++; 
          count2 --;     
  } 
}