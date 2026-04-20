#include "core/ghost.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

namespace pacman {
namespace core {

Ghost::Ghost()
    : ifcookie(1), last_move(Direction::LEFT), if_boost(0), xg(0), yg(0),
      prev_xg(0), prev_yg(0), lp(1) {}

int Ghost::x() const { return xg; }
int Ghost::y() const { return yg; }
int Ghost::prev_x() const { return prev_xg; }
int Ghost::prev_y() const { return prev_yg; }
Direction Ghost::direction() const { return last_move; }

void Ghost::setPosition(int x, int y) {
  xg = x;
  yg = y;
  prev_xg = x;
  prev_yg = y;
}

void Ghost::setDirection(Direction direction) { last_move = direction; }

void Ghost::savePreviousPosition() {
  prev_xg = xg;
  prev_yg = yg;
}

void Ghost::move(SMap &map) {
  savePreviousPosition();
  int x = xg, y = yg;

  int possible = 0;
  int up = 0, down = 0, left = 0, right = 0;

  if (map.map[x - 1][y] != WALL && map.map[x - 1][y] != GHOST) {
    possible++;
    up = 1;
  }
  if (map.map[x + 1][y] != WALL && map.map[x + 1][y] != GHOST) {
    possible++;
    down = 1;
  }
  if (map.map[x][y - 1] != WALL && map.map[x][y - 1] != GHOST) {
    possible++;
    left = 1;
  }
  if (map.map[x][y + 1] != WALL && map.map[x][y + 1] != GHOST) {
    possible++;
    right = 1;
  }

  if (possible > 0) {
    if (last_move == Direction::LEFT) {
      if (left) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          y--;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y--;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          y--;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      } else if (down) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          x++;
          last_move = Direction::RIGHT;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x++;
          last_move = Direction::RIGHT;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          x++;
          last_move = Direction::RIGHT;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      } else if (up) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          x--;
          last_move = Direction::UP;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x--;
          last_move = Direction::UP;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          x--;
          last_move = Direction::UP;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      } else if (right) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          y++;
          last_move = Direction::DOWN;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y++;
          last_move = Direction::DOWN;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          y++;
          last_move = Direction::DOWN;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      }
    } else if (last_move == Direction::RIGHT) {
      if (right) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          y++;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y++;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          y++;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      } else if (down) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          x++;
          last_move = Direction::RIGHT;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x++;
          last_move = Direction::RIGHT;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          x++;
          last_move = Direction::RIGHT;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      } else if (up) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          x--;
          last_move = Direction::UP;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x--;
          last_move = Direction::UP;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          x--;
          last_move = Direction::UP;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      } else if (left) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          y--;
          last_move = Direction::DOWN;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y--;
          last_move = Direction::DOWN;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          y--;
          last_move = Direction::DOWN;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      }
    } else if (last_move == Direction::UP) {
      if (up) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          x--;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x--;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          x--;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      } else if (right) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          y++;
          last_move = Direction::RIGHT;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y++;
          last_move = Direction::RIGHT;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          y++;
          last_move = Direction::RIGHT;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      } else if (left) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          y--;
          last_move = Direction::LEFT;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y--;
          last_move = Direction::LEFT;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          y--;
          last_move = Direction::LEFT;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      } else if (down) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          x++;
          last_move = Direction::DOWN;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x++;
          last_move = Direction::DOWN;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          x++;
          last_move = Direction::DOWN;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      }
    } else if (last_move == Direction::DOWN) {
      if (down) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          x++;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x++;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          x++;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      } else if (left) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          y--;
          last_move = Direction::LEFT;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y--;
          last_move = Direction::LEFT;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          y--;
          last_move = Direction::LEFT;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      } else if (right) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          y++;
          last_move = Direction::RIGHT;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y++;
          last_move = Direction::RIGHT;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          y++;
          last_move = Direction::RIGHT;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      } else if (up) {
        if (ifcookie != 0) {
          map.map[x][y] = PELLET;
          x--;
          last_move = Direction::UP;
        }
        if (if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x--;
          last_move = Direction::UP;
        }
        if (ifcookie == 0 && if_boost == 0) {
          map.map[x][y] = EMPTY;
          x--;
          last_move = Direction::UP;
        }
        if (map.map[x][y] == PELLET)
          ifcookie = 1;
        else
          ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          if_boost = 1;
        else
          if_boost = 0;
      }
    }
  }

  xg = x;
  yg = y;

  map.map[xg][yg] = GHOST;

  if (1) {
    if (lp % 2 != 0) {
      map.xg1 = xg;
      map.yg1 = yg;
    }
    if (lp % 2 == 0) {
      map.xg2 = xg;
      map.yg2 = yg;
    }
    lp++;
  }
}

} // namespace core
} // namespace pacman
