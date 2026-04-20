#ifndef PACMAN_CORE_CONFIG_H
#define PACMAN_CORE_CONFIG_H

#include <string>

namespace pacman {
namespace core {

struct GameConfig {
  int mapWidth = 20;
  int mapHeight = 17;
  int tileSize = 16;
  int uiHeight = 80;
  int startingLives = 3;
  int startingTimerMs = 200000;
  int gameTickDelayMs = 300;
  int pacmanStartX = 13;
  int pacmanStartY = 9;
  int ghost1StartX = 15;
  int ghost1StartY = 1;
  int ghost2StartX = 15;
  int ghost2StartY = 18;
  int ghost3StartX = 1;
  int ghost3StartY = 1;
  int ghost4StartX = 1;
  int ghost4StartY = 18;
  int powerUpScore = 5;
  int windowWidth = mapWidth * tileSize;
  int windowHeight = mapHeight * tileSize;

  void updateDerivedValues();
};

GameConfig loadConfig(const std::string &path = "config.ini");

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_CONFIG_H
