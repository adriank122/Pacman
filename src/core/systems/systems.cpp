#include "core/systems/systems.h"

namespace pacman {
namespace core {

void checkCollisions(Game &game) {
  for (const Ghost &ghost : game.ghosts) {
    bool sameTile = ghost.x() == game.pman.x() && ghost.y() == game.pman.y();
    bool crossed =
        ghost.x() == game.pman.prev_x() && ghost.y() == game.pman.prev_y() &&
        game.pman.x() == ghost.prev_x() && game.pman.y() == ghost.prev_y();
    if (sameTile || crossed) {
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
