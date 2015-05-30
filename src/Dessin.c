#include "Dessin.h"

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

void DrawCredit(int windowWidth, int windowHeight, GLuint textureID[10]) {

    glEnable(GL_TEXTURE_2D);
    // FIXME : Bind texture
    /* Dessin du quad */
    glColor3ub(50,50,50);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
      glColor3f(1,1,1);

      glTexCoord2f(0, 1);
      glVertex2f(-150, -100);

      glTexCoord2f(1, 1);
      glVertex2f(150, -100);

      glTexCoord2f(1, 0);
      glVertex2f(150, 100);

      glTexCoord2f(0, 0);
      glVertex2f(-150, 100);

    glEnd();


  glBindTexture(GL_TEXTURE_2D, 0);

  glDisable(GL_TEXTURE_2D);

}

void loadTexture(const char* filename, GLuint textureID[10], int numTexture){
  
  SDL_Surface* image;
  image = IMG_Load(filename);

  printf("filename: %s",filename);
  if(image == NULL){
    printf("Error : image not found : %s\n", filename);
  }

  glGenTextures(1, textureID);
  glBindTexture(GL_TEXTURE_2D, numTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
  // TODO : Supprimer les texture lors de la fermeture du prog
  //glDeleteTextures(10, &textureID);
  SDL_FreeSurface(image);
}