#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "vector2.h"


#define ANIMATION_FRAMES 4
#define ANIMATION_DIRECTIONS 4
#define ANIMATION_DOWN 0
#define ANIMATION_UP 1
#define ANIMATION_LEFT 2
#define ANIMATION_RIGHT 3

#define PLAYER_HITBOXRECT_DIFFERENCE 20

#define HEALTH_BAR_WIDTH 200  
#define HEALTH_BAR_HEIGHT 25   
#define HEALTH_BAR_MARGIN 10

#define PLAYER_MAX_HEALTH 100

typedef struct 
{
    SDL_FRect rect;
    SDL_Texture *image;
    SDL_Texture *animationFrames[ANIMATION_DIRECTIONS][ANIMATION_FRAMES];
    int frameIndex;
    int animationDirection;

    Vector2 direction;
    int speed;
    int animationSpeed;

    int health;

    int score;
} Player;

Player *Player_createPlayer(SDL_Renderer *renderer, float x, float y, char *animationFramesPath, int speed, int animationSpeed, int health);

void Player_loadAnimationFrames(Player *player, SDL_Renderer *renderer, char *animationFramesPath);

void Player_Input(Player *player, const Uint8 *keyState);

void Player_move(Player *player);

void Player_Animate(Player *player);

void Player_renderPlayer(Player *player, SDL_Renderer *renderer, SDL_FRect *camera);

void Player_RenderHealthBar(SDL_Renderer *renderer, Player *player, SDL_FRect *camera);

void Player_Update(Player *player, const Uint8 *keyState, SDL_Renderer *renderer, SDL_FRect *camera);

void Player_ShowScore(Player *player ,SDL_Renderer *renderer);
#endif