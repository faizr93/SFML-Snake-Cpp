#include <stdio.h>
#include "game.h"
#include "game.cpp"

int main()
{
    // Init Game Engine
    Game snake_game;

    while (snake_game.isRunning())
    {
        // Update
        snake_game.update();

        // Render
        snake_game.render();
        }

    // End of Application
    return 0;
}