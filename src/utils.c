#include "utils.h"

SDL_Rect* Utils_createRect(int x, int y, int w, int h)
{
    SDL_Rect* rect = (SDL_Rect*) malloc(sizeof(SDL_Rect));
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;

    return rect;
}

SDL_FRect* Utils_createFRect(float x, float y, float w, float h)
{
    SDL_FRect* rect = (SDL_FRect*) malloc(sizeof(SDL_FRect));
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;

    return rect;
}