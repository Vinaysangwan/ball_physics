#include "core/Game.hpp"

int main()
{
    // Init Game Class
    Game *game = new Game();

    while (game->running())
    {
        game->update();

        game->render();
    }

    delete game;

    return 0;
}