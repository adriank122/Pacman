#include "core/entities/ghost.h"
#include <array>
#include <vector>

namespace pacman {
namespace core {

Ghost::Ghost(int x, int y) {
  setPosition(x, y);
  savePreviousPosition();
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

bool isTileAvailable(const Map &map, int x, int y) { return !map.isWall(x, y); }

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

TileType Ghost::move(Map &map) {
  savePreviousPosition();

  Direction reverse = reverseOf(direction_);
  std::vector<MovePlan> candidates;

  for (const MovePlan &m : ALL_MOVES) {
    if (m.dir != reverse && isTileAvailable(map, x_ + m.dx, y_ + m.dy))
      candidates.push_back(m);
  }

  // At a dead end allow reversing
  if (candidates.empty()) {
    for (const MovePlan &m : ALL_MOVES) {
      if (isTileAvailable(map, x_ + m.dx, y_ + m.dy))
        candidates.push_back(m);
    }
  }

  if (candidates.empty())
    return TileType::EMPTY;

  // No crossroad: only one option, take it; crossroad: pick randomly
  const MovePlan &chosen = candidates.size() == 1
                               ? candidates[0]
                               : candidates[std::rand() % candidates.size()];

  x_ += chosen.dx;
  y_ += chosen.dy;
  direction_ = chosen.dir;
  return TileType::EMPTY;
}

} // namespace core
} // namespace pacman
