#include "graphics.h"
#include <SDL2/SDL_image.h>

int Graphics_initializeGraphics(SDL_Window **window, SDL_Renderer **renderer, const char *title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return -1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_Log("Unable to initialize SDL Image: %s", IMG_GetError());
        return -1;
    }

    *window = SDL_CreateWindow(title,
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               width, height,
                               SDL_WINDOW_SHOWN);

    if (!*window) 
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return -1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    if (!*renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(*window);
        return -1;
    }

    return 0;

}


void Graphics_clearScreen(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0 ,0 ,255);
    SDL_RenderClear(renderer);
}


void Graphics_renderTextureF(SDL_Renderer *renderer, SDL_Texture *texture, SDL_FRect *rect)
{
    SDL_RenderCopyF(renderer, texture, NULL, rect);
}



void Graphics_renderTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect)
{
    SDL_RenderCopy(renderer, texture, NULL, rect);
}


void Graphics_presentScreen(SDL_Renderer *renderer)
{
    SDL_RenderPresent(renderer);
}


void Graphics_cleanupGraphics(SDL_Window* window, SDL_Renderer *renderer)
{
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}


SDL_Texture* Graphics_getTextureFromPath(SDL_Renderer *renderer, char* path)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, path);
    if (!texture)
    {
        SDL_Log("Unable to load texture: %s", IMG_GetError());
    }

    return texture;
}

