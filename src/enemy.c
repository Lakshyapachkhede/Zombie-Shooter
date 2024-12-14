#include "enemy.h"

void Enemy_Init()
{
    
    for (int i = 0; i < ENEMY_TOTAL_FRAMES_ROW; i++)
    {
        for (int j = 0; j < ENEMY_TOTAL_FRAMES_COL; j++)
        {   
            SDL_Rect rect = (SDL_Rect) {i * ENEMY_FRAME_SIZE, j * ENEMY_FRAME_SIZE, ENEMY_FRAME_SIZE, ENEMY_FRAME_SIZE};

            if (i <= ENEMY_DEATH_FRAMES_START_ROW && j <= ENEMY_ATTACK_FRAMES_END_COL)
            {
                ENEMY_ANIMATION_ATTACK_SOURCE_RECT[i][j] = rect;
                break;
            }
            else if (j <= ENEMY_WALK_FRAMES_END_COL)
            {
                ENEMY_ANIMATION_WALK_SOURCE_RECT[i][j - ENEMY_WALK_FRAMES_START_COL] = rect;
                break;
            }
            else
            {
                if (j < ENEMY_DEATH_FRAMES)
                    ENEMY_ANIMATION_DEATH_SOURCE_RECT[j] = rect;
                else
                    break;
            }
        }
        
    }
    
    
}


Enemy *Enemy_CreateEnemy(SDL_Renderer *renderer, Player *player, float x, float y, char *animationFramesPath, int animationSpeed, Vector2 direction, int speed, int deathDuration, int health)
{
    Enemy *enemy = (Enemy *)malloc(sizeof(Enemy));
    Enemy_loadAnimationFrames(enemy, renderer, animationFramesPath);

    enemy->player = player;

    enemy->frameIndex = 0;
    enemy->image = enemy->animationFrames[enemy->frameIndex];
    enemy->animationSpeed = animationSpeed;

    int w, h;
    SDL_QueryTexture(enemy->image, NULL, NULL, &w, &h);
    enemy->rect = (SDL_FRect){x, y, w, h};

    enemy->speed = speed;
    enemy->direction = direction;

    enemy->health = health;

    enemy->isDied = false;
    enemy->deathDuration = deathDuration;
    
}



void Enemy_loadAnimationFrames(Enemy *enemy, SDL_Renderer *renderer, char *animationFramesPath)
{
    for (int j = 0; j < ENEMY_FRAMES; j++)
    {
        char filePath[40];
        sprintf(filePath, "%s/%d.png", animationFramesPath, j);
        enemy->animationFrames[j] = Graphics_getTextureFromPath(renderer, filePath);
    }
}


void Enemy_UpdateDirection(Enemy *enemy)
{
    enemy->direction = Vector2_Normalise(Vector2_Sub((Vector2){enemy->player->rect.x, enemy->player->rect.y}, (Vector2){enemy->rect.x, enemy->rect.y}));
}

void Enemy_move(Enemy *enemy)
{   
    enemy->rect.x += enemy->speed * enemy->direction.x;
    enemy->rect.y += enemy->speed * enemy->direction.y;

           
    if (enemy->rect.x < 0) enemy->rect.x = 0;
    if (enemy->rect.y < 0) enemy->rect.y = 0;
    if (enemy->rect.x > BACKGROUND_SIZE - enemy->rect.w) enemy->rect.x = BACKGROUND_SIZE - enemy->rect.w;
    if (enemy->rect.y > BACKGROUND_SIZE - enemy->rect.h) enemy->rect.y = BACKGROUND_SIZE - enemy->rect.h;

}

void Enemy_Animate(Enemy *enemy)
{
    enemy->frameIndex += enemy->animationSpeed;
    enemy->image = enemy->animationFrames[(int)(enemy->frameIndex) % ENEMY_FRAMES];
}      

void Enemy_renderEnemy(Enemy *enemy, SDL_Renderer *renderer, SDL_FRect *camera)
{   
    SDL_FRect destRect = (SDL_FRect){enemy->rect.x - camera->x, enemy->rect.y - camera->y, enemy->rect.w, enemy->rect.h};
    Graphics_renderTextureF(renderer, enemy->image, &destRect);
}


void Enemy_Update(Enemy *enemy, SDL_Renderer *renderer, SDL_FRect *camera)
{
    if (enemy->isDied)
    {

    }

    Enemy_UpdateDirection(enemy);
    Enemy_move(enemy);
    Enemy_Animate(enemy);
    Enemy_renderEnemy(enemy, renderer, camera);

}
