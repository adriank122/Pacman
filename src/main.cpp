#include "core/game.h"
#include "rendering/renderer.h"
#include <iostream>
#include <memory>
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
  game.state = core::MENU;
  std::unique_ptr<rendering::Renderer> renderer;

#ifdef USE_GUI
  renderer = std::make_unique<rendering::GUIRenderer>();
  cout << "Starting PACMAN in GUI mode...\n";
#else
  renderer = std::make_unique<rendering::CLIRenderer>();
  cout << "Starting PACMAN in CLI mode...\n";
#endif

  if (renderer) {
    core::game_menu(game, *renderer);
  }

  return 0;
}
