#ifndef PACMAN_CORE_GAME_H
#define PACMAN_CORE_GAME_H

#include "ghost.h"
#include "map.h"
#include "pman.h"

namespace pacman {

// Forward declaration of Renderer at correct namespace level
namespace rendering {
class Renderer;
}

namespace core {

enum GameState { MENU, PLAYING, INSTRUCTIONS, LEADERBOARD, GAME_OVER, QUIT };

struct SGame {
  Pacman pman;
  SMap map;
  Ghost ghost1, ghost2, ghost3, ghost4;
  int timer;
  int delay;
  int food;
  GameState state;
};

void game_count(SGame &game);
void game_init(SGame &game, const GameConfig &config);
void save_leaderboard(SGame game);

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_GAME_H
