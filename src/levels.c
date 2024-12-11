#include "levels.h"
#include "map.h"
#include <stdio.h>


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
    FILE* f = fopen("../data/level.txt", "w");
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


