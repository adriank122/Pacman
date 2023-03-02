#ifndef GHOST_H
#define GHOST_H

#include "map.h"

struct SGhost{
    int ifcookie;
    char last_move;
    int if_boost;
    int xg, yg, lp;
};

void init_ghost(SGhost &ghost, int x, int y);

void ghost_move(SGhost &ghost, SMap &map);
void ghost_boost();


#endif // GHOST_H
