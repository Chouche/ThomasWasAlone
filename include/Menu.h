#ifndef MENU_H_
#define MENU_H_

#include "../include/Dessin.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL_image.h> 
#include <time.h>

void DrawMenu(int menu,GLuint textureID[380],int windowWidth, int windowHeight);
void DrawIntro(int * img, int * intro);
void DrawIntrolvl(int * img);
#endif