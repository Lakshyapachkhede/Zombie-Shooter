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
#include "powerup.h"

void Game_initGame(SDL_Renderer *renderer, int levelNo, Player **player, Gun **gun, EnemyArray **enemies, SDL_FRect **camera)
{
    *player = Player_createPlayer(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "../assets/images/player", 5, 1, 100);
    *gun = Gun_CreateGun(renderer, GUN_TYPE_PISTOL, "../assets/images/aim.png", "../assets/images/bullet/bullet.png");
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

    Uint32 currentTime, lastSpawnTime = 0, gameStartTime = SDL_GetTicks();

    Mix_Music *bgm = Audio_LoadMusic("../assets/music/music1.mp3");
    Audio_PlayBGM(bgm);
    Mix_VolumeMusic(100);

    Powerup *powerupGun = Powerup_CreatePowerup(renderer, POWERUP_TYPE_SHOTGUN);
    Powerup *powerupHealth = Powerup_CreatePowerup(renderer, POWERUP_TYPE_HEALTH);

    while (run)
    {
        Input_processEvent(&e, &run);

        if (player->health <= 0)
        {
            Audio_StopMusic();
            Audio_PlaySound(Audio_LoadSound("../assets/audio/player_death.wav"));
            Game_GameOverScreen(renderer, &run, player->score);

            // Reset the game state after the game over screen
            Audio_PlayBGM(bgm);
            Mix_VolumeMusic(100);
            Game_initGame(renderer, 1, &player, &gun, &enemies, &camera);
            gameStartTime = SDL_GetTicks();
            lastSpawnTime = 0;

            powerupGun = Powerup_CreatePowerup(renderer, POWERUP_TYPE_SHOTGUN);
            powerupHealth = Powerup_CreatePowerup(renderer, POWERUP_TYPE_HEALTH);
            continue;
        }

        currentTime = SDL_GetTicks();
        Level_SpawnManager(&currentTime, &lastSpawnTime, gameStartTime, renderer, player, enemies);

        const Uint8 *keyState = SDL_GetKeyboardState(NULL);

        updateCamera(player, camera);

        Graphics_clearScreen(renderer);

        Map_renderMap(renderer, camera);

        int mouseX, mouseY;
        Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);
        Gun_Update(gun, renderer, player, buttons, mouseX, mouseY, camera);

        Enemy_UpdateEnemiesFromArray(enemies, renderer, camera);

        Enemy_HandleBulletEnemyCollisions(enemies, gun->bullets);

        Powerup_Update(powerupGun, renderer, camera, player, gun);
        Powerup_Update(powerupHealth, renderer, camera, player, gun);

        Player_Update(player, keyState, renderer, camera);

        Graphics_presentScreen(renderer);

        SDL_Delay(16);
    }
}

void updateCamera(Player *player, SDL_FRect *camera)
{

    if (player->rect.x < camera->x + CAMERA_EDGE_MARGIN)
        camera->x = player->rect.x - CAMERA_EDGE_MARGIN;
    if (player->rect.x > camera->x + WINDOW_WIDTH - CAMERA_EDGE_MARGIN)
        camera->x = player->rect.x - (WINDOW_WIDTH - CAMERA_EDGE_MARGIN);
    if (player->rect.y < camera->y + CAMERA_EDGE_MARGIN)
        camera->y = player->rect.y - CAMERA_EDGE_MARGIN;
    if (player->rect.y > camera->y + WINDOW_HEIGHT - CAMERA_EDGE_MARGIN)
        camera->y = player->rect.y - (WINDOW_HEIGHT - CAMERA_EDGE_MARGIN);

    if (camera->x < 0)
        camera->x = 0;
    if (camera->y < 0)
        camera->y = 0;
    if (camera->x > BACKGROUND_SIZE - WINDOW_WIDTH)
        camera->x = BACKGROUND_SIZE - WINDOW_WIDTH;
    if (camera->y > BACKGROUND_SIZE - WINDOW_HEIGHT)
        camera->y = BACKGROUND_SIZE - WINDOW_HEIGHT;
}

void Game_GameOverScreen(SDL_Renderer *renderer, bool *run, int score)
{
    bool waiting = true;
    SDL_Event event;

    SDL_Color white = {255, 255, 255, 255};

    SDL_Texture *gameOverText = Graphics_getTextTexture(renderer, "Game Over", 72, white);
    SDL_Texture *restartText = Graphics_getTextTexture(renderer, "Press  Enter  to  Restart", 36, white);
    SDL_Texture *devText = Graphics_getTextTexture(renderer, "Lakshya  Pachkhede", 24, white);

    int gw, gh, rw, rh, dw, dh;
    SDL_QueryTexture(gameOverText, NULL, NULL, &gw, &gh);
    SDL_QueryTexture(restartText, NULL, NULL, &rw, &rh);
    SDL_QueryTexture(devText, NULL, NULL, &dw, &dh);
    
    SDL_Rect gameOverRect = {(WINDOW_WIDTH / 2) - (gw / 2), (WINDOW_HEIGHT / 2) - (gh / 2) - 50, gw, gh};
    SDL_Rect restartRect = {(WINDOW_WIDTH / 2) - (rw / 2), (WINDOW_HEIGHT / 2) + 50, rw, rh};
    SDL_Rect devRect = {WINDOW_WIDTH - dw - HEALTH_BAR_MARGIN, WINDOW_HEIGHT - dh - HEALTH_BAR_MARGIN, dw, dh};

    char scoreText[64];
    sprintf(scoreText, "score %d", score);

    while (waiting)
    {
        // Handle events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                waiting = false;
                *run = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            {
                waiting = false;
            }
        }

        Graphics_clearScreen(renderer);

        Graphics_renderTexture(renderer, gameOverText, &gameOverRect);
        Graphics_renderTexture(renderer, restartText, &restartRect);
        Graphics_renderTexture(renderer, devText, &devRect);
        Graphics_ShowText(renderer, scoreText, HEALTH_BAR_MARGIN, HEALTH_BAR_MARGIN, 24, white);

        Graphics_presentScreen(renderer);
    }
}
