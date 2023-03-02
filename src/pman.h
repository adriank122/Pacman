#ifndef PMAN_H
#define PMAN_H

#include "map.h"


struct SPman{
    int lives, points;
};

void pman_move(SPman &pman, SMap &map);
void pman_boost();



void init_pman(SPman &pman);

#endif // PMAN_H
