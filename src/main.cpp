#include "core/config.h"
#include "core/game.h"
#include "core/game_state.h"
#include "core/game_timer.h"
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
  const auto config = core::loadConfig("config.ini");
  std::unique_ptr<rendering::Renderer> renderer;

#ifdef USE_GUI
  renderer = std::make_unique<rendering::GUIRenderer>(config);
  cout << "Starting PACMAN in GUI mode...\n";
#else
  renderer = std::make_unique<rendering::CLIRenderer>();
  cout << "Starting PACMAN in CLI mode...\n";
#endif

  if (!renderer) {
    cerr << "Failed to create renderer\n";
    return 1;
  }

  core::GameContext context(core::MENU, config, std::move(renderer));

  auto state = core::createInitialState(context);
  state->onEnter();

  core::GameTimer timer(context.game.delay);

  while (!context.quit && context.renderer->isOpen()) {
    int elapsed = timer.advance();
    context.game.timer -= elapsed;
    if (context.game.timer < 0) {
      context.game.timer = 0;
    }

    char input = '\0';
    if (context.renderer->keyAvailable()) {
      input = context.renderer->getChar();
    }

    state->handleInput(input);

#ifndef USE_GUI
    bool didUpdate = false;
#endif
    while (timer.hasTick() && !context.quit && context.renderer->isOpen()) {
      state->update();
#ifndef USE_GUI
      didUpdate = true;
#endif
      timer.consumeTick();

      auto nextState = state->takeNextState();
      if (nextState) {
        state = std::move(nextState);
        state->onEnter();
        break;
      }
    }

    context.interpolation = timer.interpolation();

#ifdef USE_GUI
    state->render();
#else
    if (didUpdate) {
      state->render();
    }
#endif

    if (!context.renderer->isOpen()) {
      break;
    }

    context.renderer->sleep(1);
  }

  return 0;
}
