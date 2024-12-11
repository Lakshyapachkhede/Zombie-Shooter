#ifndef MAP_H
#define MAP_H

#include "settings.h"
#include "vector2.h"
#include <SDL2/SDL.h>

#define MAX_TILES_TYPES 256

int Map_LayersMapGrid[MAP_LAYERS][MAP_SIZE][MAP_SIZE];

SDL_Texture* Map_Textures[MAX_TILES_TYPES];


// Loads map from csv files
void Map_loadLayersAndMap(int levelNo);

void Map_loadMapTextures(SDL_Renderer *renderer);


void Map_renderMap(SDL_Renderer *renderer, SDL_Rect *cameraRect);


#endif // MAP_H