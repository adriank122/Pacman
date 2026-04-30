#include "core/systems/systems.h"

namespace pacman {
namespace core {

void checkCollisions(Game &game) {
  for (const Ghost &ghost : game.ghosts) {
    if (ghost.x() == game.pman.x() && ghost.y() == game.pman.y()) {
      game.pman.lives--;
      game.pman.setPosition(game.pman.spawnX, game.pman.spawnY);
      return;
    }
  }
}

void applyScoring(Game &game, TileType consumed) {
  if (consumed == TileType::PELLET) {
    game.pman.points++;
  } else if (consumed == TileType::POWER_UP) {
    game.pman.points += game.powerUpScore;
  }
}

} // namespace core
} // namespace pacman
