#ifndef PACMAN_RENDERING_CLI_RENDERER_H
#define PACMAN_RENDERING_CLI_RENDERER_H

#include "core/map/map.h"
#include "renderer.h"
#include <fstream>

namespace pacman {
namespace rendering {

class CLIRenderer : public Renderer {
public:
  CLIRenderer();
  ~CLIRenderer();

  void showMenu() override;
  void showGameState(const core::SGame &game, double interpolation) override;
  void showMap(const core::SMap &map) override;
  void showGameCounter(const core::SGame &game) override;
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
  void showLeaderboardList();
  char mapObjectTypeToChar(core::MapObjectType type);
};

} // namespace rendering
} // namespace pacman

#endif // PACMAN_RENDERING_CLI_RENDERER_H
