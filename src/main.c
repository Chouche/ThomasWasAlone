#include "../include/include.h"

static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape(int winWidth, int winHeight) {
  glViewport(0, 0, winWidth, winHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-100., 100., -100*(winHeight/(float)winWidth), 100*(winHeight/(float)winWidth));
}


void setVideoMode(int winWidth, int winHeight) {
  if(NULL == SDL_SetVideoMode(winWidth, winHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }

  reshape(winWidth,winHeight);
  //glClear(GL_COLOR_BUFFER_BIT);
  //SDL_GL_SwapBuffers();
}



int main(int argc, char** argv) {

  unsigned int windowWidth  = 1600/1.5;
  unsigned int windowHeight = 1200/1.5;

  int left=0,right=0,up=0,t=0;

  //Initialisation des personnages//
      Personnage henry = Personnage2D(PointXY(0.5,0.5),TailleXY(2,2),ColorRGB(100,100,100));
      Bloc bloc1 =Bloc2D(PointXY(-10,10),TailleXY(20,5),ColorRGB(250,00,00)); 
      Bloc bloc2 =Bloc2D(PointXY(-10,-10),TailleXY(20,5),ColorRGB(250,00,00));
      Bloc bloc3 =Bloc2D(PointXY(10,-10),TailleXY(5,20),ColorRGB(250,00,00));
      Bloc bloc4 =Bloc2D(PointXY(-10,-10),TailleXY(5,20),ColorRGB(250,00,00));

  

  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  setVideoMode(windowWidth, windowHeight);

  SDL_WM_SetCaption("Clickodrome", NULL);

  glPointSize(4);

  int loop = 1;
  while(loop) {

    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    //Initialisation des variables physics
    
    int collisionHG = CollisionHG(henry,bloc1)+CollisionHG(henry,bloc2)+CollisionHG(henry,bloc3)+CollisionHG(henry,bloc4);
    int collisionHD = CollisionHD(henry,bloc1)+CollisionHD(henry,bloc2)+CollisionHD(henry,bloc3)+CollisionHD(henry,bloc4);

    glClear(GL_COLOR_BUFFER_BIT);
    //Changement de matrice
    glMatrixMode(GL_MODELVIEW);
    //On ecrase la matrice précédente pour lui donner la matrice identité
    glLoadIdentity();
    
     
    //Dessin ici :)
  
       DessinPersonnageCarre(henry);
       DessinBlocCarre(bloc1);
       DessinBlocCarre(bloc2);
       DessinBlocCarre(bloc3);
       DessinBlocCarre(bloc4);


    SDL_GL_SwapBuffers();
    /* ****** */

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }
      switch(e.type) {

        case SDL_VIDEORESIZE:
          windowWidth  = e.resize.w;
          windowHeight = e.resize.h;
          setVideoMode(windowWidth,windowHeight);
          break;

        case SDL_KEYDOWN:
          switch(e.key.keysym.sym){
            
            case SDLK_RIGHT:
              right=1;

              break;

            case SDLK_LEFT: 
              left=1;
 
              break;

            case SDLK_UP:
              up=1;
              break;  
              

            case SDLK_ESCAPE :
              loop = 0;
              break;
            default : break;
          }
          break;

        case SDL_KEYUP:
          switch(e.key.keysym.sym){
            
            case SDLK_RIGHT:
              right=0;

              break;

            case SDLK_LEFT:
            
              left=0;
              
              break;

            case SDLK_UP:
            
              left=1;
              
              break;

            case SDLK_ESCAPE :
              loop = 0;
              break;
            default : break;
          }
          break;

        default:
          break;
      }
    }

    //Déplacement;
    if(left==1 && collisionHG!=1){
      MooveLeft(&henry);
    }

    if(right==1 && collisionHD!=1){
      MooveRight(&henry);
    }

    if(up==1){

      Jump(&henry,t);
      t+=10;
    }


    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  SDL_Quit();

  return EXIT_SUCCESS;
}
