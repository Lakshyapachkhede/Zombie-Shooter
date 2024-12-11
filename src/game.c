#include "game.h"
#include "player.h"
#include "settings.h"
#include "levels.h"
#include "map.h"
#include <stdbool.h>
#include "input.h"
#include "utils.h"
#include "graphics.h"

void Game_initGame(SDL_Renderer *renderer, int levelNo, Player **player, SDL_Rect **camera)
{
    *player = Player_createPlayer(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT /2, "../assets/images/player", 5, 5);
    Map_loadLayersAndMap(levelNo);
    Map_loadMapTextures(renderer);
    
    *camera = Utils_createRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Game_gameLoop(SDL_Renderer *renderer, Player *player, SDL_Rect *camera)
{   
    bool run = true;
    SDL_Event e;

    while (run)
    {
        Input_processEvent(&e, &run);

        updateCamera(player, camera);

        Graphics_clearScreen(renderer);

        Map_renderMap(renderer, camera);
        
        Player_Update(player, SDL_GetKeyboardState(NULL), renderer);

        Graphics_presentScreen(renderer);

        SDL_Delay(16);

    }
    

}

void updateCamera(Player *player, SDL_Rect *camera)
{
    // adjust camera positions
    if (player->rect.x < camera->x + CAMERA_EDGE_MARGIN) camera->x = player->rect.x - CAMERA_EDGE_MARGIN;
    if (player->rect.x > camera->x + WINDOW_WIDTH - CAMERA_EDGE_MARGIN) camera->x = player->rect.x - (WINDOW_WIDTH - CAMERA_EDGE_MARGIN);
    if (player->rect.y < camera->y + CAMERA_EDGE_MARGIN) camera->y = player->rect.y - CAMERA_EDGE_MARGIN;
    if (player->rect.y > camera->y + WINDOW_HEIGHT - CAMERA_EDGE_MARGIN) camera->y = player->rect.y - (WINDOW_HEIGHT - CAMERA_EDGE_MARGIN);

    // for keeping camera under boundaries
    if (camera->x < 0) camera->x = 0;
    if (camera->y < 0) camera->y = 0;
    if (camera->x > BACKGROUND_SIZE - WINDOW_WIDTH) camera->x = BACKGROUND_SIZE - WINDOW_WIDTH;
    if (camera->y > BACKGROUND_SIZE - WINDOW_HEIGHT) camera->y = BACKGROUND_SIZE - WINDOW_HEIGHT;
}   
