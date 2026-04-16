#include "rendering/cli_renderer.h"
#include "core/game.h"
#include "core/map.h"
#include "utils/platform_utils.h"
#include <fstream>
#include <iomanip>
#include <iostream>

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

void CLIRenderer::showGameState(const core::SGame &game,
                                double /* interpolation */) {
  clear();
  showMap(game.map);
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

void CLIRenderer::showGameCounter(const core::SGame &game) {
  cout << "Time remaining: " << game.timer / 1000 << "\n\n";
  cout << "Points: " << game.pman.points << "\n\n";

  int food_count = 0;
  for (int i = 0; i < 17; i++) {
    for (int j = 0; j < 20; j++) {
      if (game.map.map[i][j] == core::PELLET ||
          game.map.map[i][j] == core::POWER_UP)
        food_count++;
    }
  }
  cout << "Food count: " << food_count << "\n\n";
  cout << "Lives: " << game.pman.lives << "\n\n";
}

void CLIRenderer::showGameOver(const std::string &reason) {
  clear();
  if (reason == "lives") {
    cout << "Game Over!\n\n\nYou have run out of lives.\n\n\nEnter your name "
            "and press Enter:\n\n";
  } else if (reason == "time") {
    cout << "Game Over!\n\n\nYou have run out of time.\n\n\nPress Enter to "
            "return to the menu\n\n";
  } else if (reason == "won") {
    cout << "You have eaten all the dots and completed the level!\n\n\nPress "
            "'o' to proceed to the next level.\n\n";
    cout << "Press 'm' to return to the main menu.\n\n";
  }
}

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
  cout << "\n\n\n";
  string row;
  ifstream f;
  f.open("leaderboard.txt");
  while (!f.eof()) {
    getline(f, row);
    cout << row << "\n\n";
  }
  f.close();
}

} // namespace rendering
} // namespace pacman
