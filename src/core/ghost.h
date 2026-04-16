#ifndef PACMAN_CORE_GHOST_H
#define PACMAN_CORE_GHOST_H

#include "core/entity.h"

namespace pacman {
namespace core {

class Ghost : public Entity {
public:
  Ghost();

  int x() const override;
  int y() const override;
  int prev_x() const override;
  int prev_y() const override;
  char direction() const override;
  void setPosition(int x, int y) override;
  void setDirection(char direction) override;
  void savePreviousPosition() override;
  void move(SMap &map) override;

  int ifcookie;
  char last_move;
  int if_boost;
  int xg, yg, prev_xg, prev_yg, lp;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_GHOST_H
