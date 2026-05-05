#include "core/game/game.h"
#include "core/config/config.h"
#include <iostream>
#include <vector>

using namespace std;

namespace pacman {
namespace core {

void Game::count() {
  food = 0;

  for (int i = 0; i < map.height(); i++)
    for (int j = 0; j < map.width(); j++)
      if (map.hasPellet(i, j))
        food++;
}

void Game::init(const GameConfig &config) {
  powerUpScore = config.powerUpScore;
  pman = Pacman();
  spawnX = config.pacmanStartX;
  spawnY = config.pacmanStartY;
  pman.setPosition(config.pacmanStartX, config.pacmanStartY);
  pman.savePreviousPosition();
  timer = config.startingTimerMs;
  delay = config.gameTickDelayMs;
  lives = config.startingLives;
  points = 0;
  ghosts.clear();
  ghosts.emplace_back(config.ghost1StartX, config.ghost1StartY);
  ghosts.emplace_back(config.ghost2StartX, config.ghost2StartY);
  ghosts.emplace_back(config.ghost3StartX, config.ghost3StartY);
  ghosts.emplace_back(config.ghost4StartX, config.ghost4StartY);
}

} // namespace core
} // namespace pacman
