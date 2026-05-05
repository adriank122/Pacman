#ifndef PACMAN_CORE_ENTITY_H
#define PACMAN_CORE_ENTITY_H

#include "core/map/map.h"

namespace pacman {
namespace core {

enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };

class Entity {
public:
  virtual ~Entity() = default;

  int x() const { return x_; }
  int y() const { return y_; }
  int prev_x() const { return prev_x_; }
  int prev_y() const { return prev_y_; }
  Direction direction() const { return direction_; }
  void setPosition(int x, int y) {
    x_ = x;
    y_ = y;
  }
  void setDirection(Direction d) { direction_ = d; }
  void savePreviousPosition() {
    prev_x_ = x_;
    prev_y_ = y_;
  }

  virtual TileType move(Map &map) = 0;

protected:
  int x_ = 0, y_ = 0, prev_x_ = 0, prev_y_ = 0;
  Direction direction_ = Direction::NONE;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_ENTITY_H
