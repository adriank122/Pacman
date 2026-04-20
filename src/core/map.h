#ifndef PACMAN_CORE_MAP_H
#define PACMAN_CORE_MAP_H

#include "core/config.h"

namespace pacman {
namespace core {

enum MapObjectType { EMPTY, WALL, PELLET, POWER_UP, PACMAN_PLAYER, GHOST };

constexpr int MAP_WIDTH = 20;
constexpr int MAP_HEIGHT = 17;

struct SMap {
  MapObjectType map[MAP_HEIGHT][MAP_WIDTH];
  int width;
  int height;
  int powerUpScore;
  int xp, yp, start_xp, start_yp, xg1, yg1, xg2, yg2;
};

void init_map(SMap &map, const GameConfig &config);
void map_create1(SMap &map);
void map_create2(SMap &map);
void map_create3(SMap &map);
void map_show(SMap map);

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_MAP_H
