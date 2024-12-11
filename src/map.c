#include "map.h"
#include <stdio.h>
#include <string.h>
#include "graphics.h"

void Map_loadLayersAndMap(int levelNo)
{
    for (int i = 0; i < MAP_LAYERS; i++)
    {
        char fileName[20];
        sprintf(fileName, "../maps/map%d/%d.csv", levelNo, i);

        FILE *file = fopen(fileName, "r");

        if (file == NULL)
        {
            printf("Error: Opening File: %s\n", fileName);
        }

        char line[1028];
        int row = 0;

        while (fgets(line, sizeof(line), file) && row < MAP_SIZE)
        {
            char *token = strtok(line, ",");
            int col = 0;

            while (token != NULL && col < MAP_SIZE)
            {
                Map_LayersMapGrid[i][row][col] = atoi(token);
                token = strtok(NULL, ",");
                col++;
            }
            row++;
        }

        fclose(file);
    }
}

void Map_loadMapTextures(SDL_Renderer *renderer)
{
    for (int i = 0; i < 256; i++)
    {
        char fileName[40];
        sprintf(fileName, "../assets/images/tiles/%d.png", i);

        Map_Textures[i] = Graphics_getTextureFromPath(renderer, fileName);
    }
}

void Map_renderMap(SDL_Renderer *renderer, SDL_Rect cameraRect)
{
    for (int layer = 0; layer < MAP_LAYERS; layer++)
    { // Loop through layers
        for (int i = 0; i < MAP_SIZE; i++)
        { // Loop through rows
            for (int j = 0; j < MAP_SIZE; j++)
            { // Loop through columns
                int tileX = j * TILE_SIZE - cameraRect.x;
                int tileY = i * TILE_SIZE - cameraRect.y;

                // Check if the tile is visible on the screen
                if (tileX + TILE_SIZE >= 0 && tileX <= cameraRect.w &&
                    tileY + TILE_SIZE >= 0 && tileY <= cameraRect.h)
                {

                    int tileID = Map_LayersMapGrid[layer][i][j]; // Get tile ID from the 3D matrix
                    if (tileID != -1 && Map_Textures[tileID])
                    { // Ensure tile texture exists
                        SDL_Rect destRect = {tileX, tileY, TILE_SIZE, TILE_SIZE};
                        Graphics_renderTexture(renderer, Map_Textures[tileID], &destRect);
                    }
                }
            }
        }
    }
}