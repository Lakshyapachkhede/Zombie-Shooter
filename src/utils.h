#ifndef UTILS_H
#define UTILS_H
#include <SDL2/SDL.h>
#include <stdlib.h>

SDL_Rect* Utils_createRect(int x, int y, int w, int h);
SDL_FRect* Utils_createFRect(float x, float y, float w, float h);



#endif
