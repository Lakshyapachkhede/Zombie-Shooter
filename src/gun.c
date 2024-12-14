#include "gun.h"

Gun *Gun_CreateGun(SDL_Renderer *renderer, int coolDownTime, char *soundPath, char *aimImagePath, char *bulletImagePath, int damage)
{
    Gun *gun = (Gun *)malloc(sizeof(Gun));
    gun->coolDownTime = coolDownTime;

    gun->sound = Audio_LoadSound(soundPath);

    gun->aimImage = Graphics_getTextureFromPath(renderer, aimImagePath);

    gun->bulletImage = Graphics_getTextureFromPath(renderer, bulletImagePath);

    gun->direction = (Vector2){0, 0};

    gun->bullets = Bullet_CreateBulletArray(INITIAL_BULLET_NO);

    gun->canShoot = false;

    gun->damage = damage;

    return gun;
}

void Gun_Input(Gun *gun, Player *player, Uint32 buttons, int mouseX, int mouseY)
{
    gun->direction = Vector2_Normalise(Vector2_Scale(Vector2_Sub((Vector2){player->rect.x, player->rect.y}, (Vector2){mouseX, mouseY}), -1));

    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT) && gun->canShoot)
    {
        Gun_Shoot(gun, player);
    }

}

void Gun_RenderAim(Gun *gun, SDL_Renderer *renderer, Player *player, SDL_FRect *camera)
{
    SDL_FRect * destRect = Utils_createFRect((player->rect.x + GUN_AIM_DISTANCE * gun->direction.x) - camera->x, (player->rect.y + GUN_AIM_DISTANCE * gun->direction.y) - camera->y, GUN_AIM_SIZE, GUN_AIM_SIZE);
    Graphics_renderTextureF(renderer, gun->aimImage, destRect);
}

void Gun_Shoot(Gun *gun, Player *player)
{   
    Audio_PlaySound(gun->sound);
    Bullet_AddBulletInArray(gun->bullets, gun->bulletImage, (player->rect.x + BULLET_DISTANCE_FROM_PLAYER * player->direction.x), (player->rect.y + BULLET_DISTANCE_FROM_PLAYER * player->direction.y), gun->direction, gun->damage);
    gun->canShoot = false;
    gun->shootTime = SDL_GetTicks();
}

void Gun_Update(Gun *gun, SDL_Renderer *renderer, Player *player, Uint32 buttons, int mouseX, int mouseY, SDL_FRect *camera)
{
    Gun_Input(gun, player, buttons, mouseX, mouseY);
    if (!gun->canShoot && (int)(SDL_GetTicks() - gun->shootTime) >= gun->coolDownTime)
        gun->canShoot = true;
    Gun_RenderAim(gun, renderer, player, camera);
    Bullet_UpdateBulletsFromArray(gun->bullets, renderer, camera);
}