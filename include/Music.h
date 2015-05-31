#ifndef MUSIC_H_
#define MUSIC_H_

#include <stdlib.h>
#include <stdio.h>
#include <fmodex/fmod.h>
#include <fmodex/fmod_errors.h>

FMOD_SOUND* OuvrirMusique(char* fichier, FMOD_SOUND *musique, FMOD_SYSTEM *system);
FMOD_CHANNEL* JouerMusique(FMOD_SYSTEM *system,FMOD_CHANNEL *channelArret, FMOD_CHANNEL *channel,FMOD_SOUND *musique);

#endif