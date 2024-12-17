#include "enemy.h"

void Enemy_Init(SDL_Renderer *renderer)
{
    // walk animation rows (0-3) col(4-9)
    for (int dir = 0; dir < ANIMATION_DIRECTIONS; dir++)
    {
        for (int frame = 0; frame < ENEMY_WALK_FRAMES; frame++)
        {
            ENEMY_ANIMATION_WALK_SOURCE_RECT[dir][frame] = (SDL_Rect){
                (ENEMY_WALK_FRAMES_START_COL + frame) * ENEMY_FRAME_SIZE,
                dir * ENEMY_FRAME_SIZE,
                ENEMY_FRAME_SIZE,
                ENEMY_FRAME_SIZE};
        }
    }

    // walk animation rows (0-3) col(4-9)
    for (int dir = 0; dir < ANIMATION_DIRECTIONS; dir++)
    {
        for (int frame = 0; frame < ENEMY_ATTACK_FRAMES; frame++)
        {
            ENEMY_ANIMATION_ATTACK_SOURCE_RECT[dir][frame] = (SDL_Rect){
                frame * ENEMY_FRAME_SIZE,
                dir * ENEMY_FRAME_SIZE,
                ENEMY_FRAME_SIZE,
                ENEMY_FRAME_SIZE};
        }
    }

    // death animation row 4 col (0-3)
    for (int frame = 0; frame < ENEMY_DEATH_FRAMES; frame++)
    {
        ENEMY_ANIMATION_DEATH_SOURCE_RECT[frame] = (SDL_Rect){
            frame * ENEMY_FRAME_SIZE,
            ENEMY_DEATH_FRAMES_START_ROW * ENEMY_FRAME_SIZE,
            ENEMY_FRAME_SIZE,
            ENEMY_FRAME_SIZE};
    }

    bloodTexture = Graphics_getTextureFromPath(renderer, "../assets/images/blood/4.png");
}

Enemy *Enemy_CreateEnemy(SDL_Renderer *renderer, Player *player, float x, float y, char *spriteSheetPath, int animationSpeed, Vector2 direction, int speed, int deathDuration, int health, int damage)
{
    Enemy *enemy = (Enemy *)malloc(sizeof(Enemy));

    enemy->spriteSheet = Graphics_getTextureFromPath(renderer, spriteSheetPath);

    enemy->player = player;

    enemy->rect = (SDL_FRect){x, y, ENEMY_FRAME_SIZE, ENEMY_FRAME_SIZE};

    enemy->state = ENEMY_STATE_WALK;

    enemy->frameIndex = 0;
    enemy->animationDirection = ENEMY_ANIMATION_UP;
    enemy->animationSpeed = animationSpeed;

    enemy->health = health;

    enemy->direction = direction;
    enemy->speed = speed;

    enemy->isDied = false;
    enemy->deathTime = 0;
    enemy->deathDuration = deathDuration;

    enemy->damage = damage;
    enemy->attackTime = 0;

    return enemy;
}

void Enemy_UpdateDirection(Enemy *enemy)
{
    enemy->direction = Vector2_Normalise(Vector2_Sub((Vector2){enemy->player->rect.x, enemy->player->rect.y}, (Vector2){enemy->rect.x, enemy->rect.y}));
}

void Enemy_move(Enemy *enemy)
{
    enemy->rect.x += enemy->speed * enemy->direction.x;
    enemy->rect.y += enemy->speed * enemy->direction.y;

    if (enemy->rect.x < 0)
        enemy->rect.x = 0;
    if (enemy->rect.y < 0)
        enemy->rect.y = 0;
    if (enemy->rect.x > BACKGROUND_SIZE - enemy->rect.w)
        enemy->rect.x = BACKGROUND_SIZE - enemy->rect.w;
    if (enemy->rect.y > BACKGROUND_SIZE - enemy->rect.h)
        enemy->rect.y = BACKGROUND_SIZE - enemy->rect.h;
}

void Enemy_UpdateEnemyPositionOnCollision(Enemy *enemy, EnemyArray *otherEnemies)
{
    for (size_t i = 0; i < otherEnemies->size; i++)
    {
        Enemy *otherEnemy = otherEnemies->enemies[i];

        if (enemy == otherEnemy || otherEnemy->isDied)
        {
            continue; // Skip self and dead enemies
        }

        if (Collision_CheckCollisionF(&enemy->rect, &otherEnemy->rect))
        {
            // Collision detected: resolve overlap by adjusting position
            Vector2 overlap = {
                (enemy->rect.x + enemy->rect.w / 2) - (otherEnemy->rect.x + otherEnemy->rect.w / 2),
                (enemy->rect.y + enemy->rect.h / 2) - (otherEnemy->rect.y + otherEnemy->rect.h / 2)};

            if (fabs(overlap.x) > fabs(overlap.y))
            {
                // Horizontal overlap
                if (overlap.x > 0)
                {
                    enemy->rect.x += 1.0f; // Push right
                }
                else
                {
                    enemy->rect.x -= 1.0f; // Push left
                }
            }
            else
            {
                // Vertical overlap
                if (overlap.y > 0)
                {
                    enemy->rect.y += 1.0f; // Push down
                }
                else
                {
                    enemy->rect.y -= 1.0f; // Push up
                }
            }
        }
    }
}

void Enemy_AttackPlayer(Enemy *enemy)
{   if (!enemy->attackTime)
        enemy->attackTime = SDL_GetTicks();
    
    if (SDL_GetTicks() - enemy->attackTime > 1000 && Collision_CheckCollisionF(&enemy->rect, &enemy->player->rect))
    { 
        enemy->player->health -= enemy->damage;
        enemy->attackTime = SDL_GetTicks();
    }
}

void Enemy_Animate(Enemy *enemy)
{
    if (fabs(enemy->direction.x) > fabs(enemy->direction.y))
    {
        if (enemy->direction.x < 0)
            enemy->animationDirection = ENEMY_ANIMATION_LEFT;
        else
            enemy->animationDirection = ENEMY_ANIMATION_RIGHT;
    }
    else
    {
        if (enemy->direction.y < 0)
            enemy->animationDirection = ENEMY_ANIMATION_UP;
        else
            enemy->animationDirection = ENEMY_ANIMATION_DOWN;
    }

    enemy->frameIndex += enemy->animationSpeed;
}

void Enemy_renderEnemy(Enemy *enemy, SDL_Renderer *renderer, SDL_FRect *camera)
{
    SDL_FRect destRect = (SDL_FRect){enemy->rect.x - camera->x, enemy->rect.y - camera->y, enemy->rect.w, enemy->rect.h};
    switch (enemy->state)
    {
    case ENEMY_STATE_WALK:
        SDL_RenderCopyF(renderer, enemy->spriteSheet, &ENEMY_ANIMATION_WALK_SOURCE_RECT[enemy->animationDirection][(int)(enemy->frameIndex) % ENEMY_WALK_FRAMES], &destRect);
        break;
    case ENEMY_STATE_ATTACK:
        SDL_RenderCopyF(renderer, enemy->spriteSheet, &ENEMY_ANIMATION_ATTACK_SOURCE_RECT[enemy->animationDirection][(int)(enemy->frameIndex) % ENEMY_ATTACK_FRAMES], &destRect);
        break;

    default:
        break;
    }
}

void Enemy_Update(Enemy *enemy, SDL_Renderer *renderer, SDL_FRect *camera, EnemyArray *otherEnemies)
{
    Enemy_UpdateDirection(enemy);
    Enemy_move(enemy);
    Enemy_UpdateEnemyPositionOnCollision(enemy, otherEnemies);
    Enemy_AttackPlayer(enemy);
    Enemy_Animate(enemy);
    Enemy_renderEnemy(enemy, renderer, camera);
}

EnemyArray *Enemy_CreateEnemyArray(size_t capacity)
{
    EnemyArray *array = (EnemyArray *)malloc(sizeof(EnemyArray));
    array->enemies = (Enemy **)malloc(sizeof(Enemy *) * capacity);
    array->size = 0;
    array->capacity = capacity;

    return array;
}

void Enemy_AddEnemyInArray(EnemyArray *array, SDL_Renderer *renderer, Player *player, float x, float y, char *spriteSheetPath, int animationSpeed, Vector2 direction, int speed, int deathDuration, int health, int damage)
{
    if (array->size >= array->capacity)
    {
        array->capacity *= 2;
        array->enemies = (Enemy **)realloc(array->enemies, array->capacity * sizeof(Enemy *));
    }

    array->enemies[array->size++] = Enemy_CreateEnemy(renderer, player, x, y, spriteSheetPath, animationSpeed, direction, speed, deathDuration, health, damage);
}

void Enemy_RemoveEnemyFromArray(EnemyArray *array, size_t index)
{
    if (index > array->capacity)
        return;

    free(array->enemies[index]);

    for (size_t i = index; i < array->size; i++)
    {
        array->enemies[i] = array->enemies[i + 1];
    }

    array->size--;
}

void Enemy_RenderEnemiesFromArray(EnemyArray *array, SDL_Renderer *renderer, SDL_FRect *camera)
{
    for (size_t i = 0; i < array->size; i++)
    {
        Enemy_renderEnemy(array->enemies[i], renderer, camera);
    }
}

void Enemy_DestroyEnemyArray(EnemyArray *array)
{
    for (size_t i = 0; i < array->size; i++)
    {
        free(array->enemies[i]);
    }

    free(array->enemies);
    free(array);
}

void Enemy_UpdateEnemiesFromArray(EnemyArray *array, SDL_Renderer *renderer, SDL_FRect *camera)
{

    for (size_t i = 0; i < array->size; i++)
    {
        if (array->enemies[i]->isDied)
        {
            if (!array->enemies[i]->deathTime)
                array->enemies[i]->deathTime = SDL_GetTicks();
            if (!((SDL_GetTicks() - array->enemies[i]->deathTime) > array->enemies[i]->deathDuration))
            {
                SDL_FRect destRect = (SDL_FRect){array->enemies[i]->rect.x - camera->x, array->enemies[i]->rect.y - camera->y, array->enemies[i]->rect.w, array->enemies[i]->rect.h};
                Graphics_renderTextureF(renderer, bloodTexture, &destRect);
            }
            else
            {
                Enemy_RemoveEnemyFromArray(array, i);
            }
        }
        else
            Enemy_Update(array->enemies[i], renderer, camera, array);
    }
}


void Enemy_HandleBulletEnemyCollisions(EnemyArray *enemyArray, BulletArray *bulletArray)
{
    for (size_t i = 0; i < bulletArray->size; i++)
    {
        Bullet *bullet = bulletArray->bullets[i];

        if (!bullet->active)
        {
            continue; // Skip inactive bullets
        }

        for (size_t j = 0; j < enemyArray->size; j++)
        {
            Enemy *enemy = enemyArray->enemies[j];

            if (enemy->isDied)
                continue;

            // Check if the bullet's rectangle intersects with the enemy's rectangle
            if (Collision_CheckCollisionF(&bullet->rect, &enemy->rect))
            {
                // Collision detected
                bullet->active = false; // Deactivate the bullet

                // Remove the enemy from the array
                enemy->health -= bullet->damage;
                enemy->player->score += 10;

                if (enemy->health < 0) 
                    enemy->isDied = true;


                // Remove the bullet from the array
                Bullet_RemoveBulletFromArray(bulletArray, i);

                // Adjust indices since we've removed elements from the arrays
                i--;

                break; // Exit inner loop to check the next bullet
            }
        }
    }
}