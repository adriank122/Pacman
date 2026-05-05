#include "core/systems/systems.h"

namespace pacman {
namespace core {

void checkCollisions(Game &game) {
  for (const Ghost &ghost : game.ghosts) {
    if (ghost.x() == game.pman.x() && ghost.y() == game.pman.y()) {
      game.lives--;
      game.pman.setPosition(game.spawnX, game.spawnY);
      return;
    }
  }
}

void applyScoring(Game &game, TileType consumed) {
  if (consumed == TileType::PELLET) {
    game.points++;
  } else if (consumed == TileType::POWER_UP) {
    game.points += game.powerUpScore;
  }
}

} // namespace core
} // namespace pacman
