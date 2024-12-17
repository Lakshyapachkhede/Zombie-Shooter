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
#include <math.h> 

#define GUN_PISTOL_AUDIO_PATH "../assets/audio/pistol.wav"
#define GUN_SHOTGUN_AUDIO_PATH "../assets/audio/shotgun.wav"

#define GUN_TYPE_PISTOL 0
#define GUN_TYPE_SHOTGUN 1

#define GUN_PISTOL_DAMAGE 100
#define GUN_SHOTGUN_DAMAGE 125

#define GUN_PISTOL_COOLDOWN_TIME 100
#define GUN_SHOTGUN_COOLDOWN_TIME 500

#define GUN_AIM_DISTANCE 100
#define GUN_AIM_SIZE 30
#define INITIAL_BULLET_NO 10

#define BULLET_ANGLE_OFFSET 0.261799f 

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

    int damage;

    int gunType;

}Gun;

Gun *Gun_CreateGun(SDL_Renderer *renderer, int gunType, char *aimImagePath, char *bulletImagePath);

void Gun_Input(Gun *gun, Player *player, Uint32 buttons, int mouseX, int mouseY);

void Gun_RenderAim(Gun *gun, SDL_Renderer *renderer, Player *player, SDL_FRect *camera);

void Gun_Shoot(Gun *gun, Player *player);

void Gun_Update(Gun *gun, SDL_Renderer *renderer, Player *player, Uint32 buttons, int mouseX, int mouseY, SDL_FRect *camera);

void Gun_ShootPistol(Gun *gun, Player *player);
void Gun_ShootShotgun(Gun *gun, Player *player);

#endif