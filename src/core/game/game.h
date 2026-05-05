#ifndef PACMAN_CORE_GAME_H
#define PACMAN_CORE_GAME_H

#include "core/config/config.h"
#include "core/entities/ghost.h"
#include "core/entities/pman.h"
#include "core/map/map.h"
#include <string>
#include <vector>

namespace pacman {
namespace core {

class Game {
public:
  Pacman pman;
  Map map;
  std::vector<Ghost> ghosts;
  int lives;
  int points;
  int spawnX;
  int spawnY;
  int timer;
  int delay;
  int food;
  int powerUpScore;

  void count();
  void init(const GameConfig &config);
  void saveLeaderboard(const std::string &playerName) const;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_GAME_H
