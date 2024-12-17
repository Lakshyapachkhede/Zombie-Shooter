#include "levels.h"

int Level_getLevelNumberFromFile()
{
    FILE *f = fopen("../data/level.txt", "r");
    if (f == NULL)
    {
        fclose(f);

        // create a new file if level file does not exist
        f = fopen("../data/level.txt", "w");
        if (f == NULL)
        {
            perror("Error creating level file\n");
            return -1;
        }

        // insert one in new file
        fprintf(f, "%d", LEVEL_1);
        fclose(f);

        // reopen file for reading
        f = fopen("../data/level.txt", "r");
        if (f == NULL)
        {
            perror("Error reopening level file\n");
            return -1;
        }
    }

    // read level no from file
    int levelNo;
    fscanf(f, "%d", &levelNo);

    fclose(f);
    return levelNo;
}

void Level_updateLevelNumber(int levelNo)
{
    FILE *f = fopen("../data/level.txt", "w");
    if (f == NULL)
    {
        perror("Error updating level file");
        return;
    }

    fprintf(f, "%d", levelNo);
    fclose(f);
}

void Level_loadMap(int levelNo)
{
    Map_loadLayersAndMap(levelNo);
}

void Level_generateEnemies(Uint32 *timeNow, Uint32 *prevTime, SDL_Renderer *renderer, Player *player, EnemyArray *enemies, Uint32 timeDifference, int numberOfEnemies)
{
    *timeNow = SDL_GetTicks();
    if (*timeNow - *prevTime > timeDifference)
    {
        for (int i = 0; i < numberOfEnemies; i++)
        {
            float x, y;
            Utils_generateRandomCoordinates(&x, &y);
            char filePath[64];
            sprintf(filePath, "../assets/images/enemy/spider%d.png", Utils_generateRandomNumber(1, 11));
            Enemy_AddEnemyInArray(enemies, renderer, player, x, y, filePath, 3, (Vector2){0, 0}, 4, 10000, 50, 1);
        }
        *prevTime = *timeNow;
    }
}