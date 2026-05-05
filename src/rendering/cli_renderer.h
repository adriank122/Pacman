#ifndef PACMAN_RENDERING_CLI_RENDERER_H
#define PACMAN_RENDERING_CLI_RENDERER_H

#include "core/map/map.h"
#include "renderer.h"

namespace pacman {
namespace rendering {

class CLIRenderer : public Renderer {
public:
  CLIRenderer();
  ~CLIRenderer();

  void showMenu() override;
  void showGameState(const core::Game &game, double interpolation) override;
  void showMap(const core::Map &map) override;
  void showGameCounter(const core::Game &game) override;
  void showGameOver(const std::string &reason) override;
  void showInstructions() override;
  void showLeaderboard(const std::vector<core::LeaderboardEntry> &entries) override;
  void showPauseOverlay() override;
  void clear() override;

  void sleep(int milliseconds) override;
  bool isOpen() const override;
  std::string promptPlayerName() override;

private:
  char tileTypeToChar(core::TileType type);
};

} // namespace rendering
} // namespace pacman

#endif // PACMAN_RENDERING_CLI_RENDERER_H
