#include "core/entities/pman.h"
#include "core/map/map.h"
#include <gtest/gtest.h>

using namespace pacman::core;

static Map makeOpenMap() { return Map(20, 17); }

TEST(PacmanDefaults, InitialPosition) {
  Pacman p;
  EXPECT_EQ(p.x(), 0);
  EXPECT_EQ(p.y(), 0);
}

TEST(PacmanDefaults, InitialDirection) {
  Pacman p;
  EXPECT_EQ(p.direction(), Direction::NONE);
}

TEST(PacmanSetters, SetPosition) {
  Pacman p;
  p.setPosition(3, 5);
  EXPECT_EQ(p.x(), 3);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanSetters, SetDirection) {
  Pacman p;
  p.setDirection(Direction::UP);
  EXPECT_EQ(p.direction(), Direction::UP);
}

TEST(PacmanSetters, SavePreviousPosition) {
  Pacman p;
  p.setPosition(3, 5);
  p.savePreviousPosition();
  p.setPosition(7, 9);
  EXPECT_EQ(p.prev_x(), 3);
  EXPECT_EQ(p.prev_y(), 5);
}

TEST(PacmanMove, DirectionNoneDoesNotMove) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::NONE);
  Map m = makeOpenMap();
  TileType result = p.move(m);
  EXPECT_EQ(result, TileType::EMPTY);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveUpIntoEmptyTile) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::UP);
  Map m = makeOpenMap();
  TileType result = p.move(m);
  EXPECT_EQ(result, TileType::EMPTY);
  EXPECT_EQ(p.x(), 4);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveUpBlockedByWall) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::UP);
  Map m = makeOpenMap();
  m.setTile(4, 5, TileType::WALL);
  p.move(m);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveDownIntoEmptyTile) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::DOWN);
  Map m = makeOpenMap();
  TileType result = p.move(m);
  EXPECT_EQ(result, TileType::EMPTY);
  EXPECT_EQ(p.x(), 6);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveDownBlockedByWall) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::DOWN);
  Map m = makeOpenMap();
  m.setTile(6, 5, TileType::WALL);
  p.move(m);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveLeftIntoEmptyTile) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::LEFT);
  Map m = makeOpenMap();
  TileType result = p.move(m);
  EXPECT_EQ(result, TileType::EMPTY);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 4);
}

TEST(PacmanMove, MoveLeftBlockedByWall) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::LEFT);
  Map m = makeOpenMap();
  m.setTile(5, 4, TileType::WALL);
  p.move(m);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveRightIntoEmptyTile) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::RIGHT);
  Map m = makeOpenMap();
  TileType result = p.move(m);
  EXPECT_EQ(result, TileType::EMPTY);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 6);
}

TEST(PacmanMove, MoveRightBlockedByWall) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::RIGHT);
  Map m = makeOpenMap();
  m.setTile(5, 6, TileType::WALL);
  p.move(m);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveConsumePellet) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::RIGHT);
  Map m = makeOpenMap();
  m.setTile(5, 6, TileType::PELLET);
  TileType result = p.move(m);
  EXPECT_EQ(result, TileType::PELLET);
}

TEST(PacmanMove, MoveConsumePowerUp) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::RIGHT);
  Map m = makeOpenMap();
  m.setTile(5, 6, TileType::POWER_UP);
  TileType result = p.move(m);
  EXPECT_EQ(result, TileType::POWER_UP);
}

TEST(PacmanMove, MoveSavesPreviousPosition) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::RIGHT);
  Map m = makeOpenMap();
  p.move(m);
  EXPECT_EQ(p.prev_x(), 5);
  EXPECT_EQ(p.prev_y(), 5);
}

TEST(PacmanMove, ConsumePelletClearsTile) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::RIGHT);
  Map m = makeOpenMap();
  m.setTile(5, 6, TileType::PELLET);
  p.move(m);
  EXPECT_EQ(m.getTile(5, 6), TileType::EMPTY);
}

TEST(PacmanMove, TunnelWrapLeftEntry) {
  Pacman p;
  p.setPosition(8, 0);
  p.setDirection(Direction::LEFT);
  Map m = makeOpenMap();
  p.move(m);
  EXPECT_EQ(p.x(), 8);
  EXPECT_EQ(p.y(), 19);
}

TEST(PacmanMove, TunnelWrapRightEntry) {
  Pacman p;
  p.setPosition(8, 19);
  p.setDirection(Direction::RIGHT);
  Map m = makeOpenMap();
  p.move(m);
  EXPECT_EQ(p.x(), 8);
  EXPECT_EQ(p.y(), 0);
}
