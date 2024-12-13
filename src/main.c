#include "graphics.h"
#include "game.h"
#include "settings.h"
#include "levels.h"
#include "player.h"

int main(int argc, char *argv[])
{
    (void)argc; 
    (void)argv;
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    Graphics_initializeGraphics(&window, &renderer, GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    Player *player = NULL;
    SDL_FRect* camera = NULL;
    Game_initGame(renderer, Level_getLevelNumberFromFile(), &player, &camera);

    Game_gameLoop(renderer, player, camera);

    


    return 0;
}
