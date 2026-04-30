#include "core/map/map_loader.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace pacman {
namespace core {

static TileType charToTileType(char c) {
  switch (c) {
  case '#':
    return TileType::WALL;
  case '.':
    return TileType::PELLET;
  case 'o':
    return TileType::POWER_UP;
  default:
    return TileType::EMPTY;
  }
}

Map MapLoader::load(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open())
    throw std::runtime_error("MapLoader: cannot open file: " + path);

  std::vector<std::string> rows;
  std::string line;
  while (std::getline(file, line)) {
    if (!line.empty())
      rows.push_back(line);
  }

  if (rows.empty())
    throw std::runtime_error("MapLoader: empty map file: " + path);

  int width = static_cast<int>(rows[0].size());
  for (const auto &row : rows) {
    if (static_cast<int>(row.size()) != width)
      throw std::runtime_error("MapLoader: jagged row in file: " + path);
  }

  int height = static_cast<int>(rows.size());
  Map map(width, height);

  for (int r = 0; r < height; r++)
    for (int c = 0; c < width; c++)
      map.setTile(r, c, charToTileType(rows[r][c]));

  return map;
}

} // namespace core
} // namespace pacman
