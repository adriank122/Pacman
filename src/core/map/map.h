#ifndef PACMAN_CORE_MAP_H
#define PACMAN_CORE_MAP_H

#include <string>
#include <vector>

namespace pacman {
namespace core {

enum class TileType { EMPTY, WALL, PELLET, POWER_UP };

class Map {
public:
  Map();
  Map(int width, int height);

  int width() const;
  int height() const;

  TileType getTile(int row, int col) const;
  void setTile(int row, int col, TileType type);

  bool isWall(int row, int col) const;
  bool hasPellet(int row, int col) const;
  TileType consumePellet(int row, int col);

  bool inBounds(int row, int col) const;

private:
  int width_;
  int height_;
  std::vector<TileType> tiles_;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_MAP_H
