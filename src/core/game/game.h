#ifndef PACMAN_CORE_GAME_H
#define PACMAN_CORE_GAME_H

#include "core/entities/ghost.h"
#include "core/entities/pman.h"
#include "core/map/map.h"
#include <string>

namespace pacman {

// Forward declaration of Renderer at correct namespace level
namespace rendering {
class Renderer;
}

namespace core {

struct SGame {
  Pacman pman;
  SMap map;
  Ghost ghost1, ghost2, ghost3, ghost4;
  int timer;
  int delay;
  int food;
};

void game_count(SGame &game);
void game_init(SGame &game, const GameConfig &config);
void save_leaderboard(const SGame &game, const std::string &playerName);

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_GAME_H
