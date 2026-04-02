#ifndef PACMAN_CORE_GHOST_H
#define PACMAN_CORE_GHOST_H

#include "map.h"

namespace pacman {
namespace core {

struct SGhost{
    int ifcookie;
    char last_move;
    int if_boost;
    int xg, yg, lp;
};

void init_ghost(SGhost &ghost, int x, int y);
void ghost_move(SGhost &ghost, SMap &map);
void ghost_boost();

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_GHOST_H
