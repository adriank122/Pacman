#ifndef PACMAN_CORE_MAP_H
#define PACMAN_CORE_MAP_H

namespace pacman {
namespace core {

struct SMap {
  char map[17][20];
  int xp, yp, xg1, yg1, xg2, yg2;
};

void init_map(SMap &map);
void map_create1(SMap &map);
void map_create2(SMap &map);
void map_create3(SMap &map);
void map_show(SMap map);

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_MAP_H
