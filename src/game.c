#include "game.h"
#include "settings.h"
#include "levels.h"
#include "map.h"
#include <stdbool.h>
#include "input.h"
#include "utils.h"
#include "graphics.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "enemy.h"
#include "collision.h"

void Game_initGame(SDL_Renderer *renderer, int levelNo, Player **player, Gun **gun, EnemyArray **enemies, SDL_FRect **camera)
{
    *player = Player_createPlayer(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT /2, "../assets/images/player", 5, 1);
    *gun = Gun_CreateGun(renderer, 100, "../assets/audio/pistol.wav", "../assets/images/aim.png", "../assets/images/bullet/bullet.png", GUN_PISTOL_DAMAGE);
    Map_loadLayersAndMap(levelNo);
    Map_loadMapTextures(renderer);
    
    *camera = Utils_createFRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    Enemy_Init(renderer);
    *enemies = Enemy_CreateEnemyArray(INITIAL_ENEMY_ARRAY_SIZE);

}

void Game_gameLoop(SDL_Renderer *renderer, Player *player, Gun *gun, EnemyArray *enemies, SDL_FRect *camera)
{   
    bool run = true;
    SDL_Event e;
    Uint32 time = SDL_GetTicks();
    Uint32 timeNow;
    while (run)
    {   
        timeNow = SDL_GetTicks();
        if (timeNow - time > 1000)
        {
            Enemy_AddEnemyInArray(enemies, renderer, player, 100, 100, "../assets/images/enemy/spider01.png", 3, (Vector2){0, 0}, 4, 10000, 100);
            time = timeNow;
        }
        Input_processEvent(&e, &run);

        const Uint8 *keyState = SDL_GetKeyboardState(NULL);
  
        updateCamera(player, camera);

        Graphics_clearScreen(renderer);

        Map_renderMap(renderer, camera);

        int mouseX, mouseY;
        Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);
        Gun_Update(gun, renderer, player, buttons, mouseX, mouseY, camera);

        Player_Update(player, keyState, renderer, camera);

        Enemy_UpdateEnemiesFromArray(enemies, renderer, camera);

        Enemy_HandleBulletEnemyCollisions(enemies, gun->bullets);

        Graphics_presentScreen(renderer);

        SDL_Delay(16);    
    }
    

}



void updateCamera(Player *player, SDL_FRect *camera)
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
