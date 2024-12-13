#ifndef GUN_H
#define GUN_H

#include <stdbool.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "bullet.h"
#include "vector2.h"
#include "graphics.h"
#include "audio.h"
#include "player.h"
#include "utils.h"

#define INITIAL_BULLET_NO 50

typedef struct 
{
    int coolDownTime;

    BulletArray *bullets;    

    Mix_Chunk *sound;

    SDL_Texture *aimImage;

    SDL_Texture *bulletImage;

    Vector2 direction;

    Uint32 shootTime;
    bool canShoot;

}Gun;

Gun *Gun_CreateGun(SDL_Renderer *renderer, int coolDownTime, char *soundPath, char *aimImagePath, char *bulletImagePath);

void Gun_Input(Gun *gun, Player *player, Uint32 buttons, int mouseX, int mouseY);

void Gun_RenderAim(Gun *gun, SDL_Renderer *renderer, Player *player, SDL_FRect *camera);

void Gun_Shoot(Gun *gun, Player *player);

void Gun_Update(Gun *gun, SDL_Renderer *renderer, Player *player, Uint32 buttons, int mouseX, int mouseY, SDL_FRect *camera);


#endif