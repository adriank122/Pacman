#ifndef PACMAN_CORE_LEADERBOARD_H
#define PACMAN_CORE_LEADERBOARD_H

#include <string>
#include <vector>

namespace pacman {
namespace core {

struct LeaderboardEntry {
  std::string name;
  int score;
};

class Leaderboard {
public:
  explicit Leaderboard(const std::string &filePath = "leaderboard.txt");

  const std::vector<LeaderboardEntry> &entries() const;
  void addEntry(const std::string &playerName, int score);

private:
  std::string filePath_;
  std::vector<LeaderboardEntry> entries_;

  void load();
  void save() const;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_LEADERBOARD_H
