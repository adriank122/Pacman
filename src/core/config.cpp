#include "core/config.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace pacman {
namespace core {

static std::string trim(const std::string &value) {
  auto begin = value.find_first_not_of(" \t\r\n");
  if (begin == std::string::npos)
    return "";

  auto end = value.find_last_not_of(" \t\r\n");
  return value.substr(begin, end - begin + 1);
}

void GameConfig::updateDerivedValues() {
  mapWidth = (mapWidth > 0 ? mapWidth : 20);
  mapHeight = (mapHeight > 0 ? mapHeight : 17);
  tileSize = (tileSize > 0 ? tileSize : 16);
  uiHeight = (uiHeight > 0 ? uiHeight : 80);
  windowWidth = mapWidth * tileSize;
  windowHeight = mapHeight * tileSize;
}

GameConfig loadConfig(const std::string &path) {
  GameConfig config;
  std::ifstream file(path);
  if (!file.is_open()) {
    return config;
  }

  std::string line;
  while (std::getline(file, line)) {
    auto commentPosition = line.find('#');
    if (commentPosition != std::string::npos) {
      line = line.substr(0, commentPosition);
    }
    line = trim(line);
    if (line.empty()) {
      continue;
    }

    auto equalsPos = line.find('=');
    if (equalsPos == std::string::npos) {
      continue;
    }

    std::string key = trim(line.substr(0, equalsPos));
    std::string value = trim(line.substr(equalsPos + 1));

    try {
      if (key == "tile_size") {
        config.tileSize = std::stoi(value);
      } else if (key == "ui_height") {
        config.uiHeight = std::stoi(value);
      } else if (key == "starting_lives") {
        config.startingLives = std::stoi(value);
      } else if (key == "starting_timer_ms") {
        config.startingTimerMs = std::stoi(value);
      } else if (key == "game_tick_delay_ms") {
        config.gameTickDelayMs = std::stoi(value);
      } else if (key == "pacman_start_x") {
        config.pacmanStartX = std::stoi(value);
      } else if (key == "pacman_start_y") {
        config.pacmanStartY = std::stoi(value);
      } else if (key == "ghost1_start_x") {
        config.ghost1StartX = std::stoi(value);
      } else if (key == "ghost1_start_y") {
        config.ghost1StartY = std::stoi(value);
      } else if (key == "ghost2_start_x") {
        config.ghost2StartX = std::stoi(value);
      } else if (key == "ghost2_start_y") {
        config.ghost2StartY = std::stoi(value);
      } else if (key == "ghost3_start_x") {
        config.ghost3StartX = std::stoi(value);
      } else if (key == "ghost3_start_y") {
        config.ghost3StartY = std::stoi(value);
      } else if (key == "ghost4_start_x") {
        config.ghost4StartX = std::stoi(value);
      } else if (key == "ghost4_start_y") {
        config.ghost4StartY = std::stoi(value);
      } else if (key == "power_up_score") {
        config.powerUpScore = std::stoi(value);
      }
    } catch (const std::exception &) {
      std::cerr << "Warning: invalid config value for '" << key << "'\n";
    }
  }

  config.updateDerivedValues();
  return config;
}

} // namespace core
} // namespace pacman
