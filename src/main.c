#include "../include/include.h"
#include <SDL/SDL_mixer.h>
#include <fmodex/fmod.h>
#include <fmodex/fmod_errors.h>
#include <math.h>

#define SPECTRUMSIZE        8192
#define SPECTRUMRANGE       ((float)OUTPUTRATE / 2.0f) 
#define BINSIZE      (SPECTRUMRANGE / (float)SPECTRUMSIZE)


static const unsigned int BIT_PER_PIXEL = 32;
static const unsigned int MAX_BLOC = 100;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape(int winWidth, int winHeight) {
  glViewport(0, 0, winWidth, winHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-100., 100., -100*(winHeight/(float)winWidth), 100*(winHeight/(float)winWidth));
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void setVideoMode(int winWidth, int winHeight) {
  if(NULL == SDL_SetVideoMode(winWidth, winHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }

  reshape(winWidth,winHeight);
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
  float t = 0.0;
  Bloc tabBlocs[100];
  Bloc tabBlocsFinaux[4];
  Personnage tabPerso[4];
  int currentPerso = 0;
  int level = 0;
  int gagne = 0;
  float zoom = 8;


  FMOD_SYSTEM *system;
  FMOD_SOUND *musique;
  FMOD_RESULT resultat;
  FMOD_CHANNEL *channel = 0;
  FMOD_CHANNEL *channelJump = 0;
  FMOD_SOUND *jump;

    

  FMOD_System_Create(&system);

  FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL);

  /* On ouvre la musique */

  resultat = FMOD_System_CreateSound(system, "music/music.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
      /* On vérifie si elle a bien été ouverte (IMPORTANT) */
  if (resultat != FMOD_OK)
  {
      fprintf(stderr, "Impossible de lire le fichier mp3\n");
      exit(EXIT_FAILURE);
  }

  resultat = FMOD_System_CreateSound(system, "music/jump.wav", FMOD_CREATESAMPLE, 0, &jump);
  if (resultat != FMOD_OK) {
   fprintf(stderr, "Impossible de lire pan.wav\n");
   exit(EXIT_FAILURE);
  }


  /* On active la répétition de la musique à l'infini */
  FMOD_Sound_SetLoopCount(musique, -1);

  /* On joue la musique */
  FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, &channel);
  FMOD_System_Update(system);

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
      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      break;

  }
 
  int loop = 1;

  while(loop) {

    float spectrum[SPECTRUMSIZE];
    float spectrumJump[SPECTRUMSIZE];

    // temps au début de la boucle 
    Uint32 startTime = SDL_GetTicks();

    int colLeft = 0, colRight = 0;

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(255.0, 231.0, 222.0, 255.0);

    //Caméra 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D( tabPerso[currentPerso].position.x - windowWidth / zoom, tabPerso[currentPerso].position.x + windowWidth /  zoom, tabPerso[currentPerso].position.y - windowHeight / zoom, tabPerso[currentPerso].position.y + windowHeight / zoom);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    resultat = FMOD_Channel_GetSpectrum(channel, spectrum, SPECTRUMSIZE, 0, FMOD_DSP_FFT_WINDOW_TRIANGLE); 
    if (resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de récupérer le spectre\n");
        exit(EXIT_FAILURE);
    }
    if(up == 1) {
      resultat = FMOD_Channel_GetSpectrum(channelJump, spectrumJump, SPECTRUMSIZE, 0, FMOD_DSP_FFT_WINDOW_TRIANGLE); 
      if (resultat != FMOD_OK)
      {
          fprintf(stderr, "Impossible de récupérer le spectre\n");
          exit(EXIT_FAILURE);
      }
    }
    //Dessin
 
    dessinSpectre(spectrum,spectrumJump,currentPerso);

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
      if(tabBlocs[i].id == currentPerso || tabBlocs[i].id == -1)
        DessinBlocCarre(tabBlocs[i], 1); 
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
            
            case SDLK_d:
            case SDLK_RIGHT:
              right=1;

              break;

            case SDLK_q:
            case SDLK_LEFT: 
              left=1;
            
              break;

            case SDLK_z:
            case SDLK_SPACE:
            case SDLK_UP:
             for(i=0; i<nb_bloc; i++ ) {
               if(CollisionBD(tabPerso[currentPerso],tabBlocs[i])==2 || CollisionBG(tabPerso[currentPerso],tabBlocs[i])==2){
                   up=1;
                }
              } 
              FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, jump, 0, &channelJump);
              FMOD_System_Update(system);
              break;  

              case SDLK_DOWN:
              
              break;  
            
            case SDLK_a:
              if(currentPerso == 0) currentPerso = nb_perso;
              if(currentPerso > 0) currentPerso--;
              up=0;
            break; 

            case SDLK_e:
            case SDLK_TAB :
              if(currentPerso < nb_perso) currentPerso++;
              if(currentPerso==nb_perso) currentPerso = 0;
              up=0;
            break;

            case SDLK_w:
              if(zoom == 8) zoom = 5;
              else zoom = 8;
            break;

            case SDLK_ESCAPE :
              loop = 0;
              break;

            default : break;

           }
          break;

        case SDL_KEYUP:
          switch(e.key.keysym.sym){
            
            case SDLK_d:
            case SDLK_RIGHT:
              right=0;
              break;

            case SDLK_q:
            case SDLK_LEFT:     
              left=0;

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

    //Gravité
    for(i=0; i < nb_perso; i++)
      Physics(&tabPerso[i], nb_bloc, tabBlocs, &(tabPerso[i].t), &up, currentPerso);

    for(i=0; i < nb_perso; i++) {
       if( ( tabPerso[i].position.x < tabBlocsFinaux[i].position.x+2 && tabPerso[i].position.x > tabBlocsFinaux[i].position.x-2) && ( tabPerso[i].position.y < tabBlocsFinaux[i].position.y+2 && tabPerso[i].position.y > tabBlocsFinaux[i].position.y-2) )
        gagne++;
    }
      
    if(gagne == nb_perso) {
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

  FMOD_Sound_Release(musique);
  FMOD_Sound_Release(jump);
  FMOD_System_Close(system);
  FMOD_System_Release(system);
  SDL_Quit();

  return EXIT_SUCCESS;

}



