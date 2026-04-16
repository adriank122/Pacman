#ifndef PACMAN_CORE_GAME_TIMER_H
#define PACMAN_CORE_GAME_TIMER_H

#include <chrono>

namespace pacman {
namespace core {

class GameTimer {
public:
  explicit GameTimer(int tickMs);

  // Advance timing by the elapsed wall-clock duration and return elapsed ms.
  int advance();

  // True when enough lag has accumulated for a fixed tick update.
  bool hasTick() const;

  // Consume one fixed tick from the accumulated lag.
  void consumeTick();

  // Interpolation value between the last and next tick.
  double interpolation() const;

private:
  using Clock = std::chrono::steady_clock;

  Clock::time_point previous;
  double lagMs;
  const double tickMs;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_GAME_TIMER_H
