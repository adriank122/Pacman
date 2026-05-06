#include "core/states/game_state.h"
#include "core/entities/entity.h"
#include "core/entities/ghost.h"
#include "core/entities/pman.h"
#include "core/game/game.h"
                                                                                                                                                                                          #include "core/leaderboard/leaderboard.h"
#include "core/map/map.h"
#include "core/map/map_loader.h"
#include "core/systems/systems.h"

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
      : IGameState(ctx), level(lvl), lastDirection(Direction::NONE),
        paused(false) {}

  void onEnter() override {
    context.renderer->clear();

    game.init(context.config);
    game.map = MapLoader::load("resources/maps/level" +
                               std::to_string(level) + ".map");
    game.count();
  }

  void handleInput(input_handler::Input input) override {
    if (input.isNull()) {
      return;
    }

    if (input.value() == 27) {
      requestTransition(createMainMenuState(context));
      return;
    }

    if (input.value() == ' ') {
      paused = !paused;
      return;
    }

    if (paused) {
      return;
    }

    switch (input.value()) {
    case 'w':
      lastDirection = Direction::UP;
      break;
    case 'a':
      lastDirection = Direction::LEFT;
      break;
    case 's':
      lastDirection = Direction::DOWN;
      break;
    case 'd':
      lastDirection = Direction::RIGHT;
      break;
    default:
      break;
    }
  }

  void update() override {
    if (paused) {
      return;
    }

    for (Ghost &ghost : game.ghosts)
      ghost.move(game.map);

    if (lastDirection != Direction::NONE) {
      game.pman.setDirection(lastDirection);
    }
    TileType consumed = game.pman.move(game.map);
    applyScoring(game, consumed);
    checkCollisions(game);

    game.count();

    game.timer -= context.config.gameTickDelayMs;
    if (game.timer < 0) {
      game.timer = 0;
    }

    if (game.lives <= 0) {
      requestTransition(
          std::make_unique<GameOverState>(context, "lives", level, false,
                                         game.points));
      return;
    }

    if (game.timer <= 0) {
      requestTransition(
          std::make_unique<GameOverState>(context, "time", level, false,
                                         game.points));
      return;
    }

    if (game.food <= 0) {
      requestTransition(
          std::make_unique<GameOverState>(context, "won", level, true,
                                         game.points));
      return;
    }
  }

  void render() override {
    context.renderer->clear();
    context.renderer->showGameState(game, context.timer.interpolation());
    if (paused) {
      context.renderer->showPauseOverlay();
    }
  }

private:
  int level;
  Direction lastDirection;
  bool paused;
  Game game;
};

// Game over state
class GameOverState : public IGameState {
public:
  GameOverState(GameContext &ctx, std::string reason, int level, bool won,
                int points)
      : IGameState(ctx), reason(std::move(reason)), level(level), won(won),
        points(points) {}

  void onEnter() override {
    context.renderer->clear();
    context.renderer->showGameOver(reason);

    if (!won) {
      std::string name = context.renderer->promptPlayerName();
      Leaderboard lb;
      lb.addEntry(name, points);
      requestTransition(createLeaderboardState(context));
    }
  }

  void handleInput(input_handler::Input input) override {
    if (input.isNull()) {
      return;
    }

    if (input.value() == 'm') {
      requestTransition(createMainMenuState(context));
      return;
    }

    if (won && input.value() == 'o' && level == 1) {
      requestTransition(createGameplayState(context, 2));
    }
  }

  void update() override {}
  void render() override {}

private:
  std::string reason;
  int level;
  bool won;
  int points;
};

// Instructions state
class InstructionsState : public IGameState {
public:
  explicit InstructionsState(GameContext &ctx) : IGameState(ctx) {}

  void onEnter() override {
    context.renderer->clear();
    context.renderer->showInstructions();
  }

  void handleInput(input_handler::Input input) override {
    if (input.value() == '1') {
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
    context.renderer->clear();
    Leaderboard lb;
    context.renderer->showLeaderboard(lb.entries());
  }

  void handleInput(input_handler::Input input) override {
    if (input.value() == '1') {
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
    context.renderer->clear();
    context.renderer->showMenu();
  }

  void handleInput(input_handler::Input input) override {
    if (input.isNull()) {
      return;
    }

    switch (input.value()) {
    case '1':
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
