#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "gun.h"
#include <SDL2/SDL.h>


void Game_initGame(SDL_Renderer *renderer, int levelNo, Player **player, Gun **gun, SDL_FRect **camera);
void Game_gameLoop(SDL_Renderer *renderer, Player *player, Gun *gun, SDL_FRect *camera);
void updateCamera(Player *player, SDL_FRect *camera);





#endif // GAME_H
