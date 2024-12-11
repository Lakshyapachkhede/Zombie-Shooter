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

typedef struct 
{
    SDL_FRect rect;

    SDL_Texture *image;
    SDL_Texture *animationFrames[ANIMATION_DIRECTIONS][ANIMATION_FRAMES];
    int frameIndex;
    int animationDirection;


    Vector2 direction;
    float speed;
    float animationSpeed;

} Player;

Player *Player_createPlayer(SDL_Renderer *renderer, int x, int y, char *animationFramesPath, float speed, float animationSpeed);

void Player_loadAnimationFrames(Player *player, SDL_Renderer *renderer, char *animationFramesPath);

void Player_Input(Player *player, Uint8 *keyState);

void Player_move(Player *player);

void Player_Animate(Player *player);

void Player_Update(Player *player, Uint8 *keyState, SDL_Renderer *renderer);

void Player_renderPlayer(Player *player, SDL_Renderer *renderer);

#endif