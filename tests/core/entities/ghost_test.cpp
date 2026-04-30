#include "core/entities/ghost.h"
#include "core/map/map.h"
#include <gtest/gtest.h>

using namespace pacman::core;

static SMap makeOpenMap() {
  SMap m{};
  return m;
}

TEST(GhostDefaults, InitialPosition) {
  Ghost g;
  EXPECT_EQ(g.x(), 0);
  EXPECT_EQ(g.y(), 0);
}

TEST(GhostDefaults, InitialLastMove) {
  Ghost g;
  EXPECT_EQ(g.direction(), Direction::NONE);
}

TEST(GhostDefaults, InitialPrevPosition) {
  Ghost g;
  EXPECT_EQ(g.prev_x(), 0);
  EXPECT_EQ(g.prev_y(), 0);
}

TEST(GhostSetters, SetPosition) {
  Ghost g;
  g.setPosition(3, 5);
  EXPECT_EQ(g.x(), 3);
  EXPECT_EQ(g.y(), 5);
}

TEST(GhostSetters, SetDirection) {
  Ghost g;
  g.setDirection(Direction::UP);
  EXPECT_EQ(g.direction(), Direction::UP);
}

TEST(GhostSetters, SavePreviousPosition) {
  Ghost g;
  g.setPosition(3, 5);
  g.savePreviousPosition();
  EXPECT_EQ(g.prev_x(), 3);
  EXPECT_EQ(g.prev_y(), 5);
}

// last_move=UP → reverse=DOWN; only LEFT open → ghost must go LEFT
TEST(GhostMove, MoveAvoidsWalls) {
  Ghost g;
  g.setPosition(5, 5);
  g.setDirection(Direction::UP);
  SMap m = makeOpenMap();
  m.map[4][5] = WALL; // UP - blocked
  m.map[5][6] = WALL; // RIGHT - blocked
  // map[6][5] = EMPTY (DOWN = reverse, excluded by no-reverse rule)
  // map[5][4] = EMPTY (LEFT - the only valid candidate)
  g.move(m);
  EXPECT_EQ(g.x(), 5);
  EXPECT_EQ(g.y(), 4);
}

// last_move=RIGHT → reverse=LEFT; UP is the only non-reverse, non-wall option
TEST(GhostMove, MoveDoesNotReverse) {
  Ghost g;
  g.setPosition(5, 5);
  g.setDirection(Direction::RIGHT);
  SMap m = makeOpenMap();
  m.map[6][5] = WALL; // DOWN - blocked
  m.map[5][6] = WALL; // RIGHT - blocked
  // map[5][4] = EMPTY (LEFT = reverse, excluded)
  // map[4][5] = EMPTY (UP - the only valid candidate)
  g.move(m);
  EXPECT_EQ(g.x(), 4);
  EXPECT_EQ(g.y(), 5);
}

// last_move=RIGHT → reverse=LEFT; all non-reverse tiles are walls → ghost
// reverses
TEST(GhostMove, MoveReversesAtDeadEnd) {
  Ghost g;
  g.setPosition(5, 5);
  g.setDirection(Direction::RIGHT);
  SMap m = makeOpenMap();
  m.map[4][5] = WALL; // UP - blocked
  m.map[6][5] = WALL; // DOWN - blocked
  m.map[5][6] = WALL; // RIGHT - blocked
  // map[5][4] = EMPTY (LEFT = reverse, only option at dead end)
  g.move(m);
  EXPECT_EQ(g.x(), 5);
  EXPECT_EQ(g.y(), 4);
  EXPECT_EQ(g.direction(), Direction::LEFT);
}

// last_move=UP → reverse=DOWN; only UP open → ghost goes UP and returns EMPTY
TEST(GhostMove, MoveReturnsEmpty) {
  Ghost g;
  g.setPosition(5, 5);
  g.setDirection(Direction::UP);
  SMap m = makeOpenMap();
  MapObjectType result = g.move(m);
  EXPECT_EQ(result, EMPTY);
}

TEST(GhostMove, MoveSavesPreviousPosition) {
  Ghost g;
  g.setPosition(5, 5);
  g.setDirection(Direction::UP);
  SMap m = makeOpenMap();
  g.move(m);
  EXPECT_EQ(g.prev_x(), 5);
  EXPECT_EQ(g.prev_y(), 5);
}

// last_move=RIGHT → reverse=LEFT; only UP available → last_move becomes UP
TEST(GhostMove, MoveUpdatesLastMove) {
  Ghost g;
  g.setPosition(5, 5);
  g.setDirection(Direction::RIGHT);
  SMap m = makeOpenMap();
  m.map[6][5] = WALL; // DOWN - blocked
  m.map[5][6] = WALL; // RIGHT - blocked
  // map[5][4] = EMPTY (LEFT = reverse, excluded)
  // map[4][5] = EMPTY (UP - only valid candidate)
  g.move(m);
  EXPECT_EQ(g.direction(), Direction::UP);
}
