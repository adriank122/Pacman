#ifndef PACMAN_CORE_ENTITY_H
#define PACMAN_CORE_ENTITY_H

#include "map.h"

namespace pacman {
namespace core {

enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };

class Entity {
public:
  virtual ~Entity() = default;

  virtual int x() const = 0;
  virtual int y() const = 0;
  virtual int prev_x() const = 0;
  virtual int prev_y() const = 0;
  virtual Direction direction() const = 0;
  virtual void setPosition(int x, int y) = 0;
  virtual void setDirection(Direction direction) = 0;
  virtual void savePreviousPosition() = 0;
  virtual void move(SMap &map) = 0;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_ENTITY_H
