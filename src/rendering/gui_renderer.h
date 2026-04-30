#ifndef PACMAN_RENDERING_GUI_RENDERER_H
#define PACMAN_RENDERING_GUI_RENDERER_H

#include "core/config/config.h"
#include "core/map/map.h"
#include "renderer.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace pacman {
namespace rendering {

class GUIRenderer : public Renderer {
public:
  explicit GUIRenderer(const core::GameConfig &config);
  ~GUIRenderer();

  void showMenu() override;
  void showGameState(const core::Game &game, double interpolation) override;
  void showMap(const core::SMap &map) override;
  void showGameCounter(const core::Game &game) override;
  void showGameOver(const std::string &reason) override;
  void showInstructions() override;
  void showLeaderboard() override;
  void showPauseOverlay() override;
  void clear() override;

  char getChar() override;
  bool keyAvailable() override;
  void sleep(int milliseconds) override;
  bool isOpen() const override;
  std::string promptPlayerName() override;

private:
  std::unique_ptr<sf::RenderWindow> window;
  sf::Font fonts;
  core::GameConfig config;
  char lastKeyPressed;
  std::string currentScreen;

  void renderTile(int row, int col, core::MapObjectType tileType,
                  sf::RenderWindow &win);
  void drawNamePrompt(const std::string &name, sf::RenderWindow &win);
  void drawText(const std::string &text, float x, float y,
                unsigned int fontSize, const sf::Color &color,
                sf::RenderWindow &win);
  void drawCenteredText(const std::string &text, float y, unsigned int fontSize,
                        const sf::Color &color, sf::RenderWindow &win);
  void handleEvents();
  void drawMenu(sf::RenderWindow &win);
  void drawGameUI(const core::Game &game, sf::RenderWindow &win);
  void drawInstructions(sf::RenderWindow &win);
  void drawLeaderboard(sf::RenderWindow &win);
  void drawGameOver(const std::string &reason, sf::RenderWindow &win);
};

} // namespace rendering
} // namespace pacman

#endif // PACMAN_RENDERING_GUI_RENDERER_H
