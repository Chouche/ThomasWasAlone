#include "../include/include.h"
#include <SDL/SDL_mixer.h>

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

  int nb_bloc = 0;
  int nb_perso = 0;
  int left=0,right=0,up=0, i = 0;
  //int collisionHG[nb_bloc], collisionBG[nb_bloc], collisionHD[nb_bloc], collisionBD[nb_bloc];
  float t = 0.0;
  Bloc tabBlocs[100];
  Bloc tabBlocsFinaux[4];
  Personnage tabPerso[4];
  int currentPerso = 0;
  int level = 0;
  int gagne = 0;



  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  setVideoMode(windowWidth, windowHeight);

  SDL_WM_SetCaption("tabPerso[0] Was Alone", NULL);
 
  glPointSize(4);

 BEGGINNING:

  switch(level) {

    case 0: 
      initializeLvl(tabPerso,tabBlocs, tabBlocsFinaux, &nb_perso,&nb_bloc,"niveaux/niveau1.txt");
     break;
    case 1:
      initializeLvl(tabPerso,tabBlocs, tabBlocsFinaux, &nb_perso,&nb_bloc,"niveaux/niveau2.txt");
      break;

  }
 
  int loop = 1;

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
   Mix_Music *musique; //Création du pointeur de type Mix_Music
   musique = Mix_LoadMUS("music/music.mp3"); //Chargement de la musique
   Mix_PlayMusic(musique, -1); //Jouer infiniment la musique

  while(loop) {

    // temps au début de la boucle 
    Uint32 startTime = SDL_GetTicks();

    //Initialisation des variables physics 

    int colLeft = 0, colRight = 0;

   // InitializeCollision(collisionHG, collisionBG, collisionHD, collisionBD, nb_bloc);

    //RechercheCollision(tabPerso[0], tabBlocs, collisionHG, collisionBG, collisionHD, collisionBD, nb_bloc);
    
    glClear(GL_COLOR_BUFFER_BIT);
    //Changement de matrice
    glMatrixMode(GL_MODELVIEW);
    //On ecrase la matrice précédente pour lui donner la matrice identité
    glLoadIdentity();
    
    //Dessin
  
    for(i=0; i < nb_perso; i++)
     DessinPersonnageCarre(tabPerso[i]);

    for(i=0; i < nb_bloc; i++) 
      DessinBlocCarre(tabBlocs[i], 1);

    for(i=0; i < nb_perso; i++)
      DessinBlocCarre(tabBlocsFinaux[i],0);

    SDL_GL_SwapBuffers();

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
             for(i=0; i<nb_bloc; i++ ) {
               if(CollisionBD(tabPerso[currentPerso],tabBlocs[i])==2 || CollisionBG(tabPerso[currentPerso],tabBlocs[i])==2){
                   up=1;
                }
              } 
              break;  

              case SDLK_DOWN:
              
              break;  
              
            case SDLK_SPACE :
              if(currentPerso < nb_perso) currentPerso++;
              if(currentPerso == nb_perso) currentPerso = 0;
              up=0;
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

    //Déplacement du personnage
    
    if(left == 1){
      for(i=0; i<nb_bloc; i++ ) 
        if(CollisionHG(tabPerso[currentPerso], tabBlocs[i])== 1 || CollisionBG(tabPerso[currentPerso], tabBlocs[i]) == 1) colLeft = 1;
      if(colLeft == 0) MooveLeft(&tabPerso[currentPerso]);
    }

    if(right == 1){
      for(i=0; i<nb_bloc; i++ ) 
        if(CollisionHD(tabPerso[currentPerso], tabBlocs[i]) == 1 || CollisionBD(tabPerso[currentPerso], tabBlocs[i]) == 1) colRight = 1;
      if(colRight == 0) MooveRight(&tabPerso[currentPerso]);
    }

    for(i=0; i < nb_perso; i++)
   //Gravité 
    Physics(&tabPerso[i], nb_bloc, tabBlocs, &(tabPerso[i].t), &up, currentPerso);

    for(i=0; i < nb_perso; i++) {
      if(tabPerso[i].position.x == tabBlocsFinaux[i].position.x && tabPerso[i].position.y == tabBlocsFinaux[i].position.y) 
        gagne++;
    }
      
    if(gagne == nb_perso) {
        printf("C'est gagné ! \n");
        level++; 
        goto BEGGINNING;
    }
    gagne = 0;
    
   
    if(Dead(&tabPerso[currentPerso])) tabPerso[currentPerso].t = 0; 

    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }

  } // Fin de la boucle

   Mix_FreeMusic(musique); //Libération de la musique
   Mix_CloseAudio(); //Fermeture de l'API

  SDL_Quit();

  return EXIT_SUCCESS;

}



