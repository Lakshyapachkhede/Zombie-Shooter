#include "bullet.h"


Bullet *Bullet_CreateBullet(SDL_Texture *image, float x, float y, Vector2 direction, Uint32 spawnTime, int damage)
{   
    Bullet *bullet = (Bullet*)malloc(sizeof(Bullet));

    bullet->active = true;

    bullet->image = image;
    
    int width, height;
    SDL_QueryTexture(bullet->image, NULL, NULL, &width, &height);
    bullet->rect = (SDL_FRect){x, y, width, height};

    bullet->direction = direction;

    bullet->spawnTime = spawnTime;

    bullet->damage = damage;

    return bullet;
}

void Bullet_UpdateBullet(Bullet *bullet)
{
    bullet->rect.x += BULLET_SPEED * bullet->direction.x;
    bullet->rect.y += BULLET_SPEED * bullet->direction.y;
}

void Bullet_RenderBullet(Bullet *bullet, SDL_Renderer *renderer, SDL_FRect *camera)
{   
    SDL_FRect *destRect = Utils_createFRect(bullet->rect.x - camera->x, bullet->rect.y - camera->y, bullet->rect.w, bullet->rect.h);
    Graphics_renderTextureF(renderer, bullet->image, destRect);
}

BulletArray *Bullet_CreateBulletArray(size_t capacity)
{
    BulletArray *array = (BulletArray *)malloc(sizeof(BulletArray));
    array->bullets = (Bullet **)malloc(sizeof(Bullet *) * capacity);
    array->size = 0;
    array->capacity = capacity;

    return array;
}

void Bullet_AddBulletInArray(BulletArray *array, SDL_Texture *image, float x, float y, Vector2 direction, int damage)
{
    if (array->size >= array->capacity)
    {
        array->capacity *= 2;
        array->bullets = (Bullet **)realloc(array->bullets, array->capacity * sizeof(Bullet*));
    }

    array->bullets[array->size++] = Bullet_CreateBullet(image, x, y, direction, SDL_GetTicks(), damage);
}


void Bullet_RemoveBulletFromArray(BulletArray *array, size_t index)
{
    if (index > array->capacity)
        return;
    
    free(array->bullets[index]);

    for (size_t i = index; i < array->size; i++)
    {
        array->bullets[i] = array->bullets[i+1];
    }

    array->size--;
}

void Bullet_RenderBulletsFromArray(BulletArray *array, SDL_Renderer *renderer, SDL_FRect *camera)
{
    for (size_t i = 0; i < array->size; i++)
    {
        Bullet_RenderBullet(array->bullets[i], renderer, camera);
    }
}

void Bullet_DestroyBulletArray(BulletArray *array)
{
    for (size_t i = 0; i < array->size; i++)
    {
        free(array->bullets[i]);
    }

    free(array->bullets);
    free(array);
    
}

void Bullet_UpdateBulletsFromArray(BulletArray *array, SDL_Renderer *renderer, SDL_FRect *camera)
{   
    for (size_t i = 0; i < array->size; i++)
    {
        if (SDL_GetTicks() - array->bullets[i]->spawnTime > BULLET_LIFETIME)
        {   
            Bullet_RemoveBulletFromArray(array, i);
            continue;
        }

        Bullet_UpdateBullet(array->bullets[i]);
        Bullet_RenderBullet(array->bullets[i], renderer, camera);
    }
}