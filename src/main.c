#include "../include/include.h"
#include <math.h>

#define SPECTRUMSIZE        8192
#define ZOOM 4
#define DEZOOM 2


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

int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}


int main(int argc, char** argv) {

  unsigned int windowWidth  = 800;
  unsigned int windowHeight = 600;

  int nb_bloc = 0,nb_pluie=300;
  int nb_perso = 0;
  int left=0,right=0,up=0, i = 0;
  Bloc tabBlocs[100];
  Bloc tabBlocsFinaux[4];
  Bloc tabPluie[nb_pluie];
  Personnage tabPerso[4];
  int currentPerso = 0;
  int level = 0,menu=0;
  int intro = 1;
  int gagne = 0;
  float zoom = ZOOM;
  float xt=0,yt=0;
  int credit = 0, loadintro=4;
  GLuint textureID[360];
  char str[50];
  char str1[50];
  struct timespec tim, tim2;
  tim.tv_sec  = 0;
  tim.tv_nsec = 30000000L;
  int load1 = 371,load2 = 621,load3=871;
  //int load1 = 621,load2 = 871, load3=1121;

  FMOD_SYSTEM *system;
  FMOD_SOUND *musique = NULL;
  FMOD_SOUND *starwars = NULL;
  FMOD_SOUND *feelgood = NULL;
  FMOD_SOUND *totoro = NULL;
  FMOD_SOUND *jump = NULL;
  FMOD_SOUND *playstation = NULL;
  FMOD_SOUND *mission = NULL;

  FMOD_CHANNEL *channel = 0;
  FMOD_CHANNEL *channelJump = 0;
  FMOD_CHANNEL *channeMenu = 0;
  FMOD_CHANNEL *channelIntro = 0;
  FMOD_RESULT resultat;


    //init pluie
  for(i=0;i<nb_pluie;i++){
  tabPluie[i]=Bloc2D(PointXY(rand_a_b(-200,600) ,rand_a_b(300,700)),TailleXY(0.5,rand_a_b(5,20)),ColorRGB(200, 200, 200),50);
  }

    
  // Initialisation de FMOD et ouverture des musiques
  FMOD_System_Create(&system);

  FMOD_System_Init(system, 5, FMOD_INIT_NORMAL, NULL);

  starwars = OuvrirMusique("music/starwarss.wav",starwars,system);
  musique = OuvrirMusique("music/music.mp3",musique,system);
  totoro = OuvrirMusique("music/totoro.mp3",totoro,system);
  feelgood = OuvrirMusique("music/feelgood.mp3",feelgood,system);
  jump = OuvrirMusique("music/jump.wav",jump,system);
  playstation = OuvrirMusique("music/play.mp3",playstation,system);
  mission = OuvrirMusique("music/mission.mp3",mission,system);

  /// Initialisation de la SDL 
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }
  setVideoMode(windowWidth, windowHeight);

  SDL_WM_SetCaption("tabPerso[0] Was Alone", NULL);
 
  glPointSize(4);

 // Début du niveau ou menu
 BEGGINNING:
  
  //Initialisation des niveaux
  switch(level) {
    case 0:
      zoom = 6;
      tabPerso[currentPerso].position.x = 0;
      tabPerso[currentPerso].position.y = 0;
     break;
    case 1: 
      initializeLvl(tabPerso,tabBlocs, tabBlocsFinaux, &nb_perso,&nb_bloc,"niveaux/niveau1.txt");
     break;
    case 2:
      initializeLvl(tabPerso,tabBlocs, tabBlocsFinaux, &nb_perso,&nb_bloc,"niveaux/niveau2.txt");
      break;
    case 3:
      initializeLvl(tabPerso,tabBlocs, tabBlocsFinaux, &nb_perso,&nb_bloc,"niveaux/niveau3.txt");
      break;
    case 99:
      initializeLvl(tabPerso,tabBlocs, tabBlocsFinaux, &nb_perso,&nb_bloc,"niveaux/credit.txt");
      break;   
  }
  
  currentPerso = 0;
  int loop = 1;
  if(level != 0) zoom = ZOOM;

  // Initialisation des textures
  loadTexture("./images/totoro.jpg", textureID, 1);
  loadTexture("./images/henry.jpg", textureID, 2);
  loadTexture("./images/was1.jpg", textureID, 3);
  //texture intro  
  if(intro == 1) {
    channelIntro = JouerMusique(system,channel,channelIntro,playstation); 
  }
    // Play music
  if(level == 0 && intro != 1){
    FMOD_Channel_Stop(channelIntro);
    channeMenu = JouerMusique(system,channel,channeMenu,starwars);
  }

  if(level == 1 ) 
    channel = JouerMusique(system,channeMenu,channel,feelgood);

  if(level == 2 ) {
    FMOD_Channel_Stop(channeMenu);
    channel = JouerMusique(system,channel,channel,musique);
  }
  if(level == 3 ) {
    FMOD_Channel_Stop(channeMenu);
    channel = JouerMusique(system,channel,channel,mission);
  }
  
  if (level==99)
    channel = JouerMusique(system,channeMenu,channel,totoro);

  // Boucle
  while(loop) {
    // Pour changer la musique
    if(intro == 5) {
      intro = 2;
      goto BEGGINNING;
    }
    
    float spectrum[SPECTRUMSIZE];
    float spectrumJump[SPECTRUMSIZE];

    // temps au début de la boucle 
    Uint32 startTime = SDL_GetTicks();

    int colLeft = 0, colRight = 0;

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);

    //Caméra 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Level 99 = credit
    if((level==99)||(load1<621&&level==1)||(load2<871&&level==2)||(load3<1121&&level==3)){
      gluOrtho2D(-150., 150., -130*(windowHeight/(float)windowWidth), 130*(windowHeight/(float)windowWidth));
    }   
    else if(level == 0)
    {  
      gluOrtho2D( tabPerso[currentPerso].position.x - windowWidth / zoom, tabPerso[currentPerso].position.x + windowWidth /  zoom, (tabPerso[currentPerso].position.y - windowHeight / zoom), (tabPerso[currentPerso].position.y + windowHeight / zoom));
    }
    else gluOrtho2D( tabPerso[currentPerso].position.x - windowWidth / zoom, tabPerso[currentPerso].position.x + windowWidth /  zoom, (tabPerso[currentPerso].position.y - windowHeight / zoom) + 60, (tabPerso[currentPerso].position.y + windowHeight / zoom) + 60);
   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Récupération du spectre
    if(level == 1||level == 2||level == 3) {
      resultat = FMOD_Channel_GetSpectrum(channel, spectrum, SPECTRUMSIZE, 0, FMOD_DSP_FFT_WINDOW_TRIANGLE); 
      if (resultat != FMOD_OK)
      {
          fprintf(stderr, "Impossible de récupérer le spectre\n");
          exit(EXIT_FAILURE);
      }
    }
    if(up == 1 && level !=99) {
      resultat = FMOD_Channel_GetSpectrum(channelJump, spectrumJump, SPECTRUMSIZE, 0, FMOD_DSP_FFT_WINDOW_TRIANGLE); 
      if (resultat != FMOD_OK)
      {
          fprintf(stderr, "Impossible de récupérer le spectre\n");
          exit(EXIT_FAILURE);
      }
    }
    //Dessin
   if(level == 0 || level == 99){
      if(credit == 1) {
        
      //Page crédit
      DrawCredit(windowWidth, windowHeight, textureID);
      DessinPersoPluie(nb_perso,nb_pluie,currentPerso,tabPerso,tabPluie);
      MooveYeuxTotoro(right,left,&yt,&xt,tabPerso);
      DessinYeuxTotoro(yt, xt);

        
      }
      else{ 
        if(intro != 1 )
        DrawMenu(menu,textureID,windowWidth, windowHeight);
        else{

          strcpy(str, "./images/intro/intro (");
          sprintf(str1, "%d", loadintro-3);
          strcat(str, str1);
          strcat(str,").jpg");
  
          loadTexture(str, textureID, loadintro);
          nanosleep(&tim,&tim2);
          DrawIntro(&loadintro, &intro);
        } 
      }
    }
    else
    { 

      if(level == 1 && load1 != 621) {

        strcpy(str, "./images/lvl1/level1 (");
        sprintf(str1, "%d", load1-370);
        strcat(str, str1);
        strcat(str,").jpg");
        loadTexture(str, textureID, load1);
        DrawIntrolvl(&load1);
      }
      if(level == 2 && load2 != 871){
        strcpy(str, "./images/lvl2/level2 (");
        sprintf(str1, "%d", load2-620);
        strcat(str, str1);
        strcat(str,").jpg");
        loadTexture(str, textureID, load2);
        DrawIntrolvl(&load2);
      }
      if(level == 3 && load3 != 1121){
        strcpy(str, "./images/lvl3/level3 (");
        sprintf(str1, "%d", load3-870);
        strcat(str, str1);
        strcat(str,").jpg");
        loadTexture(str, textureID, load3);
        DrawIntrolvl(&load3);
      }
      if((level== 1 && load1==621)||(level == 2 && load2==871)||(level == 3 && load3==1121)){
  
        dessinSpectre(spectrum,spectrumJump,currentPerso,up, level);

        for(i=0; i < nb_perso; i++) {
          glLineWidth(2);
          DessinBlocCarre(tabBlocsFinaux[i],0);
          glLineWidth(1);
        }

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
      }
      //Bloc du perso suis le perso
      for(i=0; i < nb_perso; i++){
          tabBlocs[i].position.x=tabPerso[i].position.x;
          tabBlocs[i].position.y=tabPerso[i].position.y;
      }
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
              if(level==0){
                menu++;
                if(menu == 3){
                  menu=0;
                }
                if(menu==14)
                {
                  menu=11;
                }
              }
              else
                {  
                  right=1;
                }
                if(level==99)right=1;
              break;

            case SDLK_q:
            case SDLK_LEFT: 
             if(level==0){ 
              menu--;
              if(menu==-1){
                menu=2;
              }
              if(menu==10){
                menu=13;
              }
            }
            else
            {
              left=1;
            }
            if(level==99)
              left=1;
              
              break;

            case SDLK_z:
            case SDLK_SPACE:
            case SDLK_UP:
             if(level!=0){
             for(i=0; i<nb_bloc; i++ ) {
               if(CollisionBD(tabPerso[currentPerso],tabBlocs[i])==2 || CollisionBG(tabPerso[currentPerso],tabBlocs[i])==2){
                   if(level != 99)
                   {
                   FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, jump, 0, &channelJump);

                   }
                   FMOD_System_Update(system);
                   up=1;
                }
              } 
           
            }
              break;  

              case SDLK_DOWN:
              
              break;  
            
            case SDLK_a:
              if(level!=0){
              if(currentPerso == 0) currentPerso = nb_perso;
              if(currentPerso > 0) currentPerso--;
              up=0;
              }
            break; 

            case SDLK_e:
            case SDLK_TAB :
              if(level!=0){
              if(currentPerso < nb_perso) currentPerso++;
              if(currentPerso==nb_perso) currentPerso = 0;
              up=0;
              }
            break;

            case SDLK_w:
              if(level != 0) {
                if(zoom == ZOOM) zoom = DEZOOM;
                else zoom = ZOOM;
              }
            break;

            //Touche M//  
            case SDLK_m:
              if(intro!=1){
              level = 0;
              menu = 0;
              credit=0;
              currentPerso=0;
              load1=371;
              load2=621;
              load3=871;
              goto BEGGINNING;
              }
              break; 

            case SDLK_RETURN:
              if(intro!=1&&level==0){
              if(level !=99) credit = 0;
              if(level==0){
                if(menu == 0){
                  level=1;
                  goto BEGGINNING;
                }
                if(menu == 2) {
                  credit = 1;
                  level=99;
                  goto BEGGINNING;
                }
              }
                if(menu==11){
                  level=1;
                  goto BEGGINNING;
                }
                if(menu==1){
                  menu=11;
                }
                
                if(menu==12){
                  level=2;
                  goto BEGGINNING;
                }
                if(menu==13){
                  level=3;
                  goto BEGGINNING;
                }
              }
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
    if(level!=0){
    if(left == 1){
      for(i=0; i<nb_bloc; i++ ) {
        if( (CollisionHG(tabPerso[currentPerso], tabBlocs[i])== 1 && i != currentPerso) || (CollisionBG(tabPerso[currentPerso], tabBlocs[i]) == 1 && i != currentPerso) ) colLeft = 1;
      }
      if(colLeft == 0) MooveLeft(&tabPerso[currentPerso]);
   

      
    }

    if(right == 1){
      for(i=0; i<nb_bloc; i++ ) {
        if( (CollisionHD(tabPerso[currentPerso], tabBlocs[i]) == 1 && i != currentPerso) || (CollisionBD(tabPerso[currentPerso], tabBlocs[i]) == 1 && i != currentPerso) ) colRight = 1;
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
        if(level == 3){
             level = 0;
              menu = 0;
              credit=0;
              currentPerso=0;
              load1=371;
              load2=621;
              goto BEGGINNING;
        }
        
        level++; 
        goto BEGGINNING;
    }
    gagne = 0;
    
     for (i = 0; i < nb_perso; i++)
     {
        if(Dead(&tabPerso[i]))
        {
          tabPerso[i].t = 0;
          glMatrixMode(GL_PROJECTION);
          glPopMatrix();

        }   
      }
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



