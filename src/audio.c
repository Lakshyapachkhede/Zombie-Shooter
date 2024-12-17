#include "audio.h"

void Audio_InitialiseAudio()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        SDL_Log("SDL could not initialize: %s\n", SDL_GetError());
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_Log("SDL_mixer could not initialize: %s\n", Mix_GetError());
        return;
    }
}

Mix_Chunk *Audio_LoadSound(char *path)
{
    Mix_Chunk *sound = Mix_LoadWAV(path);
    if (!sound)
        SDL_Log("Failed to load sound: %s\n", Mix_GetError());

    return sound;

}

Mix_Music *Audio_LoadMusic(char *path)
{
    Mix_Music *music = Mix_LoadMUS(path);
    if (!music)
        SDL_Log("Failed to load music: %s\n", Mix_GetError());

    return music;
}

void Audio_PlaySound(Mix_Chunk *sound)
{
    Mix_PlayChannel(-1, sound, 0);
}

void Audio_PlayMusic(Mix_Music *music)
{
    Mix_PlayMusic(music, 0);
}

void Audio_StopMusic()
{
    Mix_HaltMusic();
}

void Audio_PlayBGM(Mix_Music *music)
{
    Mix_PlayMusic(music, -1);
}

void Audio_CleanUpAudio()
{
    Mix_CloseAudio();
    SDL_Quit();
}