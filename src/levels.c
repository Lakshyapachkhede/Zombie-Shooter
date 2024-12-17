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

void Level_SpawnManager(Uint32 *currentTime, Uint32 *lastSpawnTime, Uint32 gameStartTime, SDL_Renderer *renderer, Player *player, EnemyArray *enemies)
{
    // Calculate elapsed game time
    Uint32 elapsedTime = *currentTime - gameStartTime;

    // Default values
    Uint32 spawnInterval = 3000; // Time between spawns (ms)
    int enemyHealth = 50;     // Enemy health
    int numberOfEnemies = 3;  // Enemies to spawn per interval
    int enemySpeed = 3;       // Enemy movement speed
    int enemyDamage = 1;      // Enemy damage

    // Adjust difficulty based on time thresholds
    if (elapsedTime > 30000) // After 30 seconds
    {
        spawnInterval = 2500; // Spawn faster
        numberOfEnemies = 4;  // Increase enemy count
        enemyHealth = 60;     // Enemies have more health
        enemySpeed = 4;       // Enemies move faster
        enemyDamage = 2;      // Enemy damages more
    }
    if (elapsedTime > 60000) // After 60 seconds
    {
        spawnInterval = 2000;
        numberOfEnemies = 5;
        enemyHealth = 70;
        enemySpeed = 5;
        enemyDamage = 3;
    }
    if (elapsedTime > 120000) // After 120 seconds
    {
        spawnInterval = 1500;
        numberOfEnemies = 6;
        enemyHealth = 80;
        enemySpeed = 5;
        enemyDamage = 5;
    }

    if (*currentTime - *lastSpawnTime >= spawnInterval)
    {
        for (int i = 0; i < numberOfEnemies; i++)
        {
            float x, y;
            Utils_generateRandomCoordinates(&x, &y);

            char spritePath[64];
            sprintf(spritePath, "../assets/images/enemy/spider%d.png", Utils_generateRandomNumber(1, 11));

            Enemy_AddEnemyInArray(enemies, renderer, player, x, y, spritePath, 3,
                                  (Vector2){0, 0}, enemySpeed, 10000, enemyHealth, enemyDamage);
        }

        *lastSpawnTime = *currentTime;
    }
}
