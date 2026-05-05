#ifndef PACMAN_CORE_PMAN_H
#define PACMAN_CORE_PMAN_H

#include "core/entities/entity.h"

namespace pacman {
namespace core {

class Pacman : public Entity {
public:
  Pacman() = default;
  TileType move(Map &map) override;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_PMAN_H
