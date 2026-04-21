#include "core/pman.h"
#include <iostream>

using namespace std;

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

MapObjectType Pacman::move(SMap &map) {
  savePreviousPosition();

  if (direction_ == Direction::NONE) {
    return EMPTY;
  }

  int xp = xp_;
  int yp = yp_;
  MapObjectType consumed = EMPTY;

  switch (direction_) {
  case Direction::LEFT:
    if (xp == 8 && yp == 0) {
      consumed = map.map[8][19];
      map.map[xp][yp] = EMPTY;
      yp = 19;
      break;
    }
    if (map.map[xp][yp - 1] != WALL) {
      consumed = map.map[xp][yp - 1];
      map.map[xp][yp] = EMPTY;
      yp--;
    }
    break;

  case Direction::UP:
    if (map.map[xp - 1][yp] != WALL) {
      consumed = map.map[xp - 1][yp];
      map.map[xp][yp] = EMPTY;
      xp--;
    }
    break;

  case Direction::DOWN:
    if (map.map[xp + 1][yp] != WALL) {
      consumed = map.map[xp + 1][yp];
      map.map[xp][yp] = EMPTY;
      xp++;
    }
    break;

  case Direction::RIGHT:
    if (xp == 8 && yp == 19) {
      consumed = map.map[8][0];
      map.map[xp][yp] = EMPTY;
      yp = 0;
      break;
    }
    if (map.map[xp][yp + 1] != WALL) {
      consumed = map.map[xp][yp + 1];
      map.map[xp][yp] = EMPTY;
      yp++;
    }
    break;

  default:
    break;
  }

  map.map[xp][yp] = PACMAN_PLAYER;
  xp_ = xp;
  yp_ = yp;
  return consumed;
}

} // namespace core
} // namespace pacman
