#ifndef PACMAN_CORE_SYSTEMS_H
#define PACMAN_CORE_SYSTEMS_H

#include "core/game.h"
#include "core/map.h"

namespace pacman {
namespace core {

void checkCollisions(SGame &game);
void applyScoring(SGame &game, MapObjectType consumed);

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_SYSTEMS_H
