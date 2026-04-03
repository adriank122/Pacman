#include "core/ghost.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

namespace pacman {
namespace core {

void init_ghost(SGhost &ghost, int x, int y) {
  ghost.last_move = 'L';
  ghost.ifcookie = 1;
  ghost.if_boost = 0;
  ghost.xg = x;
  ghost.yg = y;
  ghost.lp = 1;
}

void ghost_move(SGhost &ghost, SMap &map) {
  int x = ghost.xg, y = ghost.yg;

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

  if (possible == 1 || possible == 2) {
    if (ghost.last_move == 'L') {
      if (left) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y--;
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y--;
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y--;
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (down) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x++;
          ghost.last_move = 'R';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x++;
          ghost.last_move = 'R';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x++;
          ghost.last_move = 'R';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (up) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x--;
          ghost.last_move = 'U';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x--;
          ghost.last_move = 'U';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x--;
          ghost.last_move = 'U';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (right) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y++;
          ghost.last_move = 'D';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y++;
          ghost.last_move = 'D';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y++;
          ghost.last_move = 'D';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      }
    } else if (ghost.last_move == 'R') {
      if (right) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y++;
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y++;
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y++;
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (down) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x++;
          ghost.last_move = 'R';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x++;
          ghost.last_move = 'R';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x++;
          ghost.last_move = 'R';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (up) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x--;
          ghost.last_move = 'U';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x--;
          ghost.last_move = 'U';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x--;
          ghost.last_move = 'U';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (left) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y--;
          ghost.last_move = 'D';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y--;
          ghost.last_move = 'D';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y--;
          ghost.last_move = 'D';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      }
    } else if (ghost.last_move == 'U') {
      if (up) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x--;
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x--;
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x--;
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (right) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y++;
          ghost.last_move = 'R';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y++;
          ghost.last_move = 'R';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y++;
          ghost.last_move = 'R';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (left) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y--;
          ghost.last_move = 'L';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y--;
          ghost.last_move = 'L';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y--;
          ghost.last_move = 'L';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (down) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x++;
          ghost.last_move = 'D';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x++;
          ghost.last_move = 'D';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x++;
          ghost.last_move = 'D';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      }
    } else if (ghost.last_move == 'D') {
      if (down) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x++;
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x++;
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x++;
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (right) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y++;
          ghost.last_move = 'R';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y++;
          ghost.last_move = 'R';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y++;
          ghost.last_move = 'R';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (up) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x--;
          ghost.last_move = 'U';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x--;
          ghost.last_move = 'U';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x--;
          ghost.last_move = 'U';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (left) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y--;
          ghost.last_move = 'L';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y--;
          ghost.last_move = 'L';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y--;
          ghost.last_move = 'L';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      }
    }
  }
  if (possible > 2) {
    srand(time(0));
    int los = 1 + rand() % 4;

    if (los == 1) {
      if (up) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          ghost.last_move = 'U';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          ghost.last_move = 'U';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          ghost.last_move = 'U';
        }
        if (map.map[x - 1][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x - 1][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
        x--;
      } else if (down) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          ghost.last_move = 'D';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;

          ghost.last_move = 'D';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          ghost.last_move = 'D';
        }
        if (map.map[x + 1][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x + 1][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (left) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y--;
          ghost.last_move = 'L';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y--;
          ghost.last_move = 'L';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y--;
          ghost.last_move = 'L';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (right) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y++;
          ghost.last_move = 'R';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y++;
          ghost.last_move = 'R';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y++;
          ghost.last_move = 'R';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      }
    }
    if (los == 2) {
      if (down) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x++;
          ghost.last_move = 'D';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x++;
          ghost.last_move = 'D';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x++;
          ghost.last_move = 'D';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (left) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y--;
          ghost.last_move = 'L';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y--;
          ghost.last_move = 'L';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y--;
          ghost.last_move = 'L';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (right) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y++;
          ghost.last_move = 'R';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y++;
          ghost.last_move = 'R';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y++;
          ghost.last_move = 'R';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (up) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x--;
          ghost.last_move = 'U';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x--;
          ghost.last_move = 'U';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x--;
          ghost.last_move = 'U';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      }
    }
    if (los == 3) {
      if (left) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y--;
          ghost.last_move = 'L';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y--;
          ghost.last_move = 'L';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y--;
          ghost.last_move = 'L';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (right) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y++;
          ghost.last_move = 'R';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y++;
          ghost.last_move = 'R';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y++;
          ghost.last_move = 'R';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (up) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x--;
          ghost.last_move = 'U';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x--;
          ghost.last_move = 'U';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x--;
          ghost.last_move = 'U';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (down) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x++;
          ghost.last_move = 'D';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x++;
          ghost.last_move = 'D';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x++;
          ghost.last_move = 'D';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      }
    }
    if (los == 4) {
      if (right) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y++;
          ghost.last_move = 'R';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y++;
          ghost.last_move = 'R';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y++;
          ghost.last_move = 'R';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (up) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x--;
          ghost.last_move = 'U';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x--;
          ghost.last_move = 'U';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x--;
          ghost.last_move = 'U';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (down) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          x++;
          ghost.last_move = 'D';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          x++;
          ghost.last_move = 'D';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          x++;
          ghost.last_move = 'D';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      } else if (left) {
        if (ghost.ifcookie != 0) {
          map.map[x][y] = PELLET;
          y--;
          ghost.last_move = 'L';
        }
        if (ghost.if_boost != 0) {
          map.map[x][y] = POWER_UP;
          y--;
          ghost.last_move = 'L';
        }
        if (ghost.ifcookie == 0 && ghost.if_boost == 0) {
          map.map[x][y] = EMPTY;
          y--;
          ghost.last_move = 'L';
        }
        if (map.map[x][y] == PELLET)
          ghost.ifcookie = 1;
        else
          ghost.ifcookie = 0;
        if (map.map[x][y] == POWER_UP)
          ghost.if_boost = 1;
        else
          ghost.if_boost = 0;
      }
    }
  }

  ghost.xg = x;
  ghost.yg = y;

  map.map[ghost.xg][ghost.yg] = GHOST;

  if (1) {
    if (ghost.lp % 2 != 0) {
      map.xg1 = ghost.xg;
      map.yg1 = ghost.yg;
    }
    if (ghost.lp % 2 == 0) {
      map.xg2 = ghost.xg;
      map.yg2 = ghost.yg;
    }
    ghost.lp++;
  }
}

void ghost_boost() {}

} // namespace core
} // namespace pacman
