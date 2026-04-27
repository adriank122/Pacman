#include "rendering/gui_renderer.h"
#include "core/game/game.h"
#include "core/map/map.h"
#include "utils/platform_utils.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

namespace pacman {
namespace rendering {

GUIRenderer::GUIRenderer(const core::GameConfig &config)
    : config(config), lastKeyPressed(0), currentScreen("menu") {
  int totalHeight = config.windowHeight + config.uiHeight;
  window = std::make_unique<sf::RenderWindow>(
      sf::VideoMode(config.windowWidth, totalHeight), "PACMAN");
  window->setFramerateLimit(60);

  if (!fonts.loadFromFile("resources/fonts/Roboto-Regular.ttf")) {
    cerr << "Warning: Could not load font from "
            "resources/fonts/Roboto-Regular.ttf"
         << endl;
  }
}

GUIRenderer::~GUIRenderer() {
  cout << "Closing GUI Renderer..." << endl;
  if (window) {
    window->close();
  }
}

void GUIRenderer::handleEvents() {
  if (!window)
    return;

  sf::Event event;
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window->close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
      case sf::Keyboard::W:
        lastKeyPressed = 'w';
        break;
      case sf::Keyboard::A:
        lastKeyPressed = 'a';
        break;
      case sf::Keyboard::S:
        lastKeyPressed = 's';
        break;
      case sf::Keyboard::D:
        lastKeyPressed = 'd';
        break;
      case sf::Keyboard::Num1:
        lastKeyPressed = '1';
        break;
      case sf::Keyboard::Num2:
        lastKeyPressed = '2';
        break;
      case sf::Keyboard::Num3:
        lastKeyPressed = '3';
        break;
      case sf::Keyboard::Num4:
        lastKeyPressed = '4';
        break;
      case sf::Keyboard::O:
        lastKeyPressed = 'o';
        break;
      case sf::Keyboard::M:
        lastKeyPressed = 'm';
        break;
      case sf::Keyboard::Space:
        lastKeyPressed = ' ';
        break;
      case sf::Keyboard::Escape:
        lastKeyPressed = 27;
        break;
      case sf::Keyboard::Return:
        lastKeyPressed = 13;
        break;
      default:
        break;
      }
    }
  }
}

void GUIRenderer::clear() {
  if (window) {
    window->clear(sf::Color::Black);
  }
}

char GUIRenderer::getChar() {
  char key = lastKeyPressed;
  lastKeyPressed = 0;
  return key;
}

bool GUIRenderer::keyAvailable() {
  handleEvents();
  return lastKeyPressed != 0 && window->isOpen();
}

bool GUIRenderer::isOpen() const { return window ? window->isOpen() : false; }

std::string GUIRenderer::promptPlayerName() {
  if (!window)
    return "Anonymous";

  std::string name;

  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window->close();
        return name.empty() ? "Anonymous" : name;
      }
      if (event.type == sf::Event::TextEntered) {
        sf::Uint32 c = event.text.unicode;
        if (c == 13 || c == 10) {
          return name.empty() ? "Anonymous" : name;
        } else if (c == 8) {
          if (!name.empty())
            name.pop_back();
        } else if (c >= 32 && c < 128 && name.size() < 20) {
          name += static_cast<char>(c);
        }
      }
    }

    window->clear(sf::Color::Black);
    drawNamePrompt(name, *window);
    window->display();
  }

  return name.empty() ? "Anonymous" : name;
}

void GUIRenderer::drawNamePrompt(const std::string &name,
                                 sf::RenderWindow &win) {
  sf::RectangleShape overlay(
      sf::Vector2f(config.windowWidth, config.windowHeight + config.uiHeight));
  overlay.setFillColor(sf::Color(0, 0, 0, 210));
  overlay.setPosition(0, 0);
  win.draw(overlay);

  float boxY = (config.windowHeight - 110) / 2.0f;
  sf::RectangleShape box(sf::Vector2f(config.windowWidth - 40, 110));
  box.setFillColor(sf::Color(20, 20, 70));
  box.setOutlineColor(sf::Color::White);
  box.setOutlineThickness(2);
  box.setPosition(20, boxY);
  win.draw(box);

  drawCenteredText("Enter your name:", boxY + 12, 16, sf::Color::Yellow, win);

  sf::RectangleShape inputField(sf::Vector2f(config.windowWidth - 80, 28));
  inputField.setFillColor(sf::Color(50, 50, 110));
  inputField.setOutlineColor(sf::Color::Cyan);
  inputField.setOutlineThickness(1);
  inputField.setPosition(40, boxY + 42);
  win.draw(inputField);

  drawText(name + "_", 50, boxY + 46, 14, sf::Color::White, win);
  drawCenteredText("Press Enter to confirm", boxY + 82, 12, sf::Color::White,
                   win);
}

void GUIRenderer::sleep(int milliseconds) {
  utils::sleep_ms(milliseconds);
  handleEvents();
}

void GUIRenderer::renderTile(int row, int col, core::MapObjectType tileType,
                             sf::RenderWindow &win) {
  int x = col * config.tileSize;
  int y = row * config.tileSize;

  sf::RectangleShape tile(sf::Vector2f(config.tileSize, config.tileSize));
  tile.setPosition(x, y);

  sf::CircleShape shape;

  switch (tileType) {
  case core::WALL:
    tile.setFillColor(sf::Color::Blue);
    win.draw(tile);
    break;
  case core::PELLET:
    shape.setRadius(2);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x + config.tileSize / 2 - 2, y + config.tileSize / 2 - 2);
    win.draw(shape);
    break;
  case core::POWER_UP:
    shape.setRadius(4);
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(x + config.tileSize / 2 - 4, y + config.tileSize / 2 - 4);
    win.draw(shape);
    break;
  case core::PACMAN_PLAYER:
  case core::GHOST:
    // Entities are drawn separately with interpolation in GUI mode.
    break;
  case core::EMPTY:
    break;
  default:
    break;
  }
}

void GUIRenderer::drawText(const string &text, float x, float y,
                           unsigned int fontSize, const sf::Color &color,
                           sf::RenderWindow &win) {
  sf::Text sfText(text, fonts, fontSize);
  sfText.setPosition(x, y);
  sfText.setFillColor(color);
  win.draw(sfText);
}

void GUIRenderer::drawCenteredText(const string &text, float y,
                                   unsigned int fontSize,
                                   const sf::Color &color,
                                   sf::RenderWindow &win) {
  sf::Text sfText(text, fonts, fontSize);
  float xPos = (config.windowWidth - sfText.getLocalBounds().width) / 2.0f;
  sfText.setPosition(xPos, y);
  sfText.setFillColor(color);
  win.draw(sfText);
}

void GUIRenderer::drawMenu(sf::RenderWindow &win) {
  drawCenteredText("PACMAN", 10, 24, sf::Color::Yellow, win);
  drawCenteredText("by Adrian Kaliciecki", 40, 12, sf::Color::White, win);
  drawCenteredText("1) New Game", 90, 16, sf::Color::Green, win);
  drawCenteredText("2) Instructions", 120, 16, sf::Color::Green, win);
  drawCenteredText("3) Ranking", 150, 16, sf::Color::Green, win);
  drawCenteredText("4) Quit", 180, 16, sf::Color::Green, win);
  drawCenteredText("Select option:", 220, 12, sf::Color::Cyan, win);
}

void GUIRenderer::drawGameUI(const core::SGame &game, sf::RenderWindow &win) {
  sf::RectangleShape uiBg(sf::Vector2f(config.windowWidth, config.uiHeight));
  uiBg.setFillColor(sf::Color(30, 30, 30));
  uiBg.setPosition(0, config.windowHeight);
  win.draw(uiBg);

  sf::RectangleShape separator(sf::Vector2f(config.windowWidth, 2));
  separator.setFillColor(sf::Color::White);
  separator.setPosition(0, config.windowHeight);
  win.draw(separator);

  stringstream ss;
  ss << "Time: " << (game.timer / 1000) << "s";
  drawText(ss.str(), 10, config.windowHeight + 5, 12, sf::Color::Green, win);

  ss.str("");
  ss.clear();
  ss << "Points: " << game.pman.points;
  drawText(ss.str(), 10, config.windowHeight + 25, 12, sf::Color::Cyan, win);

  ss.str("");
  ss.clear();
  ss << "Lives: " << game.pman.lives;
  drawText(ss.str(), 10, config.windowHeight + 45, 12, sf::Color::Yellow, win);

  ss.str("");
  ss.clear();
  ss << "Food: " << game.food;
  drawText(ss.str(), 150, config.windowHeight + 5, 12, sf::Color::Magenta, win);
}

void GUIRenderer::drawInstructions(sf::RenderWindow &win) {
  drawCenteredText("INSTRUCTIONS", 10, 20, sf::Color::Yellow, win);
  drawText("Movement Keys:", 20, 50, 14, sf::Color::White, win);
  drawText("W - Move Up", 30, 70, 12, sf::Color::Green, win);
  drawText("A - Move Left", 30, 85, 12, sf::Color::Green, win);
  drawText("S - Move Down", 30, 100, 12, sf::Color::Green, win);
  drawText("D - Move Right", 30, 115, 12, sf::Color::Green, win);
  drawText("SPACE - Pause Game", 30, 130, 12, sf::Color::Green, win);
  drawText("ESC - Quit Game", 30, 145, 12, sf::Color::Green, win);
  drawText("Objective:", 20, 175, 14, sf::Color::White, win);
  drawText("Collect pellets (dots) to advance levels", 30, 195, 12,
           sf::Color::Cyan, win);
  drawText("Avoid ghosts (red) - You have 3 lives", 30, 210, 12,
           sf::Color::Cyan, win);
  drawText("Special pellets give 5x points", 30, 225, 12, sf::Color::Cyan, win);
  drawCenteredText("Press 1 to return to menu", 260, 12, sf::Color::Yellow,
                   win);
}

void GUIRenderer::drawLeaderboard(sf::RenderWindow &win) {
  drawCenteredText("HIGH SCORES", 10, 20, sf::Color::Yellow, win);

  drawText("Name", 30, 40, 12, sf::Color(180, 180, 180), win);
  drawText("Score", config.windowWidth - 80, 40, 12, sf::Color(180, 180, 180),
           win);

  ifstream rankFile("leaderboard.txt");
  if (!rankFile.is_open()) {
    drawCenteredText("No scores yet", 150, 16, sf::Color::Red, win);
    drawCenteredText("Press 1 to return to menu", 230, 12, sf::Color::Yellow,
                     win);
    return;
  }

  string line;
  int yPos = 60;
  int rank = 1;

  while (getline(rankFile, line) && rank <= 10 &&
         yPos < config.windowHeight - 20) {
    auto tab = line.find('\t');
    if (tab == string::npos)
      continue;

    string name = line.substr(0, tab);
    string score = line.substr(tab + 1);

    sf::Color rankColor = sf::Color::White;
    if (rank == 1)
      rankColor = sf::Color::Yellow;
    else if (rank == 2)
      rankColor = sf::Color(192, 192, 192);
    else if (rank == 3)
      rankColor = sf::Color(184, 134, 11);

    stringstream rankStr;
    rankStr << rank << ". " << name;
    drawText(rankStr.str(), 30, yPos, 13, rankColor, win);
    drawText(score, config.windowWidth - 80, yPos, 13, rankColor, win);

    yPos += 20;
    rank++;
  }
  rankFile.close();

  drawCenteredText("Press 1 to return to menu", 230, 12, sf::Color::Yellow,
                   win);
}

void GUIRenderer::drawGameOver(const string &reason, sf::RenderWindow &win) {
  sf::RectangleShape overlay(
      sf::Vector2f(config.windowWidth, config.windowHeight));
  overlay.setFillColor(sf::Color(0, 0, 0, 150));
  overlay.setPosition(0, 0);
  win.draw(overlay);

  sf::RectangleShape msgBox(sf::Vector2f(config.windowWidth - 40, 120));
  msgBox.setPosition(20, 40);

  if (reason == "lives") {
    msgBox.setFillColor(sf::Color(128, 0, 0));
    win.draw(msgBox);
    drawCenteredText("GAME OVER", 60, 24, sf::Color::White, win);
    drawCenteredText("You ran out of lives!", 100, 16, sf::Color::Yellow, win);
    drawCenteredText("Press 'm' for menu", 140, 12, sf::Color::White, win);
  } else if (reason == "time") {
    msgBox.setFillColor(sf::Color(128, 60, 0));
    win.draw(msgBox);
    drawCenteredText("TIME'S UP!", 60, 24, sf::Color::White, win);
    drawCenteredText("You ran out of time!", 100, 16, sf::Color::Yellow, win);
    drawCenteredText("Press 'm' for menu", 140, 12, sf::Color::White, win);
  } else if (reason == "won") {
    msgBox.setFillColor(sf::Color(0, 128, 0));
    win.draw(msgBox);
    drawCenteredText("LEVEL COMPLETE!", 50, 24, sf::Color::White, win);
    drawCenteredText("You ate all the pellets!", 90, 16, sf::Color::Yellow,
                     win);
    drawCenteredText("Press 'o' for next level or 'm' for menu", 130, 12,
                     sf::Color::White, win);
  }
}

void GUIRenderer::showMenu() {
  if (!window)
    return;
  currentScreen = "menu";
  window->clear(sf::Color::Black);
  drawMenu(*window);
  window->display();
}

void GUIRenderer::showGameState(const core::SGame &game, double interpolation) {
  if (!window)
    return;
  currentScreen = "game";
  window->clear(sf::Color::Black);
  showMap(game.map);

  auto lerp = [](double a, double b, double t) {
    return static_cast<float>(a + (b - a) * t);
  };

  float playerX =
      lerp(game.pman.prev_y(), game.pman.y(), interpolation) * config.tileSize;
  float playerY =
      lerp(game.pman.prev_x(), game.pman.x(), interpolation) * config.tileSize;

  sf::CircleShape playerShape(7.f);
  playerShape.setFillColor(sf::Color::Yellow);
  playerShape.setPosition(playerX + 1.f, playerY + 1.f);
  window->draw(playerShape);

  auto drawGhost = [&](const core::Ghost &ghost) {
    float ghostX =
        lerp(ghost.prev_y(), ghost.y(), interpolation) * config.tileSize;
    float ghostY =
        lerp(ghost.prev_x(), ghost.x(), interpolation) * config.tileSize;
    sf::CircleShape ghostShape(7.f);
    ghostShape.setFillColor(sf::Color::Red);
    ghostShape.setPosition(ghostX + 1.f, ghostY + 1.f);
    window->draw(ghostShape);
  };

  drawGhost(game.ghost1);
  drawGhost(game.ghost2);
  drawGhost(game.ghost3);
  drawGhost(game.ghost4);

  drawGameUI(game, *window);
  window->display();
}

void GUIRenderer::showMap(const core::SMap &map) {
  if (!window)
    return;
  for (int i = 0; i < config.mapHeight; i++) {
    for (int j = 0; j < config.mapWidth; j++) {
      renderTile(i, j, map.map[i][j], *window);
    }
  }
}

void GUIRenderer::showGameCounter(const core::SGame &) {}

void GUIRenderer::showGameOver(const string &reason) {
  if (!window)
    return;
  window->clear(sf::Color::Black);
  drawGameOver(reason, *window);
  window->display();
}

void GUIRenderer::showPauseOverlay() {
  if (!window)
    return;

  sf::RectangleShape overlay(
      sf::Vector2f(config.windowWidth, config.windowHeight + config.uiHeight));
  overlay.setFillColor(sf::Color(0, 0, 0, 160));
  overlay.setPosition(0, 0);
  window->draw(overlay);

  sf::RectangleShape box(sf::Vector2f(config.windowWidth - 60, 120));
  box.setFillColor(sf::Color(20, 20, 20, 220));
  box.setOutlineColor(sf::Color::White);
  box.setOutlineThickness(2);
  box.setPosition(30, (config.windowHeight + config.uiHeight - 120) / 2);
  window->draw(box);

  float centerY = (config.windowHeight + config.uiHeight) / 2.0f;
  drawCenteredText("PAUSED", centerY - 30, 24, sf::Color::Yellow, *window);
  drawCenteredText("Press Space to continue", centerY, 16, sf::Color::White,
                   *window);
  drawCenteredText("Press Esc to return to menu", centerY + 24, 16,
                   sf::Color::White, *window);
  window->display();
}

void GUIRenderer::showInstructions() {
  if (!window)
    return;
  currentScreen = "instructions";
  window->clear(sf::Color::Black);
  drawInstructions(*window);
  window->display();
}

void GUIRenderer::showLeaderboard() {
  if (!window)
    return;
  currentScreen = "ranking";
  window->clear(sf::Color::Black);
  drawLeaderboard(*window);
  window->display();
}

} // namespace rendering
} // namespace pacman
