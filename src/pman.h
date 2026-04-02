#ifndef PMAN_H
#define PMAN_H

#include "map.h"
#include "platform_utils.h"

// Forward declaration
class Renderer;

struct SPman{
    int lives, points;
};

void pman_move(SPman &pman, SMap &map, Renderer &renderer);
void pman_boost();



void init_pman(SPman &pman);

#endif // PMAN_H
