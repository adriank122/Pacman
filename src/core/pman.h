#ifndef PACMAN_CORE_PMAN_H
#define PACMAN_CORE_PMAN_H

#include "map.h"

namespace pacman {

// Forward declaration of Renderer at correct namespace level
namespace rendering {
class Renderer;
}

namespace core {

struct SPman {
  int lives, points;
};

void pman_move(SPman &pman, SMap &map, rendering::Renderer &renderer);
void pman_boost();
void init_pman(SPman &pman);

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_PMAN_H
