#ifndef PACMAN_CORE_GAME_STATE_H
#define PACMAN_CORE_GAME_STATE_H

#include <memory>

#include "core/game_context/game_context.h"
#include "input_handler/input.h"

namespace pacman {
namespace core {

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
std::unique_ptr<IGameState> createNameEntryState(GameContext &context,
                                                 int points);

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_GAME_STATE_H
