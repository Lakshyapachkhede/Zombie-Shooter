#include "player.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "settings.h"


Player *Player_createPlayer(SDL_Renderer *renderer, float x, float y, char *animationFramesPath, int speed, int animationSpeed, int health)
{
    Player *player = (Player*) malloc(sizeof(Player));
    
    Player_loadAnimationFrames(player, renderer, animationFramesPath);
    player->image = player->animationFrames[0][0];
    player->frameIndex = 0;
    player->animationDirection = ANIMATION_DOWN;
    player->direction = (Vector2){0.0f, 0.0f};
    player->speed = speed;

    player->rect = (SDL_FRect){x, y, 0, 0};

    int playerWidth, playerHeight;
    SDL_QueryTexture(player->image, NULL, NULL, &playerWidth, &playerHeight);

    player->rect.w = playerWidth;
    player->rect.h = playerHeight;

    player->animationSpeed = animationSpeed;

    player->health = health; 

    player->score = 0;

    return player;

}


void Player_loadAnimationFrames(Player *player, SDL_Renderer *renderer, char *animationFramesPath)
{
    char *animationDirectionDir[ANIMATION_DIRECTIONS] = {"down", "up", "left", "right"};

    for (int i = 0; i < ANIMATION_DIRECTIONS; i++)
    {
        for (int j = 0; j < ANIMATION_FRAMES; j++)
        {   
            char filePath[40];
            sprintf(filePath, "%s/%s/%d.png", animationFramesPath, animationDirectionDir[i], j);
            player->animationFrames[i][j] = Graphics_getTextureFromPath(renderer, filePath);
        }
    }

}

void Player_Input(Player *player, const Uint8 *keyState)
{
    player->direction.x = (float)(keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_D]) - (float)(keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_A]);
    player->direction.y = (float)(keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_S]) - (float)(keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W]);

    if (player->direction.x != 0 && player->direction.y != 0) // for normalising digonal movement
        player->direction = Vector2_Normalise(player->direction);
}

void Player_move(Player *player)
{   
    player->rect.x += player->speed * player->direction.x;
    player->rect.y += player->speed * player->direction.y;

           
    if (player->rect.x < 0) player->rect.x = 0;
    if (player->rect.y < 0) player->rect.y = 0;
    if (player->rect.x > BACKGROUND_SIZE - player->rect.w) player->rect.x = BACKGROUND_SIZE - player->rect.w;
    if (player->rect.y > BACKGROUND_SIZE - player->rect.h) player->rect.y = BACKGROUND_SIZE - player->rect.h;
  

}

void Player_Animate(Player *player)
{
    if (player->direction.x != 0)
    {
        if (player->direction.x < 0)    
            player->animationDirection = ANIMATION_LEFT;
        else
            player->animationDirection = ANIMATION_RIGHT;
    }
    else 
    {
        if (player->direction.y < 0)    
            player->animationDirection = ANIMATION_UP;
        else
            player->animationDirection = ANIMATION_DOWN;
    }

    player->frameIndex += player->animationSpeed;
    player->image = player->animationFrames[player->animationDirection][(int)(player->frameIndex) % ANIMATION_FRAMES];


}      

void Player_renderPlayer(Player *player, SDL_Renderer *renderer, SDL_FRect *camera)
{   
    SDL_FRect destRect = (SDL_FRect){player->rect.x - camera->x, player->rect.y - camera->y, player->rect.w, player->rect.h};
    Graphics_renderTextureF(renderer, player->image, &destRect);

}

void Player_RenderHealthBar(SDL_Renderer *renderer, Player *player, SDL_FRect *camera)
{
    // Define position and size
    SDL_Rect fullBarRect = {
        (int)(camera->w - HEALTH_BAR_WIDTH - HEALTH_BAR_MARGIN),
        (int)(HEALTH_BAR_MARGIN),
        HEALTH_BAR_WIDTH,
        HEALTH_BAR_HEIGHT
    };

    int healthBarCurrentWidth = (int)((player->health / (float)PLAYER_MAX_HEALTH) * HEALTH_BAR_WIDTH);

    SDL_Rect currentHealthRect = {
        fullBarRect.x,
        fullBarRect.y,
        healthBarCurrentWidth,
        HEALTH_BAR_HEIGHT
    };

    // Render bars
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    SDL_RenderFillRect(renderer, &fullBarRect);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &currentHealthRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Player_Update(Player *player, const Uint8 *keyState, SDL_Renderer *renderer, SDL_FRect *camera)
{
    Player_Input(player, keyState);
    Player_move(player);
    Player_Animate(player);
    Player_renderPlayer(player, renderer, camera);
    Player_RenderHealthBar(renderer, player, camera);
}


