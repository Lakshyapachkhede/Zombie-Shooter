#include "gun.h"

Gun *Gun_CreateGun(SDL_Renderer *renderer, int gunType, char *aimImagePath, char *bulletImagePath)
{
    Gun *gun = (Gun *)malloc(sizeof(Gun));




    gun->aimImage = Graphics_getTextureFromPath(renderer, aimImagePath);

    gun->bulletImage = Graphics_getTextureFromPath(renderer, bulletImagePath);

    gun->direction = (Vector2){0, 0};

    gun->bullets = Bullet_CreateBulletArray(INITIAL_BULLET_NO);

    gun->canShoot = false;

    gun->gunType = gunType;

    if (gun->gunType == GUN_TYPE_PISTOL)
    {
        gun->damage = GUN_PISTOL_DAMAGE;
        gun->coolDownTime = GUN_PISTOL_COOLDOWN_TIME;
        gun->sound = Audio_LoadSound(GUN_PISTOL_AUDIO_PATH);
    }

    else
    {
        gun->damage = GUN_SHOTGUN_DAMAGE;
        gun->coolDownTime = GUN_SHOTGUN_COOLDOWN_TIME;
        gun->sound = Audio_LoadSound(GUN_SHOTGUN_AUDIO_PATH);
    }


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
    if (gun->gunType == GUN_TYPE_PISTOL)
        Gun_ShootPistol(gun, player);
    else
        Gun_ShootShotgun(gun, player);
}

void Gun_Update(Gun *gun, SDL_Renderer *renderer, Player *player, Uint32 buttons, int mouseX, int mouseY, SDL_FRect *camera)
{
    Gun_Input(gun, player, buttons, mouseX, mouseY);
    if (!gun->canShoot && (int)(SDL_GetTicks() - gun->shootTime) >= gun->coolDownTime)
        gun->canShoot = true;
    Gun_RenderAim(gun, renderer, player, camera);
    Bullet_UpdateBulletsFromArray(gun->bullets, renderer, camera);
}

void Gun_ShootPistol(Gun *gun, Player *player)
{   
    Audio_PlaySound(gun->sound);
    Bullet_AddBulletInArray(gun->bullets, gun->bulletImage, (player->rect.x + BULLET_DISTANCE_FROM_PLAYER * player->direction.x), (player->rect.y + BULLET_DISTANCE_FROM_PLAYER * player->direction.y), gun->direction, gun->damage);
    gun->canShoot = false;
    gun->shootTime = SDL_GetTicks();
}

void Gun_ShootShotgun(Gun *gun, Player *player)
{
    // Play the shooting sound
    Audio_PlaySound(gun->sound);

    // Original bullet (straight)
    Bullet_AddBulletInArray(
        gun->bullets, 
        gun->bulletImage, 
        player->rect.x + BULLET_DISTANCE_FROM_PLAYER * player->direction.x,
        player->rect.y + BULLET_DISTANCE_FROM_PLAYER * player->direction.y,
        gun->direction, 
        gun->damage
    );

    // Calculate left bullet direction (rotated by -15 degrees)
    Vector2 leftDirection;
    leftDirection.x = gun->direction.x * cos(-BULLET_ANGLE_OFFSET) - gun->direction.y * sin(-BULLET_ANGLE_OFFSET);
    leftDirection.y = gun->direction.x * sin(-BULLET_ANGLE_OFFSET) + gun->direction.y * cos(-BULLET_ANGLE_OFFSET);

    Bullet_AddBulletInArray(
        gun->bullets, 
        gun->bulletImage, 
        player->rect.x + BULLET_DISTANCE_FROM_PLAYER * player->direction.x,
        player->rect.y + BULLET_DISTANCE_FROM_PLAYER * player->direction.y,
        Vector2_Normalise(leftDirection), 
        gun->damage
    );

    // Calculate right bullet direction (rotated by +15 degrees)
    Vector2 rightDirection;
    rightDirection.x = gun->direction.x * cos(BULLET_ANGLE_OFFSET) - gun->direction.y * sin(BULLET_ANGLE_OFFSET);
    rightDirection.y = gun->direction.x * sin(BULLET_ANGLE_OFFSET) + gun->direction.y * cos(BULLET_ANGLE_OFFSET);

    Bullet_AddBulletInArray(
        gun->bullets, 
        gun->bulletImage, 
        player->rect.x + BULLET_DISTANCE_FROM_PLAYER * player->direction.x,
        player->rect.y + BULLET_DISTANCE_FROM_PLAYER * player->direction.y,
        Vector2_Normalise(rightDirection), 
        gun->damage
    );

    // Update the shoot timer
    gun->canShoot = false;
    gun->shootTime = SDL_GetTicks();
}
