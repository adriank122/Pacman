#ifndef PACMAN_CORE_GAME_CONTEXT_H
#define PACMAN_CORE_GAME_CONTEXT_H

#include <memory>

#include "core/config/config.h"
#include "core/game/game_timer.h"
#include "input_handler/input_handler.h"
#include "rendering/renderer.h"

namespace pacman {
namespace core {

class GameContext {
public:
  GameContext(const GameConfig &config,
              std::unique_ptr<rendering::Renderer> renderer,
              std::unique_ptr<input_handler::InputHandler> inputHandler)
      : config(config), timer(config.gameTickDelayMs),
        renderer(std::move(renderer)), inputHandler(std::move(inputHandler)),
        quit(false) {}

  GameConfig config;
  GameTimer timer;
  std::unique_ptr<rendering::Renderer> renderer;
  std::unique_ptr<input_handler::InputHandler> inputHandler;
  bool quit;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_GAME_CONTEXT_H
