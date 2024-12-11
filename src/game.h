#ifndef GAME_H
#define GAME_H
#include "player.h"
#include <SDL2/SDL.h>

Player *Game_player = NULL;
SDL_Rect *Game_camera = NULL;

void Game_initGame(SDL_Renderer *renderer, int levelNo, Player **player, SDL_Rect **camera);
void Game_gameLoop(SDL_Renderer *renderer, Player *player, SDL_Rect *camera);






#endif // GAME_H
