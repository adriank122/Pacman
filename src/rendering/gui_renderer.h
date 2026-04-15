#ifndef PACMAN_RENDERING_GUI_RENDERER_H
#define PACMAN_RENDERING_GUI_RENDERER_H

#include "core/map.h"
#include "renderer.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace pacman {
namespace rendering {

class GUIRenderer : public Renderer {
public:
  GUIRenderer();
  ~GUIRenderer();

  void showMenu() override;
  void showGameState(const core::SGame &game) override;
  void showMap(const core::SMap &map) override;
  void showGameCounter(const core::SGame &game) override;
  void showGameOver(const std::string &reason) override;
  void showInstructions() override;
  void showLeaderboard() override;
  void clear() override;

  char getChar() override;
  bool keyAvailable() override;
  void sleep(int milliseconds) override;
  bool isOpen() const override;

private:
  std::unique_ptr<sf::RenderWindow> window;
  sf::Font fonts;
  char lastKeyPressed;
  std::string currentScreen;

  static const int TILE_SIZE = 16;
  static const int MAP_WIDTH = 20;
  static const int MAP_HEIGHT = 17;
  static const int WINDOW_WIDTH = 320;
  static const int WINDOW_HEIGHT = 272;
  static const int UI_HEIGHT = 80;

  void renderTile(int row, int col, core::MapObjectType tileType,
                  sf::RenderWindow &win);
  void drawText(const std::string &text, float x, float y,
                unsigned int fontSize, const sf::Color &color,
                sf::RenderWindow &win);
  void drawCenteredText(const std::string &text, float y, unsigned int fontSize,
                        const sf::Color &color, sf::RenderWindow &win);
  void handleEvents();
  void drawMenu(sf::RenderWindow &win);
  void drawGameUI(const core::SGame &game, sf::RenderWindow &win);
  void drawInstructions(sf::RenderWindow &win);
  void drawLeaderboard(sf::RenderWindow &win);
  void drawGameOver(const std::string &reason, sf::RenderWindow &win);
};

} // namespace rendering
} // namespace pacman

#endif // PACMAN_RENDERING_GUI_RENDERER_H
