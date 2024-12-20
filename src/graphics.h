#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int Graphics_initializeGraphics(SDL_Window **window, SDL_Renderer **renderer, const char *title, int width, int height);

void Graphics_clearScreen(SDL_Renderer *renderer);

void Graphics_renderTextureF(SDL_Renderer *renderer, SDL_Texture *texture, SDL_FRect *rect);

void Graphics_renderTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect);

void Graphics_presentScreen(SDL_Renderer *renderer);

void Graphics_cleanupGraphics(SDL_Window* window, SDL_Renderer *renderer);

SDL_Texture* Graphics_getTextureFromPath(SDL_Renderer *renderer, char* path);

void Graphics_ShowText(SDL_Renderer *renderer, const char *text, int x, int y, int size, SDL_Color color);

SDL_Texture* Graphics_getTextTexture(SDL_Renderer *renderer, const char *text, int size, SDL_Color color);


#endif // GRAPHICS_H
