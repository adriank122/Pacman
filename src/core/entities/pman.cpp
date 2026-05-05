#include "core/entities/pman.h"

namespace pacman {
namespace core {

TileType Pacman::move(Map &map) {
  savePreviousPosition();

  if (direction_ == Direction::NONE)
    return TileType::EMPTY;

  int newRow = x_;
  int newCol = y_;

  switch (direction_) {
  case Direction::LEFT:
    if (x_ == 8 && y_ == 0) {
      newCol = 19;
      break;
    }
    if (!map.isWall(x_, y_ - 1))
      newCol = y_ - 1;
    break;

  case Direction::RIGHT:
    if (x_ == 8 && y_ == 19) {
      newCol = 0;
      break;
    }
    if (!map.isWall(x_, y_ + 1))
      newCol = y_ + 1;
    break;

  case Direction::UP:
    if (!map.isWall(x_ - 1, y_))
      newRow = x_ - 1;
    break;

  case Direction::DOWN:
    if (!map.isWall(x_ + 1, y_))
      newRow = x_ + 1;
    break;

  default:
    break;
  }

  TileType consumed = map.consumePellet(newRow, newCol);
  x_ = newRow;
  y_ = newCol;
  return consumed;
}

} // namespace core
} // namespace pacman
