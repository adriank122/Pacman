#include "core/pman.h"
#include <iostream>

using namespace std;

namespace pacman {
namespace core {

Pacman::Pacman()
    : lives(3), points(0), xp_(13), yp_(9), prev_xp_(13), prev_yp_(9),
      direction_('\0') {}

int Pacman::x() const { return xp_; }
int Pacman::y() const { return yp_; }
int Pacman::prev_x() const { return prev_xp_; }
int Pacman::prev_y() const { return prev_yp_; }
char Pacman::direction() const { return direction_; }

void Pacman::setPosition(int x, int y) {
  xp_ = x;
  yp_ = y;
}

void Pacman::setDirection(char direction) { direction_ = direction; }

void Pacman::savePreviousPosition() {
  prev_xp_ = xp_;
  prev_yp_ = yp_;
}

void Pacman::move(SMap &map) {
  savePreviousPosition();

  if (map.map[xp_][yp_] == GHOST) {
    lives--;
    map.map[xp_][yp_] = GHOST;
    map.xp = 13;
    map.yp = 9;
    xp_ = map.xp;
    yp_ = map.yp;
  }

  if (direction_ == '\0') {
    return;
  }

  int currentPoints = points;
  int xp = xp_;
  int yp = yp_;

  switch (direction_) {
  case 'a':
    if (xp == 8 && yp == 0) {
      map.map[xp][yp] = EMPTY;
      if (map.map[8][19] == PELLET)
        currentPoints++;
      yp = 19;
      break;
    }
    if (map.map[xp][yp - 1] != WALL) {
      if (map.map[xp][yp - 1] == PELLET) {
        currentPoints++;
      }
      if (map.map[xp][yp - 1] == POWER_UP) {
        currentPoints += 5;
      }
      if (map.map[xp][yp - 1] == GHOST) {
        lives--;
        map.map[xp][yp] = EMPTY;
        xp = 13;
        yp = 9;
      }
      map.map[xp][yp] = EMPTY;
      yp--;
    }
    break;

  case 'w':
    if (map.map[xp - 1][yp] != WALL) {
      if (map.map[xp - 1][yp] == PELLET) {
        currentPoints++;
      }
      if (map.map[xp - 1][yp] == POWER_UP) {
        currentPoints += 5;
      }
      if (map.map[xp - 1][yp] == GHOST) {
        lives--;
        map.map[xp][yp] = EMPTY;
        xp = 13;
        yp = 9;
      }
      map.map[xp][yp] = EMPTY;
      xp--;
    }
    break;

  case 's':
    if (map.map[xp + 1][yp] != WALL) {
      if (map.map[xp + 1][yp] == PELLET) {
        currentPoints++;
      }
      if (map.map[xp + 1][yp] == POWER_UP) {
        currentPoints += 5;
      }
      if (map.map[xp + 1][yp] == GHOST) {
        lives--;
        map.map[xp][yp] = EMPTY;
        xp = 13;
        yp = 9;
      }
      map.map[xp][yp] = EMPTY;
      xp++;
    }
    break;

  case 'd':
    if (xp == 8 && yp == 19) {
      map.map[xp][yp] = EMPTY;
      if (map.map[8][0] == PELLET)
        currentPoints++;
      yp = 0;
      break;
    }
    if (map.map[xp][yp + 1] != WALL) {
      if (map.map[xp][yp + 1] == PELLET) {
        currentPoints++;
      }
      if (map.map[xp][yp + 1] == POWER_UP) {
        currentPoints += 5;
      }
      if (map.map[xp][yp + 1] == GHOST) {
        lives--;
        map.map[xp][yp] = EMPTY;
        xp = 13;
        yp = 9;
      }
      map.map[xp][yp] = EMPTY;
      yp++;
    }
    break;

  default:
    break;
  }

  if (map.map[xp][yp] == GHOST) {
    lives--;
    map.map[xp][yp] = GHOST;
    xp = 13;
    yp = 9;
  }

  map.map[xp][yp] = PACMAN_PLAYER;
  map.xp = xp;
  map.yp = yp;
  xp_ = xp;
  yp_ = yp;
  points = currentPoints;
}

} // namespace core
} // namespace pacman
