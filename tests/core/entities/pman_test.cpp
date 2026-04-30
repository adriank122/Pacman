#include "core/entities/pman.h"
#include "core/map/map.h"
#include <gtest/gtest.h>

using namespace pacman::core;

static SMap makeOpenMap() {
  SMap m{};
  return m;
}

TEST(PacmanDefaults, InitialLivesAndPoints) {
  Pacman p;
  EXPECT_EQ(p.lives, 0);
  EXPECT_EQ(p.points, 0);
}

TEST(PacmanDefaults, InitialSpawnCoords) {
  Pacman p;
  EXPECT_EQ(p.spawnX, 0);
  EXPECT_EQ(p.spawnY, 0);
}

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
  SMap m = makeOpenMap();
  MapObjectType result = p.move(m);
  EXPECT_EQ(result, EMPTY);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveUpIntoEmptyTile) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::UP);
  SMap m = makeOpenMap();
  MapObjectType result = p.move(m);
  EXPECT_EQ(result, EMPTY);
  EXPECT_EQ(p.x(), 4);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveUpBlockedByWall) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::UP);
  SMap m = makeOpenMap();
  m.map[4][5] = WALL;
  p.move(m);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveDownIntoEmptyTile) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::DOWN);
  SMap m = makeOpenMap();
  MapObjectType result = p.move(m);
  EXPECT_EQ(result, EMPTY);
  EXPECT_EQ(p.x(), 6);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveDownBlockedByWall) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::DOWN);
  SMap m = makeOpenMap();
  m.map[6][5] = WALL;
  p.move(m);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveLeftIntoEmptyTile) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::LEFT);
  SMap m = makeOpenMap();
  MapObjectType result = p.move(m);
  EXPECT_EQ(result, EMPTY);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 4);
}

TEST(PacmanMove, MoveLeftBlockedByWall) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::LEFT);
  SMap m = makeOpenMap();
  m.map[5][4] = WALL;
  p.move(m);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveRightIntoEmptyTile) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::RIGHT);
  SMap m = makeOpenMap();
  MapObjectType result = p.move(m);
  EXPECT_EQ(result, EMPTY);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 6);
}

TEST(PacmanMove, MoveRightBlockedByWall) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::RIGHT);
  SMap m = makeOpenMap();
  m.map[5][6] = WALL;
  p.move(m);
  EXPECT_EQ(p.x(), 5);
  EXPECT_EQ(p.y(), 5);
}

TEST(PacmanMove, MoveConsumePellet) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::RIGHT);
  SMap m = makeOpenMap();
  m.map[5][6] = PELLET;
  MapObjectType result = p.move(m);
  EXPECT_EQ(result, PELLET);
}

TEST(PacmanMove, MoveConsumePowerUp) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::RIGHT);
  SMap m = makeOpenMap();
  m.map[5][6] = POWER_UP;
  MapObjectType result = p.move(m);
  EXPECT_EQ(result, POWER_UP);
}

TEST(PacmanMove, MoveSavesPreviousPosition) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::RIGHT);
  SMap m = makeOpenMap();
  p.move(m);
  EXPECT_EQ(p.prev_x(), 5);
  EXPECT_EQ(p.prev_y(), 5);
}

TEST(PacmanMove, MoveUpdatesMapOldTile) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::RIGHT);
  SMap m = makeOpenMap();
  p.move(m);
  EXPECT_EQ(m.map[5][5], EMPTY);
}

TEST(PacmanMove, MoveUpdatesMapNewTile) {
  Pacman p;
  p.setPosition(5, 5);
  p.setDirection(Direction::RIGHT);
  SMap m = makeOpenMap();
  p.move(m);
  EXPECT_EQ(m.map[5][6], PACMAN_PLAYER);
}

TEST(PacmanMove, TunnelWrapLeftEntry) {
  Pacman p;
  p.setPosition(8, 0);
  p.setDirection(Direction::LEFT);
  SMap m = makeOpenMap();
  p.move(m);
  EXPECT_EQ(p.x(), 8);
  EXPECT_EQ(p.y(), 19);
}

TEST(PacmanMove, TunnelWrapRightEntry) {
  Pacman p;
  p.setPosition(8, 19);
  p.setDirection(Direction::RIGHT);
  SMap m = makeOpenMap();
  p.move(m);
  EXPECT_EQ(p.x(), 8);
  EXPECT_EQ(p.y(), 0);
}
