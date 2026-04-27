#include "core/game/game_timer.h"
#include <algorithm>

namespace pacman {
namespace core {

GameTimer::GameTimer(int tickMs)
    : previous(Clock::now()), lagMs(0.0), tickMs(static_cast<double>(tickMs)) {}

int GameTimer::advance() {
  auto current = Clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(current - previous)
          .count();
  previous = current;
  if (elapsed < 0) {
    elapsed = 0;
  }

  lagMs += static_cast<double>(elapsed);
  return static_cast<int>(elapsed);
}

bool GameTimer::hasTick() const { return lagMs >= tickMs; }

void GameTimer::consumeTick() {
  if (lagMs >= tickMs) {
    lagMs -= tickMs;
  } else {
    lagMs = 0.0;
  }
}

double GameTimer::interpolation() const {
  return std::min(1.0, lagMs / tickMs);
}

} // namespace core
} // namespace pacman
