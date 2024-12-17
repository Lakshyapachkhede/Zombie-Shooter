#ifndef UTILS_H
#define UTILS_H
#include <SDL2/SDL.h>
#include "settings.h"
#include <time.h>
#include <stdlib.h>

SDL_Rect* Utils_createRect(int x, int y, int w, int h);
SDL_FRect* Utils_createFRect(float x, float y, float w, float h);
void Utils_generateRandomCoordinates(float *x, float *y);
int Utils_generateRandomNumber(int min, int max);

#endif
