#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "gun.h"
#include "enemy.h"
#include <SDL2/SDL.h>


void Game_initGame(SDL_Renderer *renderer, int levelNo, Player **player, Gun **gun, EnemyArray **enemies, SDL_FRect **camera);
void Game_gameLoop(SDL_Renderer *renderer, Player *player, Gun *gun, EnemyArray *enemies, SDL_FRect *camera);
void updateCamera(Player *player, SDL_FRect *camera);


void Game_GameOverScreen(SDL_Renderer *renderer, bool *run, int score);


#endif // GAME_H
