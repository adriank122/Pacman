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
  game.food = 0;

  for (int i = 0; i < 17; i++)
    for (int j = 0; j < 20; j++)
      if (game.map.map[i][j] == core::PELLET ||
          game.map.map[i][j] == core::POWER_UP)
        game.food++;

  if ((game.ghost1.x() == game.pman.x() && game.ghost1.y() == game.pman.y()) ||
      (game.ghost2.x() == game.pman.x() && game.ghost2.y() == game.pman.y())) {
    game.pman.lives--;
    game.pman.setPosition(13, 9);
    game.map.xp = 13;
    game.map.yp = 9;
    game.map.map[game.map.xp][game.map.yp] = core::PACMAN_PLAYER;
  }
}

void game_init(SGame &game) {
  init_map(game.map);
  game.pman = Pacman();
  game.timer = 200000;
  game.delay = 300;
  game.ghost1 = Ghost();
  game.ghost1.setPosition(15, 1);
  game.ghost2 = Ghost();
  game.ghost2.setPosition(15, 18);
  game.ghost3 = Ghost();
  game.ghost3.setPosition(1, 1);
  game.ghost4 = Ghost();
  game.ghost4.setPosition(1, 18);
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
