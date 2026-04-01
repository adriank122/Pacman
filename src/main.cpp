#include <iostream>
#include "game.h"
#include "platform_utils.h"
#include "cli_renderer.h"

using namespace std;

int main()
{
    struct SGame game;
    CLIRenderer renderer;

    game_menu(game, renderer);

    return 0;
}

