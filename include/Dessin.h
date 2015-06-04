#ifndef DESSIN_H_
#define DESSIN_H_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL_image.h> 

#include "../include/Dessin.h"
#include "../include/include.h"


void dessinCarre(int Filled,float r, float g, float b , float positionX, float positionY,float tailleX, float tailleY );
void dessinOpacity(int Filled, float r, float g, float b , float positionX, float positionY,float tailleX, float tailleY);
void dessinCercle(int nbsubdivision, int Filled);
void dessinSpectre(float spectrum[], float spectrumJump[], int currentPerso, int up,int level);
void loadTexture(const char* filename, GLuint textureID[10], int numTexture);
void DrawCredit(int windowWidth, int windowHeight, GLuint textureID[10]);
 
#endif