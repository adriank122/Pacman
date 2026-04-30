#ifndef PACMAN_CORE_GAME_H
#define PACMAN_CORE_GAME_H

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
  SMap map;
  std::vector<Ghost> ghosts;
  int timer;
  int delay;
  int food;

  void count();
  void init(const GameConfig &config);
  void saveLeaderboard(const std::string &playerName) const;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_GAME_H
