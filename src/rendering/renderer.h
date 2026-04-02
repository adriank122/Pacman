#ifndef PACMAN_RENDERING_RENDERER_H
#define PACMAN_RENDERING_RENDERER_H

#include <string>

namespace pacman {
namespace core {
struct SGame;
struct SMap;
} // namespace core

namespace rendering {

class Renderer {
public:
  virtual ~Renderer() = default;

  // Rendering functions
  virtual void showMenu() = 0;
  virtual void showGameState(const core::SGame &game) = 0;
  virtual void showMap(const core::SMap &map) = 0;
  virtual void showGameCounter(const core::SGame &game) = 0;
  virtual void showGameOver(const std::string &reason) = 0;
  virtual void showInstructions() = 0;
  virtual void showLeaderboard() = 0;
  virtual void clear() = 0;

  // Input functions
  virtual char getChar() = 0;
  virtual bool keyAvailable() = 0;
  virtual void sleep(int milliseconds) = 0;
};

} // namespace rendering
} // namespace pacman

#endif // PACMAN_RENDERING_RENDERER_H
