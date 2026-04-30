#include "core/game/game.h"
#include "core/config/config.h"
#include <algorithm>
#include <fstream>
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
  pman.spawnX = config.pacmanStartX;
  pman.spawnY = config.pacmanStartY;
  pman.setPosition(config.pacmanStartX, config.pacmanStartY);
  pman.savePreviousPosition();
  timer = config.startingTimerMs;
  delay = config.gameTickDelayMs;
  pman.lives = config.startingLives;
  ghosts.clear();
  ghosts.emplace_back(config.ghost1StartX, config.ghost1StartY);
  ghosts.emplace_back(config.ghost2StartX, config.ghost2StartY);
  ghosts.emplace_back(config.ghost3StartX, config.ghost3StartY);
  ghosts.emplace_back(config.ghost4StartX, config.ghost4StartY);
}

void Game::saveLeaderboard(const std::string &playerName) const {
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
      {playerName.empty() ? "Anonymous" : playerName, pman.points});

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
