#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

void Audio_InitialiseAudio();

Mix_Chunk *Audio_LoadSound(char *path);

Mix_Music *Audio_LoadMusic(char *path);

void Audio_PlaySound(Mix_Chunk *sound);

void Audio_PlayMusic(Mix_Music *music);

void Audio_PlayBGM(Mix_Music *music);

void Audio_CleanUpAudio();

void Audio_StopMusic();






#endif


