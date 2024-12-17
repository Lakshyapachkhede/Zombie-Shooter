#ifndef POWERUP_H
#define POWERUP_H
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graphics.h"
#include "utils.h"
#include "gun.h"
#include "collision.h"

#define POWERUP_TYPE_HEALTH 0
#define POWERUP_TYPE_SHOTGUN 1

#define POWERUP_IMG_SIZE 64
#define POWERUP_DURATION 15000
#define POWERUP_RESPAWN_DELAY 15000

typedef struct 
{
    SDL_Texture *image;
    SDL_FRect rect;
    short int type;
    Uint32 activationTime;
    Uint32 respawnTime;
    bool isActivated;
    bool gunChanged;


}Powerup;

Powerup *Powerup_CreatePowerup(SDL_Renderer *renderer, short int type);

void Powerup_Action(Powerup *powerup, Gun *gun, Player *player);

void Powerup_RenderPowerup(Powerup *powerup, SDL_Renderer *renderer, SDL_FRect *camera);
void Powerup_CheckCollisionPlayer(Powerup *powerup, Player *player);
void Powerup_Update(Powerup *powerup, SDL_Renderer *renderer, SDL_FRect *camera, Player *player, Gun *gun);

#endif