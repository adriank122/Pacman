#include "core/config/config.h"
#include "core/game/game.h"
#include "core/game/game_timer.h"
#include "core/states/game_state.h"
#include "input_handler/input.h"
#include "rendering/renderer.h"
#include <iostream>
#include <memory>
#include <string>

#ifdef USE_GUI
#include "input_handler/gui_input_handler.h"
#include "rendering/gui_renderer.h"
#else
#include "input_handler/cli_input_handler.h"
#include "rendering/cli_renderer.h"
#endif

using namespace std;
using namespace pacman;

int main() {
  const auto config = core::loadConfig("config.ini");
  std::unique_ptr<rendering::Renderer> renderer;
  std::unique_ptr<input_handler::InputHandler> inputHandler;

#ifdef USE_GUI
  auto guiRenderer = std::make_unique<rendering::GUIRenderer>(config);
  inputHandler = guiRenderer->createInputHandler();
  renderer = std::move(guiRenderer);
  cout << "Starting PACMAN in GUI mode...\n";
#else
  renderer = std::make_unique<rendering::CLIRenderer>();
  inputHandler = std::make_unique<input_handler::CLIInputHandler>();
  cout << "Starting PACMAN in CLI mode...\n";
#endif

  if (!renderer) {
    cerr << "Failed to create renderer\n";
    return 1;
  }

  core::GameContext context(config, std::move(renderer),
                            std::move(inputHandler));

  auto state = core::createInitialState(context);
  state->onEnter();

  core::GameTimer timer(context.game.delay);

  while (!context.quit && context.renderer->isOpen()) {
    int elapsed = timer.advance();
    context.game.timer -= elapsed;
    if (context.game.timer < 0) {
      context.game.timer = 0;
    }

    input_handler::Input input;
    if (context.inputHandler->keyAvailable()) {
      input = context.inputHandler->getInput();
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
