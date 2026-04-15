#include "core/game.h"
#include "core/game_state.h"
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
  std::unique_ptr<rendering::Renderer> renderer;

#ifdef USE_GUI
  renderer = std::make_unique<rendering::GUIRenderer>();
  cout << "Starting PACMAN in GUI mode...\n";
#else
  renderer = std::make_unique<rendering::CLIRenderer>();
  cout << "Starting PACMAN in CLI mode...\n";
#endif

  if (!renderer) {
    cerr << "Failed to create renderer\n";
    return 1;
  }

  core::GameContext context(core::MENU, 300, std::move(renderer));

  auto state = core::createInitialState(context);
  state->onEnter();

  while (!context.quit) {
    char input = '\0';
    if (context.renderer->keyAvailable()) {
      input = context.renderer->getChar();
    }

    state->handleInput(input);
    state->update();
    state->render();

    auto nextState = state->takeNextState();
    if (nextState) {
      state = std::move(nextState);
      state->onEnter();
    }

    context.renderer->sleep(context.game.delay);
  }

  return 0;
}
