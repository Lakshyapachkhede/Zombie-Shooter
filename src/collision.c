#include "collision.h"

bool Collision_CheckCollisionF(SDL_FRect *rect1, SDL_FRect *rect2)
{
    return !(rect1->x + rect1->w < rect2->x || // rect1 is to the left of rect2
             rect1->x > rect2->x + rect2->w || // rect1 is to the right of rect2
             rect1->y + rect1->h < rect2->y || // rect1 is above rect2
             rect1->y > rect2->y + rect2->h);  // rect1 is below rect2
}

bool Collision_CheckCollision(SDL_Rect *rect1, SDL_Rect *rect2)
{
    return !(rect1->x + rect1->w < rect2->x || // rect1 is to the left of rect2
             rect1->x > rect2->x + rect2->w || // rect1 is to the right of rect2
             rect1->y + rect1->h < rect2->y || // rect1 is above rect2
             rect1->y > rect2->y + rect2->h);  // rect1 is below rect2
}

