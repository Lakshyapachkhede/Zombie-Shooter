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
void Level_generateEnemies(Uint32 *timeNow, Uint32 *prevTime, SDL_Renderer *renderer, Player *player, EnemyArray *enemies, Uint32 timeDifference, int numberOfEnemies);




#endif // LEVELS_H