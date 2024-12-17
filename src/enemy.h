#ifndef ENEMY_H
#define ENEMY_H
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "settings.h"
#include "player.h"
#include "vector2.h"
#include <math.h>
#include "graphics.h"
#include "bullet.h"
#include "collision.h"
#include "audio.h"
#include <SDL2/SDL_mixer.h>


#define INITIAL_ENEMY_ARRAY_SIZE 10

#define ENEMY_FRAME_SIZE 64

#define ENEMY_ANIMATION_DIRECTIONS 4
#define ENEMY_ANIMATION_UP 0
#define ENEMY_ANIMATION_RIGHT 3
#define ENEMY_ANIMATION_DOWN 2
#define ENEMY_ANIMATION_LEFT 1

#define ENEMY_WALK_FRAMES 6
#define ENEMY_ATTACK_FRAMES 4
#define ENEMY_DEATH_FRAMES 4

#define ENEMY_TOTAL_STATES 3

#define ENEMY_STATE_WALK 0
#define ENEMY_STATE_ATTACK 1
#define ENEMY_STATE_DIE 2

#define ENEMY_TOTAL_FRAMES_ROW 5
#define ENEMY_TOTAL_FRAMES_COL 10

#define ENEMY_WALK_FRAMES_START_ROW 0
#define ENEMY_WALK_FRAMES_END_ROW 3
#define ENEMY_WALK_FRAMES_START_COL 4
#define ENEMY_WALK_FRAMES_END_COL 9

#define ENEMY_ATTACK_FRAMES_START_ROW 0
#define ENEMY_ATTACK_FRAMES_END_ROW 3
#define ENEMY_ATTACK_FRAMES_START_COL 0
#define ENEMY_ATTACK_FRAMES_END_COL 3

#define ENEMY_DEATH_FRAMES_START_ROW 4
#define ENEMY_DEATH_FRAMES_END_ROW 4
#define ENEMY_DEATH_FRAMES_START_COL 0
#define ENEMY_DEATH_FRAMES_END_COL 3



SDL_Rect ENEMY_ANIMATION_WALK_SOURCE_RECT[ANIMATION_DIRECTIONS][ENEMY_WALK_FRAMES];
SDL_Rect ENEMY_ANIMATION_ATTACK_SOURCE_RECT[ANIMATION_DIRECTIONS][ENEMY_ATTACK_FRAMES];
SDL_Rect ENEMY_ANIMATION_DEATH_SOURCE_RECT[ENEMY_DEATH_FRAMES];

typedef struct 
{
    SDL_Texture *spriteSheet;

    Player *player;

    SDL_FRect rect;

    int state;

    int frameIndex;
    int animationDirection;
    int animationSpeed;

    int health;

    Vector2 direction;
    int speed;

    bool isDied;
    Uint32 deathTime;
    Uint32 deathDuration;

    int damage;
    Uint32 attackTime;
    Mix_Chunk *deathSound;
}Enemy;

typedef struct 
{
    Enemy **enemies;
    size_t size;
    size_t capacity;
}EnemyArray;

SDL_Texture *bloodTexture;

void Enemy_Init(SDL_Renderer *renderer);
Enemy *Enemy_CreateEnemy(SDL_Renderer *renderer, Player *player, float x, float y, char *spriteSheetPath, int animationSpeed, Vector2 direction, int speed, int deathDuration, int health, int damage);
void Enemy_UpdateDirection(Enemy *enemy);
void Enemy_move(Enemy *enemy);
void Enemy_Animate(Enemy *enemy);
void Enemy_UpdateEnemyPositionOnCollision(Enemy *enemy, EnemyArray *otherEnemies);
void Enemy_renderEnemy(Enemy *enemy, SDL_Renderer *renderer, SDL_FRect *camera);
void Enemy_Update(Enemy *enemy, SDL_Renderer *renderer, SDL_FRect *camera, EnemyArray *otherEnemies);


EnemyArray *Enemy_CreateEnemyArray(size_t capacity);
void Enemy_AddEnemyInArray(EnemyArray *array, SDL_Renderer *renderer, Player *player, float x, float y, char *spriteSheetPath, int animationSpeed, Vector2 direction, int speed, int deathDuration, int health, int damage);
void Enemy_RemoveEnemyFromArray(EnemyArray *array, size_t index);
void Enemy_RenderEnemiesFromArray(EnemyArray *array, SDL_Renderer *renderer, SDL_FRect *camera);
void Enemy_DestroyEnemyArray(EnemyArray *array);
void Enemy_UpdateEnemiesFromArray(EnemyArray *array, SDL_Renderer *renderer, SDL_FRect *camera);

void Enemy_HandleBulletEnemyCollisions(EnemyArray *enemyArray, BulletArray *bulletArray);

#endif 