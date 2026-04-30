#include "core/map/map_loader.h"
#include <fstream>
#include <gtest/gtest.h>

using namespace pacman::core;

static const char *kTmpPath = "/tmp/pacman_test.map";

static void writeTmpMap(const char *content) {
  std::ofstream f(kTmpPath);
  f << content;
}

TEST(MapLoader, LoadsDimensions) {
  writeTmpMap("###\n#.#\n###\n");
  Map m = MapLoader::load(kTmpPath);
  EXPECT_EQ(m.width(), 3);
  EXPECT_EQ(m.height(), 3);
}

TEST(MapLoader, LoadsTileTypes) {
  writeTmpMap("###\n#.#\n###\n");
  Map m = MapLoader::load(kTmpPath);
  EXPECT_EQ(m.getTile(0, 0), TileType::WALL);
  EXPECT_EQ(m.getTile(1, 1), TileType::PELLET);
}

TEST(MapLoader, LoadsPowerUp) {
  writeTmpMap("#o#\n");
  Map m = MapLoader::load(kTmpPath);
  EXPECT_EQ(m.getTile(0, 1), TileType::POWER_UP);
}

TEST(MapLoader, LoadsEmptyTile) {
  writeTmpMap("# #\n");
  Map m = MapLoader::load(kTmpPath);
  EXPECT_EQ(m.getTile(0, 1), TileType::EMPTY);
}

TEST(MapLoader, ThrowsOnMissingFile) {
  EXPECT_THROW(MapLoader::load("/tmp/nonexistent_pacman_map.map"),
               std::runtime_error);
}

TEST(MapLoader, ThrowsOnJaggedRows) {
  writeTmpMap("###\n##\n###\n");
  EXPECT_THROW(MapLoader::load(kTmpPath), std::runtime_error);
}

TEST(MapLoader, SkipsBlankLines) {
  writeTmpMap("###\n\n#.#\n\n###\n");
  Map m = MapLoader::load(kTmpPath);
  EXPECT_EQ(m.height(), 3);
}
