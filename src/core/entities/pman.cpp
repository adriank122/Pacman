#include "core/entities/pman.h"

namespace pacman {
namespace core {

Pacman::Pacman()
    : lives(0), points(0), spawnX(0), spawnY(0), xp_(0), yp_(0), prev_xp_(0),
      prev_yp_(0), direction_(Direction::NONE) {}

int Pacman::x() const { return xp_; }
int Pacman::y() const { return yp_; }
int Pacman::prev_x() const { return prev_xp_; }
int Pacman::prev_y() const { return prev_yp_; }
Direction Pacman::direction() const { return direction_; }

void Pacman::setPosition(int x, int y) {
  xp_ = x;
  yp_ = y;
}

void Pacman::setDirection(Direction direction) { direction_ = direction; }

void Pacman::savePreviousPosition() {
  prev_xp_ = xp_;
  prev_yp_ = yp_;
}

TileType Pacman::move(Map &map) {
  savePreviousPosition();

  if (direction_ == Direction::NONE)
    return TileType::EMPTY;

  int newRow = xp_;
  int newCol = yp_;

  switch (direction_) {
  case Direction::LEFT:
    if (xp_ == 8 && yp_ == 0) {
      newCol = 19;
      break;
    }
    if (!map.isWall(xp_, yp_ - 1))
      newCol = yp_ - 1;
    break;

  case Direction::RIGHT:
    if (xp_ == 8 && yp_ == 19) {
      newCol = 0;
      break;
    }
    if (!map.isWall(xp_, yp_ + 1))
      newCol = yp_ + 1;
    break;

  case Direction::UP:
    if (!map.isWall(xp_ - 1, yp_))
      newRow = xp_ - 1;
    break;

  case Direction::DOWN:
    if (!map.isWall(xp_ + 1, yp_))
      newRow = xp_ + 1;
    break;

  default:
    break;
  }

  TileType consumed = map.consumePellet(newRow, newCol);
  xp_ = newRow;
  yp_ = newCol;
  return consumed;
}

} // namespace core
} // namespace pacman
