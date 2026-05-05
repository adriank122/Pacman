#ifndef PACMAN_CORE_GHOST_H
#define PACMAN_CORE_GHOST_H

#include "core/entities/entity.h"

namespace pacman {
namespace core {

class Ghost : public Entity {
public:
  Ghost() = default;
  Ghost(int x, int y);
  TileType move(Map &map) override;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_GHOST_H
