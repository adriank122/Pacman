#include "core/map.h"
#include "core/config.h"
#include <iomanip>
#include <iostream>

using namespace std;

namespace pacman {
namespace core {

void init_map(SMap &map, const GameConfig &config) {
  map.width = config.mapWidth;
  map.height = config.mapHeight;
  map.powerUpScore = config.powerUpScore;
}

void map_create1(SMap &map) {
  for (int i = 0; i < map.height; i++) {
    for (int j = 0; j < map.width; j++) {
      map.map[i][j] = WALL;
    }
  }

  for (int i = 1; i < map.width - 1; i++) {
    map.map[1][i] = PELLET;
    map.map[3][i] = PELLET;
    map.map[6][i] = PELLET;
    map.map[8][i] = PELLET;
    map.map[10][i] = PELLET;
    map.map[13][i] = PELLET;
    map.map[15][i] = PELLET;
  }

  for (int i = 1; i < map.height - 1; i++) {
    map.map[i][1] = PELLET;
    map.map[i][3] = PELLET;
    map.map[i][5] = PELLET;
    map.map[i][7] = PELLET;
    map.map[i][12] = PELLET;
    map.map[i][14] = PELLET;
    map.map[i][16] = PELLET;
    map.map[i][18] = PELLET;
  }

  map.map[2][5] = WALL;
  map.map[2][7] = WALL;
  map.map[2][12] = WALL;
  map.map[2][14] = WALL;

  map.map[3][2] = WALL;
  map.map[3][4] = WALL;
  map.map[3][15] = WALL;
  map.map[3][17] = WALL;

  map.map[6][2] = WALL;
  map.map[6][4] = WALL;
  map.map[6][6] = WALL;
  map.map[6][13] = WALL;
  map.map[6][15] = WALL;
  map.map[6][17] = WALL;

  map.map[8][4] = WALL;
  map.map[8][6] = WALL;
  map.map[8][13] = WALL;
  map.map[8][15] = WALL;

  map.map[10][2] = WALL;
  map.map[10][6] = WALL;
  map.map[10][13] = WALL;
  map.map[10][17] = WALL;

  map.map[13][2] = WALL;
  map.map[13][4] = WALL;
  map.map[13][15] = WALL;
  map.map[13][17] = WALL;

  map.map[14][5] = WALL;
  map.map[14][7] = WALL;
  map.map[14][12] = WALL;
  map.map[14][14] = WALL;

}

void map_create2(SMap &map) {
  for (int i = 0; i < map.height; i++) {
    for (int j = 0; j < map.width; j++) {
      map.map[i][j] = WALL;
    }
  }

  for (int j = 1; j < map.width - 1; j++) {
    map.map[1][j] = PELLET;
    map.map[4][j] = PELLET;
    map.map[6][j] = PELLET;
    map.map[10][j] = PELLET;
    map.map[15][j] = PELLET;
  }

  map.map[2][1] = PELLET;
  map.map[3][1] = PELLET;
  map.map[5][1] = PELLET;
  map.map[8][1] = PELLET;
  map.map[11][1] = PELLET;
  map.map[13][1] = PELLET;
  map.map[14][1] = PELLET;

  map.map[2][18] = PELLET;
  map.map[3][18] = PELLET;
  map.map[5][18] = PELLET;
  map.map[8][18] = PELLET;
  map.map[11][18] = PELLET;
  map.map[13][18] = PELLET;
  map.map[14][18] = PELLET;

  map.map[8][3] = PELLET;

  map.map[8][16] = PELLET;

  map.map[7][4] = PELLET;
  map.map[8][4] = PELLET;
  map.map[9][4] = PELLET;

  map.map[7][8] = PELLET;
  map.map[8][8] = PELLET;
  map.map[9][8] = PELLET;

  map.map[7][11] = PELLET;
  map.map[8][11] = PELLET;
  map.map[9][11] = PELLET;

  map.map[7][15] = PELLET;
  map.map[8][15] = PELLET;
  map.map[9][15] = PELLET;

  map.map[2][7] = PELLET;
  map.map[3][7] = PELLET;
  map.map[13][7] = PELLET;
  map.map[14][7] = PELLET;

  map.map[2][12] = PELLET;
  map.map[3][12] = PELLET;
  map.map[13][12] = PELLET;
  map.map[14][12] = PELLET;

  map.map[8][0] = PELLET;
  map.map[8][2] = PELLET;
  map.map[8][17] = PELLET;
  map.map[8][19] = PELLET;

  map.map[12][1] = PELLET;
  map.map[12][2] = PELLET;
  map.map[12][3] = PELLET;
  map.map[12][4] = PELLET;
  map.map[12][5] = PELLET;
  map.map[12][6] = PELLET;
  map.map[12][7] = PELLET;
  map.map[12][12] = PELLET;
  map.map[12][13] = PELLET;
  map.map[12][14] = PELLET;
  map.map[12][15] = PELLET;
  map.map[12][16] = PELLET;
  map.map[12][17] = PELLET;
  map.map[12][18] = PELLET;

  map.map[13][8] = PELLET;
  map.map[13][9] = PELLET;
  map.map[13][10] = PELLET;
  map.map[13][11] = PELLET;
}

void map_create3(SMap &map) {
  for (int i = 0; i < map.height; i++)
    for (int j = 0; j < map.width; j++)
      map.map[i][j] = WALL;

  for (int j = 1; j < 19; j++) {
    map.map[1][j] = PELLET;
    map.map[3][j] = PELLET;
    map.map[13][j] = PELLET;
    map.map[15][j] = PELLET;
  }

  for (int i = 1; i < 7; i++) {
    map.map[i][1] = PELLET;
    map.map[i][map.width - 2] = PELLET;
  }

  for (int i = 10; i < map.height - 1; i++) {
    map.map[i][1] = PELLET;
    map.map[i][map.width - 2] = PELLET;
  }

  for (int j = 3; j < 17; j++) {
    map.map[5][j] = PELLET;
    map.map[11][j] = PELLET;
  }

  for (int i = 1; i < 7; i++) {
    map.map[i][1] = PELLET;
    map.map[i][18] = PELLET;
  }

  for (int j = 7; j < 13; j++) {
    map.map[6][j] = PELLET;
    map.map[10][j] = PELLET;
  }

  for (int i = 5; i < 14; i++) {
    map.map[i][3] = PELLET;
    map.map[i][16] = PELLET;
  }

  for (int j = 0; j < 6; j++)
    map.map[8][j] = PELLET;

  for (int j = map.width - 6; j < map.width; j++)
    map.map[8][j] = PELLET;

  for (int j = 5; j < 8; j++) {
    map.map[7][j] = PELLET;
    map.map[9][j] = PELLET;
  }

  for (int j = 12; j < 15; j++) {
    map.map[7][j] = PELLET;
    map.map[9][j] = PELLET;
  }

  for (int j = 7; j < 13; j++)
    map.map[8][j] = PELLET;

  map.map[6][2] = PELLET;
  map.map[10][2] = PELLET;

  map.map[2][5] = PELLET;
  map.map[14][5] = PELLET;

  map.map[4][7] = PELLET;
  map.map[12][7] = PELLET;

  map.map[4][12] = PELLET;
  map.map[12][12] = PELLET;

  map.map[2][14] = PELLET;
  map.map[14][14] = PELLET;

  map.map[6][17] = PELLET;
  map.map[10][17] = PELLET;

  map.map[1][1] = POWER_UP;
  map.map[15][1] = POWER_UP;
  map.map[1][18] = POWER_UP;
  map.map[15][18] = POWER_UP;

}

void map_show(SMap map) {
  cout << "\n";
  for (int i = 0; i < map.height; i++) {
    cout << "\n\t";
    for (int j = 0; j < map.width; j++)
      cout << setw(2) << map.map[i][j];
  }
  cout << "\n";
}

} // namespace core
} // namespace pacman
