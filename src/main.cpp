#include <iostream>
#include <string>
#include "game.h"
#include "renderer.h"

#ifdef USE_GUI
#include "gui_renderer.h"
#else
#include "cli_renderer.h"
#endif

using namespace std;

int main()
{
    struct SGame game;
    Renderer* renderer = nullptr;
    
    #ifdef USE_GUI
        renderer = new GUIRenderer();
        cout << "Starting PACMAN in GUI mode...\n";
    #else
        renderer = new CLIRenderer();
        cout << "Starting PACMAN in CLI mode...\n";
    #endif
    
    if (renderer) {
        game_menu(game, *renderer);
        delete renderer;
    }
    
    return 0;
}

