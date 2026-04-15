#include "core/game.h"
#include "rendering/renderer.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

namespace pacman {
namespace core {

void game_count(SGame &game) {
  game.timer -= game.delay;
  game.food = 0;

  for (int i = 0; i < 17; i++)
    for (int j = 0; j < 20; j++)
      if (game.map.map[i][j] == core::PELLET ||
          game.map.map[i][j] == core::POWER_UP)
        game.food++;

  if ((game.ghost1.xg == game.map.xp && game.ghost1.yg == game.map.yp) ||
      (game.ghost2.xg == game.map.xp && game.ghost2.yg == game.map.yp)) {
    game.pman.lives--;
    game.map.xp = 13;
    game.map.yp = 9;
    game.map.map[game.map.xp][game.map.yp] = core::PACMAN_PLAYER;
  }
}

void game_init(SGame &game) {
  init_map(game.map);
  init_pman(game.pman);
  game.timer = 200000;
  game.delay = 300;
  init_ghost(game.ghost1, 15, 1);
  init_ghost(game.ghost2, 15, 18);
  init_ghost(game.ghost3, 1, 1);
  init_ghost(game.ghost4, 1, 18);
}

void save_leaderboard(SGame game) {
  vector<string> leaderboard;
  string line;

  // Read existing leaderboard
  ifstream f("leaderboard.txt");
  while (getline(f, line)) {
    leaderboard.push_back(line);
  }
  f.close();

  // Write leaderboard with new entry
  ofstream of("leaderboard.txt");
  for (const auto &entry : leaderboard) {
    of << entry << "\n";
  }
  of << "Player-" << game.pman.points << "\n";
  of.close();
}

} // namespace core
} // namespace pacman
