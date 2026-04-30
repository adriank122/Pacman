#include "rendering/cli_renderer.h"
#include "core/game/game.h"
#include "core/map/map.h"
#include "utils/platform_utils.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

namespace pacman {
namespace rendering {

CLIRenderer::CLIRenderer() {}

CLIRenderer::~CLIRenderer() {}

void CLIRenderer::clear() { utils::clear_screen(); }

char CLIRenderer::getChar() { return utils::get_char(); }

bool CLIRenderer::keyAvailable() { return utils::key_available(); }

void CLIRenderer::sleep(int milliseconds) { utils::sleep_ms(milliseconds); }

bool CLIRenderer::isOpen() const { return true; }

void CLIRenderer::showMenu() {
  clear();
  cout << "\t\tPACMAN\n\n\n";
  cout << "Press:\n\n";
  cout << "1 -->\tNew Game\n";
  cout << "2 -->\tInstructions\n";
  cout << "3 -->\tLeaderboard\n";
  cout << "4 -->\tQuit\n\n";
}

void CLIRenderer::showGameState(const core::Game &game,
                                double /* interpolation */) {
  clear();

  char display[17][20];
  for (int i = 0; i < 17; i++)
    for (int j = 0; j < 20; j++)
      display[i][j] = mapObjectTypeToChar(game.map.map[i][j]);

  for (const core::Ghost &g : game.ghosts)
    display[g.x()][g.y()] = 'A';
  display[game.pman.x()][game.pman.y()] = 'O';

  for (int i = 0; i < 17; i++) {
    for (int j = 0; j < 20; j++)
      cout << setw(2) << display[i][j];
    cout << "\n";
  }

  showGameCounter(game);
}

void CLIRenderer::showMap(const core::SMap &map) {
  for (int i = 0; i < 17; i++) {
    for (int j = 0; j < 20; j++) {
      cout << setw(2) << mapObjectTypeToChar(map.map[i][j]);
    }
    cout << "\n";
  }
}

char CLIRenderer::mapObjectTypeToChar(core::MapObjectType type) {
  switch (type) {
  case core::EMPTY:
    return ' ';
  case core::WALL:
    return 'x';
  case core::PELLET:
    return '.';
  case core::POWER_UP:
    return 'e';
  case core::PACMAN_PLAYER:
    return 'O';
  case core::GHOST:
    return 'A';
  }
  return ' ';
}

void CLIRenderer::showGameCounter(const core::Game &game) {
  cout << "Time remaining: " << game.timer / 1000 << "\n\n";
  cout << "Points: " << game.pman.points << "\n\n";
  cout << "Food count: " << game.food << "\n\n";
  cout << "Lives: " << game.pman.lives << "\n\n";
}

void CLIRenderer::showGameOver(const std::string &reason) {
  clear();
  if (reason == "lives") {
    cout << "Game Over!\n\n\nYou have run out of lives.\n\n\n";
  } else if (reason == "time") {
    cout << "Game Over!\n\n\nYou have run out of time.\n\n\n";
  } else if (reason == "won") {
    cout << "You have eaten all the dots and completed the level!\n\n\n";
    cout << "Press 'o' to proceed to the next level.\n\n";
    cout << "Press 'm' to return to the main menu.\n\n";
    return;
  }
  cout << "Enter your name and press Enter:\n\n";
}

std::string CLIRenderer::promptPlayerName() { return utils::read_line(); }

void CLIRenderer::showInstructions() {
  clear();
  cout << "\nW --> move up\n";
  cout << "A --> move left\n";
  cout << "S --> move down\n";
  cout << "D --> move right\n";
  cout << "SPACE --> pause the game\n";
  cout << "ESC --> quit the game\n\n";
  cout << "Collect all the dots to complete the level!\nDon't let the ghosts "
          "catch you.\n";
  cout << "You have three lives\n\n\n\n";
  cout << "1 -->Back to main menu\n";
}

void CLIRenderer::showLeaderboard() {
  clear();
  cout << "Leaderboard:\n";
  showLeaderboardList();
  cout << "\n\n\n";
  cout << "1 -->Back to main menu";
}

void CLIRenderer::showPauseOverlay() {
  cout << "\n--- PAUSED ---\n";
  cout << "Press Space to continue, Esc to return to the main menu\n";
}

void CLIRenderer::showLeaderboardList() {
  cout << "\n\n";
  cout << left << setw(6) << "Rank" << setw(22) << "Name"
       << "Score\n";
  cout << string(38, '-') << "\n\n";

  ifstream f("leaderboard.txt");
  string line;
  int rank = 1;
  while (getline(f, line) && rank <= 10) {
    auto tab = line.find('\t');
    if (tab == string::npos)
      continue;
    string name = line.substr(0, tab);
    string score = line.substr(tab + 1);
    cout << left << setw(6) << rank << setw(22) << name << score << "\n\n";
    rank++;
  }
  f.close();
}

} // namespace rendering
} // namespace pacman
