#ifndef PACMAN_CORE_PMAN_H
#define PACMAN_CORE_PMAN_H

#include "core/entity.h"

namespace pacman {
namespace core {

class Pacman : public Entity {
public:
  Pacman();

  int x() const override;
  int y() const override;
  int prev_x() const override;
  int prev_y() const override;
  Direction direction() const override;
  void setPosition(int x, int y) override;
  void setDirection(Direction direction) override;
  void savePreviousPosition() override;
  MapObjectType move(SMap &map) override;

  int lives;
  int points;
  int spawnX;
  int spawnY;

private:
  int xp_;
  int yp_;
  int prev_xp_;
  int prev_yp_;
  Direction direction_;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_PMAN_H
