#ifndef PACMAN_CORE_GAME_STATE_H
#define PACMAN_CORE_GAME_STATE_H

#include <memory>
#include <string>

#include "core/config/config.h"
#include "core/game/game.h"
#include "input_handler/input.h"
#include "input_handler/input_handler.h"
#include "rendering/renderer.h"

namespace pacman {
namespace core {

class GameContext {
public:
  GameContext(const GameConfig &config,
              std::unique_ptr<rendering::Renderer> renderer,
              std::unique_ptr<input_handler::InputHandler> inputHandler)
      : config(config), game(), renderer(std::move(renderer)),
        inputHandler(std::move(inputHandler)), quit(false), level(1) {
    game.delay = config.gameTickDelayMs;
  }

  GameConfig config;
  Game game;
  std::unique_ptr<rendering::Renderer> renderer;
  std::unique_ptr<input_handler::InputHandler> inputHandler;
  bool quit;
  int level;
  double interpolation = 0.0;
};

class IGameState {
public:
  explicit IGameState(GameContext &ctx) : context(ctx) {}
  virtual ~IGameState() = default;

  virtual void onEnter() = 0;
  virtual void handleInput(input_handler::Input input) = 0;
  virtual void update() = 0;
  virtual void render() = 0;

  std::unique_ptr<IGameState> takeNextState() { return std::move(nextState); }

protected:
  GameContext &context;
  std::unique_ptr<IGameState> nextState;

  template <typename TState>
  void requestTransition(std::unique_ptr<TState> state) {
    nextState = std::unique_ptr<IGameState>(state.release());
  }
};

std::unique_ptr<IGameState> createInitialState(GameContext &context);
std::unique_ptr<IGameState> createMainMenuState(GameContext &context);
std::unique_ptr<IGameState> createGameplayState(GameContext &context,
                                                int level);
std::unique_ptr<IGameState> createInstructionsState(GameContext &context);
std::unique_ptr<IGameState> createLeaderboardState(GameContext &context);

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_GAME_STATE_H