#include "../include/Music.h"


FMOD_SOUND* OuvrirMusique(char* fichier, FMOD_SOUND *musique, FMOD_SYSTEM *system) {
  
  FMOD_RESULT resultat;
  /* On ouvre la musique */
  resultat = FMOD_System_CreateSound(system, fichier, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
  /* On vérifie si elle a bien été ouverte (IMPORTANT) */
  if (resultat != FMOD_OK)
  {
      fprintf(stderr, "Impossible de lire le fichier mp3\n");
      exit(EXIT_FAILURE);
  }
  return musique;
}

FMOD_CHANNEL* JouerMusique(FMOD_SYSTEM *system, FMOD_CHANNEL *channelArret, FMOD_CHANNEL *channel,FMOD_SOUND *musique) {

	FMOD_Channel_Stop(channelArret);
    /* On active la répétition de la musique à l'infini */
    FMOD_Sound_SetLoopCount(musique, -1);
    /* On joue la musique */
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, &channel);
    FMOD_System_Update(system);

    return channel;
}