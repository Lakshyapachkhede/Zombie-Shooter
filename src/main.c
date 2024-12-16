#include "graphics.h"
#include "game.h"
#include "settings.h"
#include "levels.h"
#include "audio.h"
#include "player.h"
#include "gun.h"
#include "enemy.h"

int main(int argc, char *argv[])
{
    (void)argc; 
    (void)argv;
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    Graphics_initializeGraphics(&window, &renderer, GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    Audio_InitialiseAudio();

    Player *player = NULL;
    Gun *gun = NULL;
    SDL_FRect* camera = NULL;
    EnemyArray *enemies = NULL;
    Game_initGame(renderer, Level_getLevelNumberFromFile(), &player, &gun, &enemies, &camera);

    Game_gameLoop(renderer, player, gun, enemies, camera);

    Graphics_cleanupGraphics(window, renderer);
    Audio_CleanUpAudio();

    return 0;
}
