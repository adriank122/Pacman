#include "core/systems/systems.h"

namespace pacman {
namespace core {

void checkCollisions(Game &game) {
  for (const Ghost &ghost : game.ghosts) {
    if (ghost.x() == game.pman.x() && ghost.y() == game.pman.y()) {
      game.pman.lives--;
      game.pman.setPosition(game.pman.spawnX, game.pman.spawnY);
      game.map.map[game.pman.spawnX][game.pman.spawnY] = PACMAN_PLAYER;
      return;
    }
  }
}

void applyScoring(Game &game, MapObjectType consumed) {
  if (consumed == PELLET) {
    game.pman.points++;
  } else if (consumed == POWER_UP) {
    game.pman.points += game.map.powerUpScore;
  }
}

} // namespace core
} // namespace pacman
