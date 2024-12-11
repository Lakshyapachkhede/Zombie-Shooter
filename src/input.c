#include "input.h"

void Input_processEvent(SDL_Event *e, bool *run)
{
    if (SDL_PollEvent(e))
    {
        if (e->type == SDL_QUIT)
            *run = false;
    }

}