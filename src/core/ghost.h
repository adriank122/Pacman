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
  Direction direction() const override;
  void setPosition(int x, int y) override;
  void setDirection(Direction direction) override;
  void savePreviousPosition() override;
  MapObjectType move(SMap &map) override;

  Direction last_move;
  int xg, yg, prev_xg, prev_yg;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_GHOST_H
