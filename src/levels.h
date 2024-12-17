#ifndef LEVELS_H
#define LEVELS_H

#define LEVEL_1 1
#define WAVE_ADD_ENIMIES 10

#include "map.h"
#include <stdio.h>
#include "player.h"
#include <SDL2/SDL.h>
#include "vector2.h"
#include "enemy.h"
#include "utils.h"


int Level_getLevelNumberFromFile();
void Level_updateLevelNumber(int levelNo);
void Level_loadMap(int levelNo);
void Level_SpawnManager(Uint32 *currentTime, Uint32 *lastSpawnTime, Uint32 gameStartTime, SDL_Renderer *renderer, Player *player, EnemyArray *enemies);


#endif // LEVELS_H