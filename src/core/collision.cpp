#include "core/collision.h"

namespace pacman {
namespace core {

void checkCollisions(SGame &game) {
  const Ghost *ghosts[] = {&game.ghost1, &game.ghost2, &game.ghost3,
                           &game.ghost4};
  for (const Ghost *ghost : ghosts) {
    if (ghost->x() == game.pman.x() && ghost->y() == game.pman.y()) {
      game.pman.lives--;
      game.pman.setPosition(game.pman.spawnX, game.pman.spawnY);
      game.map.map[game.pman.spawnX][game.pman.spawnY] = PACMAN_PLAYER;
      return;
    }
  }
}

} // namespace core
} // namespace pacman
