#include "../include/include.h"
#include <SDL/SDL_mixer.h>
#include <fmodex/fmod.h>
#include <fmodex/fmod_errors.h>


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

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
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


    FMOD_SYSTEM *system;

    FMOD_SOUND *musique;

    FMOD_RESULT resultat;

    

    FMOD_System_Create(&system);

    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    /* On ouvre la musique */

    resultat = FMOD_System_CreateSound(system, "music/music.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
        /* On vérifie si elle a bien été ouverte (IMPORTANT) */
    if (resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier mp3\n");
        exit(EXIT_FAILURE);
    }


    /* On active la répétition de la musique à l'infini */
    FMOD_Sound_SetLoopCount(musique, -1);

    /* On joue la musique */
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);

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
   
    break;
    case 1: 
      initializeLvl(tabPerso,tabBlocs, tabBlocsFinaux, &nb_perso,&nb_bloc,"niveaux/niveau1.txt");
     break;
    case 2:
      initializeLvl(tabPerso,tabBlocs, tabBlocsFinaux, &nb_perso,&nb_bloc,"niveaux/niveau2.txt");
      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      break;

  }
 
  int loop = 1;
/*
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
   Mix_Music *musique; //Création du pointeur de type Mix_Music
  // musique = Mix_LoadMUS("music/music.mp3"); //Chargement de la musique
   Mix_PlayMusic(musique, -1); //Jouer infiniment la musique
*/
  while(loop) {

    // temps au début de la boucle 
    Uint32 startTime = SDL_GetTicks();

    //Initialisation des variables physics 

    int colLeft = 0, colRight = 0;

   // InitializeCollision(collisionHG, collisionBG, collisionHD, collisionBD, nb_bloc);

    //RechercheCollision(tabPerso[0], tabBlocs, collisionHG, collisionBG, collisionHD, collisionBD, nb_bloc);
    
    glClear(GL_COLOR_BUFFER_BIT);

    //Caméra 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D( tabPerso[currentPerso].position.x - windowWidth / 6.0, tabPerso[currentPerso].position.x + windowWidth /  6.0, tabPerso[currentPerso].position.y - windowHeight / 6.0, tabPerso[currentPerso].position.y + windowHeight / 6.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (level==0)
    {
       DrawMenu();
    }

    //Dessin
    printf("%d\n",nb_perso );
    for(i=0; i < nb_perso; i++)
      if (i==currentPerso)
      {
        DessinPersonnageCarre(tabPerso[i]);
      }
      else
      {
        dessinCarre(1, 126, 126, 126 , tabPerso[i].position.x, tabPerso[i].position.y,tabPerso[i].taille.x, tabPerso[i].taille.y );
      } 
      

    for(i=nb_perso; i < nb_bloc; i++){
      {
        if(tabBlocs[i].id == currentPerso || tabBlocs[i].id == -1)
      DessinBlocCarre(tabBlocs[i], 1);
    }
  }

    for(i=0; i < nb_perso; i++)
      DessinBlocCarre(tabBlocsFinaux[i],0);


    for(i=0; i < nb_perso; i++){
      
      
        tabBlocs[i].position.x=tabPerso[i].position.x;
        tabBlocs[i].position.y=tabPerso[i].position.y;
      
      
    }

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
              if(currentPerso==nb_perso) currentPerso = 0;
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
      for(i=0; i<nb_bloc; i++ ) {
        if(CollisionHG(tabPerso[currentPerso], tabBlocs[i])== 1 && i != currentPerso || CollisionBG(tabPerso[currentPerso], tabBlocs[i]) == 1 && i != currentPerso ) colLeft = 1;
      }
      if(colLeft == 0) MooveLeft(&tabPerso[currentPerso]);
   

      
    }

    if(right == 1){
      for(i=0; i<nb_bloc; i++ ) {
        if(CollisionHD(tabPerso[currentPerso], tabBlocs[i]) == 1 && i != currentPerso || CollisionBD(tabPerso[currentPerso], tabBlocs[i]) == 1 && i != currentPerso) colRight = 1;
      }
      if(colRight == 0) MooveRight(&tabPerso[currentPerso]);
       
       

    }

    for(i=0; i < nb_perso; i++)
   //Gravité 
    Physics(&tabPerso[i], nb_bloc, tabBlocs, &(tabPerso[i].t), &up, currentPerso);

    for(i=0; i < nb_perso; i++) {
       if( ( tabPerso[i].position.x < tabBlocsFinaux[i].position.x+2 && tabPerso[i].position.x > tabBlocsFinaux[i].position.x-2) && ( tabPerso[i].position.y < tabBlocsFinaux[i].position.y+2 && tabPerso[i].position.y > tabBlocsFinaux[i].position.y-2) )
        gagne++;
    }
      
    if(gagne == nb_perso && level!=0) {
        printf("C'est gagné ! \n");
        level++; 
        goto BEGGINNING;
    }
    gagne = 0;
    
   
    if(Dead(&tabPerso[currentPerso]))
    {
      tabPerso[currentPerso].t = 0;
      glMatrixMode(GL_PROJECTION);
      glPopMatrix();

    }   

    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }

  } // Fin de la boucle


  SDL_Quit();

  return EXIT_SUCCESS;

}



