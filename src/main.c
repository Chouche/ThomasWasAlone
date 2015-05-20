#include "../include/include.h"

static const unsigned int BIT_PER_PIXEL = 32;
static const unsigned int MAX_BLOC = 100;
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

  unsigned int windowWidth  = 800;
  unsigned int windowHeight = 600;

  unsigned int nb_bloc = 5;
  int left=0,right=0,up=0, down = 0,direction=0,angle_init, i = 0;
  int collisionHG[nb_bloc], collisionBG[nb_bloc], collisionHD[nb_bloc], collisionBD[nb_bloc];
 

  double t = 0.0;

  Bloc blocs[nb_bloc];

  //Initialisation des personnages//
      Personnage henry = Personnage2D(PointXY(2,2),TailleXY(20,20),ColorRGB(100,100,100));
      

      blocs[0] = Bloc2D(PointXY(-50,10.),TailleXY(50,50),ColorRGB(250,00,00)); 
      blocs[1] = Bloc2D(PointXY(50,0),TailleXY(25,20),ColorRGB(250,00,00));
      blocs[2] = Bloc2D(PointXY(100,-10),TailleXY(5,20),ColorRGB(250,00,00));
      blocs[3] = Bloc2D(PointXY(-100,-10),TailleXY(5,20),ColorRGB(250,00,00));
      blocs[4] = Bloc2D(PointXY(-10,-50),TailleXY(150,10),ColorRGB(250,00,00));

  

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

    int colLeft = 0, colRight = 0, colUp = 0, colDown = 0;

    for(i = 0; i < nb_bloc; i++){
      collisionHG[i] = 0;
      collisionHD[i] = 0;
      collisionBG[i] = 0;
      collisionBD[i] = 0;
    }

    for(i = 0; i < nb_bloc; i++) {
      collisionHG[i] = CollisionHG(henry,blocs[i]);
      collisionHD[i] = CollisionHD(henry,blocs[i]);
      collisionBG[i] = CollisionBG(henry,blocs[i]);
      collisionBD[i] = CollisionBD(henry,blocs[i]);
    }
    
    glClear(GL_COLOR_BUFFER_BIT);
    //Changement de matrice
    glMatrixMode(GL_MODELVIEW);
    //On ecrase la matrice précédente pour lui donner la matrice identité
    glLoadIdentity();
    
     
    //Dessin ici :)
  
    DessinPersonnageCarre(henry);

    for(i=0; i < nb_bloc; i++) 
      DessinBlocCarre(blocs[i]);


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
              direction=1;

              break;

            case SDLK_LEFT: 
              left=1;
              direction=-1;
              break;

            case SDLK_UP:
              up=1;
              break;  

              case SDLK_DOWN:
              down = 1;
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

             
            
              break;


            case SDLK_DOWN:

            down = 0;

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

    //Déplacement
   /* printf("HD: %d\n",collisionHG[0].col );*/
    
    if(left == 1){
      for(i=0; i<nb_bloc; i++ ) 
        if(collisionHG[i] == 1 || collisionBG[i] == 1) colLeft = 1;
      if(colLeft == 0) MooveLeft(&henry);
    }

    if(right == 1){
      for(i=0; i<nb_bloc; i++ ) 
        if(collisionHD[i] == 1 || collisionBD[i] == 1) colRight = 1;
      if(colRight == 0) MooveRight(&henry);
    }

    // /* SAUT */
    // if(up == 1){
    //   for(i=0; i<nb_bloc; i++) 
    //     if(collisionHD[i] == 2 || collisionHG[i] == 2)
    //       {
    //         up=0;
    //         colUp = 1;
    //        } 
    //   if(colUp == 1) {
    //     t+=1;
    //     Gravity(&henry,t,0.15);
    //     for(i=0; i<nb_bloc; i++ ) { 
    //      if(CollisionBG(henry,blocs[i]) == 2)  henry.position.y = blocs[i].position.y+blocs[i].taille.y;
    //      if(CollisionBD(henry,blocs[i]) == 2)  henry.position.y = blocs[i].position.y+blocs[i].taille.y;
           
    //     }
    //   }
    // }
    
    /* GRAVITE */
    for(i=0; i<nb_bloc; i++ ) {
      if(collisionBD[i] == 2 || collisionBG[i] == 2){
        colDown = 1;
        t=0.;
      } 
    }
    if(colDown == 0) {
        t += 1;
        Gravity(&henry, t,0);
        for(i=0; i<nb_bloc; i++ ) { 
         if(CollisionBG(henry,blocs[i]) == 2)
         {
            henry.position.y = blocs[i].position.y+blocs[i].taille.y;
           
         }  
         if(CollisionBD(henry,blocs[i]) == 2){
            henry.position.y = blocs[i].position.y+blocs[i].taille.y;
           
         }  
           
        }
    } 
    if( colDown = 1 && up == 1) {
        t += 1;
         henry.position.y = henry.position.y+5;
        Gravity(&henry, t,0.05);
        for(i=0; i<nb_bloc; i++ ) { 
         if(CollisionBG(henry,blocs[i]) == 2)
         {
            henry.position.y = blocs[i].position.y+blocs[i].taille.y;
            up=0;
           
         }  
         if(CollisionBD(henry,blocs[i]) == 2)
         {
          henry.position.y = blocs[i].position.y+blocs[i].taille.y;
          up=0;
          
         }  
           
        }
    }
   




    /*if(down == 1){
      for(i=0; i<nb_bloc; i++ ) 
        if(collisionBD[i] == 2 || collisionBG[i] == 2) colDown = 1;
      if(colDown == 0) MooveDown(&henry);
    }*/

    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  SDL_Quit();

  return EXIT_SUCCESS;
}




//if(up==1){

    //   if(left==1||right==1){
        
    //      angle_init=M_PI/3;
    //   }
    //   else{
    //       direction=0;
    //       angle_init=M_PI/2; //permet de sauter droit 
         
    //   } 
      

    //  // Jump(&henry,t,direction,angle_init);
    //   t+=3;
      
    // }

    // if(collisionBD==0 && collisionBG==0){ // Il n'y a PAS de collision


    //   if(up==0) Fall(&henry,t);
      
    //   if(up==0) t+=3;

    // }else // Il y a une collision
    // {
      
    // //henry.position.y+=PosCollision(henry,bloc2);
    //   t=0;
    //   up=0;
     
    // }