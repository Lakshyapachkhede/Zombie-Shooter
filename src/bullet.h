#ifndef BULLET_H
#define BULLET_H

#define BULLET_SPEED 100
#define BULLET_LIFETIME 1000

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector2.h"
#include "graphics.h"
#include "utils.h"


typedef struct 
{   
    bool active;
    SDL_Texture *image;
    SDL_FRect rect;
    Vector2 direction;
    Uint32 spawnTime;
}Bullet;

typedef struct 
{
    Bullet **bullets;
    size_t size;
    size_t capacity;
}BulletArray;

Bullet *Bullet_CreateBullet(SDL_Texture *image, float x, float y, Vector2 direction, Uint32 spawnTime);

void Bullet_UpdateBullet(Bullet *bullet);

void Bullet_RenderBullet(Bullet *bullet, SDL_Renderer *renderer, SDL_FRect *camera);

BulletArray *Bullet_CreateBulletArray(size_t capacity);

void Bullet_AddBulletInArray(BulletArray *array, SDL_Texture *image, float x, float y, Vector2 direction);

void Bullet_UpdateBulletsFromArray(BulletArray *array, SDL_Renderer *renderer, SDL_FRect *camera);

void Bullet_RenderBulletsFromArray(BulletArray *array, SDL_Renderer *renderer, SDL_FRect *camera);

void Bullet_RemoveBulletFromArray(BulletArray *array, size_t index);

void Bullet_DestroyBulletArray(BulletArray *array);






#endif

