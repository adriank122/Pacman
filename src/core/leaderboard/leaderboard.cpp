#include "core/leaderboard/leaderboard.h"
#include <algorithm>
#include <fstream>

namespace pacman {
namespace core {

Leaderboard::Leaderboard(const std::string &filePath) : filePath_(filePath) {
  load();
}

const std::vector<LeaderboardEntry> &Leaderboard::entries() const {
  return entries_;
}

void Leaderboard::addEntry(const std::string &playerName, int score) {
  entries_.push_back({playerName.empty() ? "Anonymous" : playerName, score});
  std::sort(entries_.begin(), entries_.end(),
            [](const auto &a, const auto &b) { return a.score > b.score; });
  if (entries_.size() > 10)
    entries_.resize(10);
  save();
}

void Leaderboard::load() {
  entries_.clear();
  std::ifstream f(filePath_);
  std::string line;
  while (std::getline(f, line)) {
    auto tab = line.find('\t');
    if (tab == std::string::npos)
      continue;
    try {
      entries_.push_back(
          {line.substr(0, tab), std::stoi(line.substr(tab + 1))});
    } catch (...) {
    }
  }
}

void Leaderboard::save() const {
  std::ofstream of(filePath_);
  for (const auto &e : entries_)
    of << e.name << '\t' << e.score << '\n';
}

} // namespace core
} // namespace pacman
