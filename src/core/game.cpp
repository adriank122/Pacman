#include "core/game.h"
#include "core/config.h"
#include "rendering/renderer.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

namespace pacman {
namespace core {

void game_count(SGame &game) {
  game.food = 0;

  for (int i = 0; i < game.map.height; i++)
    for (int j = 0; j < game.map.width; j++)
      if (game.map.map[i][j] == core::PELLET ||
          game.map.map[i][j] == core::POWER_UP)
        game.food++;
}

void game_init(SGame &game, const GameConfig &config) {
  init_map(game.map, config);
  game.pman = Pacman();
  game.pman.spawnX = config.pacmanStartX;
  game.pman.spawnY = config.pacmanStartY;
  game.pman.setPosition(config.pacmanStartX, config.pacmanStartY);
  game.pman.savePreviousPosition();
  game.timer = config.startingTimerMs;
  game.delay = config.gameTickDelayMs;
  game.pman.lives = config.startingLives;
  game.ghost1 = Ghost();
  game.ghost1.setPosition(config.ghost1StartX, config.ghost1StartY);
  game.ghost2 = Ghost();
  game.ghost2.setPosition(config.ghost2StartX, config.ghost2StartY);
  game.ghost3 = Ghost();
  game.ghost3.setPosition(config.ghost3StartX, config.ghost3StartY);
  game.ghost4 = Ghost();
  game.ghost4.setPosition(config.ghost4StartX, config.ghost4StartY);
}

void save_leaderboard(const SGame &game, const std::string &playerName) {
  vector<pair<string, int>> entries;

  ifstream f("leaderboard.txt");
  string line;
  while (getline(f, line)) {
    auto tab = line.find('\t');
    if (tab != string::npos) {
      try {
        entries.push_back({line.substr(0, tab), stoi(line.substr(tab + 1))});
      } catch (...) {
      }
    }
  }
  f.close();

  entries.push_back(
      {playerName.empty() ? "Anonymous" : playerName, game.pman.points});

  sort(entries.begin(), entries.end(),
       [](const auto &a, const auto &b) { return a.second > b.second; });

  if (entries.size() > 10)
    entries.resize(10);

  ofstream of("leaderboard.txt");
  for (const auto &[name, score] : entries)
    of << name << '\t' << score << '\n';
}

} // namespace core
} // namespace pacman
