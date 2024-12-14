#ifndef ENEMY_H
#define ENEMY_H
#include <SDL2\SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "settings.h"
#include "player.h"
#include "vector2.h"


#define ENEMY_FRAME_SIZE 64

#define ANIMATION_DIRECTIONS 4
#define ANIMATION_UP 0
#define ANIMATION_RIGHT 1
#define ANIMATION_DOWN 2
#define ANIMATION_LEFT 3

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
    Player *player;

    SDL_Texture *spriteSheet;

    SDL_FRect rect;

    int frameIndex;
    int animationSpeed;

    int health;

    Vector2 direction;
    int speed;

    bool isDied;
    Uint32 deathTime;
    int deathDuration;



}Enemy;

void Enemy_Init();

Enemy *Enemy_CreateEnemy(SDL_Renderer *renderer, Player *player, float x, float y, char *animationFramesPath, int animationSpeed, Vector2 direction, int speed, int deathDuration, int health);
void Enemy_loadAnimationFrames(Enemy *enemy, SDL_Renderer *renderer, char *animationFramesPath)




#endif 