#include "core/pman.h"
#include <iostream>

using namespace std;

namespace pacman {
namespace core {

void init_pman(SPman &pman) {
  pman.lives = 3;
  pman.points = 0;
}

void pman_move(SPman &pman, SMap &map, char input) {
  if (map.map[map.xp][map.yp] == GHOST) {
    pman.lives--;
    map.map[map.xp][map.yp] = GHOST;
    map.xp = 13;
    map.yp = 9;
  }

  if (input == '\0') {
    return;
  }

  int points = pman.points;
  int xp = map.xp, yp = map.yp;

  switch (input) {

  case 'a':

    if (xp == 8 && yp == 0) {
      map.map[xp][yp] = EMPTY;
      if (map.map[8][19] == PELLET)
        points++;
      yp = 19;
      break;
    }

    if (map.map[xp][yp - 1] != WALL) {
      if (map.map[xp][yp - 1] == PELLET) {
        points++;
      }
      if (map.map[xp][yp - 1] == POWER_UP) {
        points += 5;
      }
      if (map.map[xp][yp - 1] == GHOST) {
        pman.lives--;
        map.map[xp][yp] = EMPTY;
        xp = 13;
        yp = 9;
      }
      map.map[xp][yp] = EMPTY;
      yp--;
      break;
    } else
      break;

  case 'w':
    if (map.map[xp - 1][yp] != WALL) {
      if (map.map[xp - 1][yp] == PELLET) {
        points++;
      }
      if (map.map[xp - 1][yp] == POWER_UP) {
        points += 5;
      }
      if (map.map[xp - 1][yp] == GHOST) {
        pman.lives--;
        map.map[xp][yp] = EMPTY;
        xp = 13;
        yp = 9;
      }
      map.map[xp][yp] = EMPTY;
      xp--;
      break;
    } else
      break;

  case 's':
    if (map.map[xp + 1][yp] != WALL) {
      if (map.map[xp + 1][yp] == PELLET) {
        points++;
      }
      if (map.map[xp + 1][yp] == POWER_UP) {
        points += 5;
      }
      if (map.map[xp + 1][yp] == GHOST) {
        pman.lives--;
        map.map[xp][yp] = EMPTY;
        xp = 13;
        yp = 9;
      }
      map.map[xp][yp] = EMPTY;
      xp++;
      break;
    } else
      break;

  case 'd':
    if (xp == 8 && yp == 19) {
      map.map[xp][yp] = EMPTY;
      if (map.map[8][0] == PELLET)
        points++;
      yp = 0;
      break;
    }
    if (map.map[xp][yp + 1] != WALL) {
      if (map.map[xp][yp + 1] == PELLET) {
        points++;
      }
      if (map.map[xp][yp + 1] == POWER_UP) {
        points += 5;
      }
      if (map.map[xp][yp + 1] == GHOST) {
        pman.lives--;
        map.map[xp][yp] = EMPTY;
        xp = 13;
        yp = 9;
      }
      map.map[xp][yp] = EMPTY;
      yp++;
      break;
    } else
      break;
  default:
    break;
  }

  if (map.map[map.xp][map.yp] == GHOST) {
    pman.lives--;
    map.map[xp][yp] = GHOST;
    xp = 13;
    yp = 9;
  }

  map.map[xp][yp] = PACMAN_PLAYER;
  map.xp = xp;
  map.yp = yp;
  pman.points = points;
}

void pman_boost() {}

} // namespace core
} // namespace pacman
