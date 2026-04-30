#include "core/map/map.h"

namespace pacman {
namespace core {

Map::Map() : width_(0), height_(0) {}

Map::Map(int width, int height)
    : width_(width), height_(height), tiles_(width * height, TileType::EMPTY) {}

int Map::width() const { return width_; }
int Map::height() const { return height_; }

bool Map::inBounds(int row, int col) const {
  return row >= 0 && row < height_ && col >= 0 && col < width_;
}

TileType Map::getTile(int row, int col) const {
  return tiles_[row * width_ + col];
}

void Map::setTile(int row, int col, TileType type) {
  tiles_[row * width_ + col] = type;
}

bool Map::isWall(int row, int col) const {
  return getTile(row, col) == TileType::WALL;
}

bool Map::hasPellet(int row, int col) const {
  TileType t = getTile(row, col);
  return t == TileType::PELLET || t == TileType::POWER_UP;
}

TileType Map::consumePellet(int row, int col) {
  TileType t = getTile(row, col);
  if (t == TileType::PELLET || t == TileType::POWER_UP) {
    setTile(row, col, TileType::EMPTY);
    return t;
  }
  return TileType::EMPTY;
}

} // namespace core
} // namespace pacman
