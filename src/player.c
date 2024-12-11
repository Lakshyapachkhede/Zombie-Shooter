#include "player.h"
#include "graphics.h"
#include "vector2.h"
#include <stdio.h>


void Player_createPlayer(SDL_Renderer *renderer, int x, int y, char *animationFramesPath, float speed, float animationSpeed)
{
    Player player;
    Player_loadAnimationFrames(&player, renderer, "../assets/images/player");
    player.image = player.animationFrames[0][0];
    player.frameIndex = 0;
    player.animationDirection = ANIMATION_DOWN;
    player.direction = (Vector2){0, 0};
    player.speed = speed;

    player.rect = (SDL_FRect){x, y, 0, 0};
    SDL_QueryTexture(player.image, NULL, NULL, &player.rect.w, &player.rect.h);

    player.animationSpeed = animationSpeed;

}


void Player_loadAnimationFrames(Player *player, SDL_Renderer *renderer, char *animationFramesPath)
{
    char *animationDirectionDir[ANIMATION_DIRECTIONS] = {"down", "up", "left", "right"};

    for (int i = 0; i < ANIMATION_DIRECTIONS; i++)
    {
        for (int j = 0; j < ANIMATION_FRAMES; j++)
        {   
            char* filePath[40];
            sprintf(filePath, "%s/%s/%d.png", animationFramesPath, animationDirectionDir[i], j);
            player->animationFrames[i][j] = Graphics_getTextureFromPath(renderer, filePath);
        }
    }

}

void Player_Input(Player *player, Uint8 *keyState)
{
    player->direction.x = (int)(keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_D]) - (int)(keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_A]);
    player->direction.y = (int)(keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_S]) - (int)(keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W]);

    if (player->direction.x != 0 && player->direction.y != 0) // for normalising digonal movement
        player->direction = Vector2_Normalise(player->direction);
}

void Player_move(Player *player)
{   
    player->rect.x += player->speed * player->direction.x;
    player->rect.y += player->speed * player->direction.y;
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
}      

void Player_Update(Player *player, Uint8 *keyState)
{
    Player_Input(player, keyState);
    Player_move(player);
    Player_Animate(player);
}
