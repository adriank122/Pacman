#include "core/ghost.h"
#include <array>
#include <vector>

namespace pacman {
namespace core {

Ghost::Ghost()
    : last_move(Direction::LEFT), xg(0), yg(0), prev_xg(0), prev_yg(0) {}

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

namespace {

struct MovePlan {
  int dx;
  int dy;
  Direction dir;
};

constexpr std::array<MovePlan, 4> ALL_MOVES = {{
    {-1, 0, Direction::UP},
    {1, 0, Direction::DOWN},
    {0, -1, Direction::LEFT},
    {0, 1, Direction::RIGHT},
}};

bool isTileAvailable(const SMap &map, int x, int y) {
  return map.map[x][y] != WALL;
}

Direction reverseOf(Direction dir) {
  switch (dir) {
  case Direction::UP:
    return Direction::DOWN;
  case Direction::DOWN:
    return Direction::UP;
  case Direction::LEFT:
    return Direction::RIGHT;
  case Direction::RIGHT:
    return Direction::LEFT;
  default:
    return Direction::NONE;
  }
}

} // namespace

MapObjectType Ghost::move(SMap &map) {
  savePreviousPosition();

  Direction reverse = reverseOf(last_move);
  std::vector<MovePlan> candidates;

  for (const MovePlan &m : ALL_MOVES) {
    if (m.dir != reverse && isTileAvailable(map, xg + m.dx, yg + m.dy))
      candidates.push_back(m);
  }

  // At a dead end allow reversing
  if (candidates.empty()) {
    for (const MovePlan &m : ALL_MOVES) {
      if (isTileAvailable(map, xg + m.dx, yg + m.dy))
        candidates.push_back(m);
    }
  }

  if (candidates.empty())
    return EMPTY;

  // No crossroad: only one option, take it; crossroad: pick randomly
  const MovePlan &chosen = candidates.size() == 1
                               ? candidates[0]
                               : candidates[std::rand() % candidates.size()];

  xg += chosen.dx;
  yg += chosen.dy;
  last_move = chosen.dir;
  return EMPTY;
}

} // namespace core
} // namespace pacman
