#include "powerup.h"

Powerup *Powerup_CreatePowerup(SDL_Renderer *renderer, short int type)
{
    Powerup *powerup = (Powerup *)malloc(sizeof(Powerup));
    powerup->type = type;

    if (type == POWERUP_TYPE_HEALTH)
    {
        powerup->image = Graphics_getTextureFromPath(renderer, "../assets/images/heart.png");
    }
    else
    {
        powerup->image = Graphics_getTextureFromPath(renderer, "../assets/images/shotgun.png");
    }

    powerup->rect = (SDL_FRect){0, 0, POWERUP_IMG_SIZE, POWERUP_IMG_SIZE};
    Utils_generateRandomCoordinates(&powerup->rect.x, &powerup->rect.y);

    powerup->activationTime = 0;

    powerup->isActivated = false;


    return powerup;
}

void Powerup_Action(Powerup *powerup, Gun *gun, Player *player)
{
    if (powerup->type == POWERUP_TYPE_HEALTH)
        player->health = PLAYER_MAX_HEALTH;
    else
    {
        Gun_changeGun(gun);
        powerup->gunChanged = false;

    }
}

void Powerup_RenderPowerup(Powerup *powerup, SDL_Renderer *renderer, SDL_FRect *camera)
{
    SDL_FRect destRect = (SDL_FRect){powerup->rect.x - camera->x, powerup->rect.y - camera->y, POWERUP_IMG_SIZE, POWERUP_IMG_SIZE};
    Graphics_renderTextureF(renderer, powerup->image , &destRect);
}

void Powerup_CheckCollisionPlayer(Powerup *powerup, Player *player)
{
    if (Collision_CheckCollisionF(&powerup->rect, &player->rect))
    {
        powerup->isActivated = true;
    }
}

void Powerup_Update(Powerup *powerup, SDL_Renderer *renderer, SDL_FRect *camera, Player *player, Gun *gun)
{
    if (!powerup->isActivated)
    {
 
        Powerup_RenderPowerup(powerup, renderer, camera);
        Powerup_CheckCollisionPlayer(powerup, player);

        if (powerup->isActivated)
        {

            Powerup_Action(powerup, gun, player);


            powerup->activationTime = SDL_GetTicks();
            powerup->respawnTime = SDL_GetTicks() + POWERUP_DURATION + POWERUP_RESPAWN_DELAY;
        }
    }
    else
    {

        if (powerup->type == POWERUP_TYPE_SHOTGUN &&
            SDL_GetTicks() - powerup->activationTime > POWERUP_DURATION && !powerup->gunChanged)
        {
            Gun_changeGun(gun);
            powerup->gunChanged = true;
        }

   
        if (SDL_GetTicks() >= powerup->respawnTime)
        {
            powerup->isActivated = false;
            Utils_generateRandomCoordinates(&powerup->rect.x, &powerup->rect.y);
        }
    }
}

