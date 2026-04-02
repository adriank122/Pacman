#include "core/game.h"
#include "rendering/renderer.h"
#include <iostream>
#include <string>

#ifdef USE_GUI
#include "rendering/gui_renderer.h"
#else
#include "rendering/cli_renderer.h"
#endif

using namespace std;
using namespace pacman;

int main() {
  core::SGame game;
  rendering::Renderer *renderer = nullptr;

#ifdef USE_GUI
  renderer = new rendering::GUIRenderer();
  cout << "Starting PACMAN in GUI mode...\n";
#else
  renderer = new rendering::CLIRenderer();
  cout << "Starting PACMAN in CLI mode...\n";
#endif

  if (renderer) {
    core::game_menu(game, *renderer);
    delete renderer;
  }

  return 0;
}
