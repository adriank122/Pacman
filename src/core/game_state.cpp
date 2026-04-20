#include "core/game_state.h"
#include "core/game.h"
#include "core/ghost.h"
#include "core/map.h"
#include "core/pman.h"

#include <iostream>

namespace pacman {
namespace core {

class MainMenuState;
class GameplayState;
class InstructionsState;
class LeaderboardState;
class GameOverState;

// Gameplay state
class GameplayState : public IGameState {
public:
  GameplayState(GameContext &ctx, int lvl)
      : IGameState(ctx), level(lvl), lastInput('\0'), paused(false) {}

  void onEnter() override {
    context.game.state = PLAYING;
    context.level = level;
    context.renderer->clear();

    if (level == 1) {
      map_create1(context.game.map);
    } else {
      map_create2(context.game.map);
    }

    game_count(context.game);
  }

  void handleInput(char input) override {
    if (input == '\0') {
      return;
    }

    if (input == 27) {
      requestTransition(createMainMenuState(context));
      return;
    }

    if (input == ' ') {
      paused = !paused;
      return;
    }

    if (paused) {
      return;
    }

    lastInput = input;
  }

  void update() override {
    if (paused) {
      return;
    }

    context.game.ghost1.move(context.game.map);
    context.game.ghost2.move(context.game.map);
    context.game.ghost3.move(context.game.map);
    context.game.ghost4.move(context.game.map);

    if (lastInput != '\0') {
      context.game.pman.setDirection(lastInput);
    }
    context.game.pman.move(context.game.map);

    game_count(context.game);

    if (context.game.pman.lives <= 0) {
      requestTransition(
          std::make_unique<GameOverState>(context, "lives", level, false));
      return;
    }

    if (context.game.timer <= 0) {
      requestTransition(
          std::make_unique<GameOverState>(context, "time", level, false));
      return;
    }

    if (context.game.food <= 0) {
      requestTransition(
          std::make_unique<GameOverState>(context, "won", level, true));
      return;
    }
  }

  void render() override {
    context.renderer->clear();
    context.renderer->showGameState(context.game, context.interpolation);
    if (paused) {
      context.renderer->showPauseOverlay();
    }
  }

private:
  int level;
  char lastInput;
  bool paused;
};

// Game over state
class GameOverState : public IGameState {
public:
  GameOverState(GameContext &ctx, std::string reason, int level, bool won)
      : IGameState(ctx), reason(std::move(reason)), level(level), won(won) {}

  void onEnter() override {
    context.game.state = GAME_OVER;
    context.renderer->clear();
    context.renderer->showGameOver(reason);

    // Save scoreboard if lost by lives or time
    if (!won) {
      save_leaderboard(context.game);
    }
  }

  void handleInput(char input) override {
    if (input == '\0') {
      return;
    }

    if (input == 'm') {
      requestTransition(createMainMenuState(context));
      return;
    }

    if (won && input == 'o' && level == 1) {
      game_init(context.game, context.config);
      context.level = 2;
      requestTransition(createGameplayState(context, 2));
    }
  }

  void update() override {}
  void render() override {}

private:
  std::string reason;
  int level;
  bool won;
};

// Instructions state
class InstructionsState : public IGameState {
public:
  explicit InstructionsState(GameContext &ctx) : IGameState(ctx) {}

  void onEnter() override {
    context.game.state = INSTRUCTIONS;
    context.renderer->clear();
    context.renderer->showInstructions();
  }

  void handleInput(char input) override {
    if (input == '1') {
      requestTransition(createMainMenuState(context));
    }
  }

  void update() override {}
  void render() override {}
};

// Leaderboard state
class LeaderboardState : public IGameState {
public:
  explicit LeaderboardState(GameContext &ctx) : IGameState(ctx) {}

  void onEnter() override {
    context.game.state = LEADERBOARD;
    context.renderer->clear();
    context.renderer->showLeaderboard();
  }

  void handleInput(char input) override {
    if (input == '1') {
      requestTransition(createMainMenuState(context));
    }
  }

  void update() override {}
  void render() override {}
};

// Main menu state
class MainMenuState : public IGameState {
public:
  explicit MainMenuState(GameContext &ctx) : IGameState(ctx) {}

  void onEnter() override {
    context.game.state = MENU;
    context.renderer->clear();
    context.renderer->showMenu();
  }

  void handleInput(char input) override {
    if (input == '\0') {
      return;
    }

    switch (input) {
    case '1':
      game_init(context.game, context.config);
      context.level = 1;
      requestTransition(createGameplayState(context, 1));
      break;
    case '2':
      requestTransition(createInstructionsState(context));
      break;
    case '3':
      requestTransition(createLeaderboardState(context));
      break;
    case '4':
      context.quit = true;
      break;
    default:
      break;
    }
  }

  void update() override {}
  void render() override {}
};

std::unique_ptr<IGameState> createMainMenuState(GameContext &context) {
  return std::make_unique<MainMenuState>(context);
}

std::unique_ptr<IGameState> createGameplayState(GameContext &context,
                                                int level) {
  return std::make_unique<GameplayState>(context, level);
}

std::unique_ptr<IGameState> createInstructionsState(GameContext &context) {
  return std::make_unique<InstructionsState>(context);
}

std::unique_ptr<IGameState> createLeaderboardState(GameContext &context) {
  return std::make_unique<LeaderboardState>(context);
}

std::unique_ptr<IGameState> createInitialState(GameContext &context) {
  return createMainMenuState(context);
}

} // namespace core
} // namespace pacman
