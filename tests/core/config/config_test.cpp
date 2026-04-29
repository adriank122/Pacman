#include "core/config/config.h"
#include <fstream>
#include <gtest/gtest.h>
#include <string>

using namespace pacman::core;

static std::string writeTempIni(const std::string &content) {
  std::string path = "/tmp/pacman_config_test.ini";
  std::ofstream f(path);
  f << content;
  return path;
}

TEST(GameConfigDefaults, StructHasExpectedDefaults) {
  GameConfig cfg;
  EXPECT_EQ(cfg.mapWidth, 20);
  EXPECT_EQ(cfg.mapHeight, 17);
  EXPECT_EQ(cfg.tileSize, 16);
  EXPECT_EQ(cfg.uiHeight, 80);
  EXPECT_EQ(cfg.startingLives, 3);
  EXPECT_EQ(cfg.startingTimerMs, 200000);
  EXPECT_EQ(cfg.gameTickDelayMs, 300);
  EXPECT_EQ(cfg.pacmanStartX, 13);
  EXPECT_EQ(cfg.pacmanStartY, 9);
  EXPECT_EQ(cfg.ghost1StartX, 15);
  EXPECT_EQ(cfg.ghost1StartY, 1);
  EXPECT_EQ(cfg.ghost2StartX, 15);
  EXPECT_EQ(cfg.ghost2StartY, 18);
  EXPECT_EQ(cfg.ghost3StartX, 1);
  EXPECT_EQ(cfg.ghost3StartY, 1);
  EXPECT_EQ(cfg.ghost4StartX, 1);
  EXPECT_EQ(cfg.ghost4StartY, 18);
  EXPECT_EQ(cfg.powerUpScore, 5);
}

TEST(LoadConfig, MissingFileReturnsDefaults) {
  GameConfig cfg = loadConfig("/tmp/does_not_exist_pacman.ini");
  EXPECT_EQ(cfg.startingLives, 3);
  EXPECT_EQ(cfg.tileSize, 16);
  EXPECT_EQ(cfg.mapWidth, 20);
}

TEST(LoadConfig, ParsesAllSupportedKeys) {
  std::string ini = "tile_size = 32\n"
                    "ui_height = 100\n"
                    "starting_lives = 5\n"
                    "starting_timer_ms = 99000\n"
                    "game_tick_delay_ms = 150\n"
                    "pacman_start_x = 2\n"
                    "pacman_start_y = 3\n"
                    "ghost1_start_x = 4\n"
                    "ghost1_start_y = 5\n"
                    "ghost2_start_x = 6\n"
                    "ghost2_start_y = 7\n"
                    "ghost3_start_x = 8\n"
                    "ghost3_start_y = 9\n"
                    "ghost4_start_x = 10\n"
                    "ghost4_start_y = 11\n"
                    "power_up_score = 50\n";
  GameConfig cfg = loadConfig(writeTempIni(ini));

  EXPECT_EQ(cfg.tileSize, 32);
  EXPECT_EQ(cfg.uiHeight, 100);
  EXPECT_EQ(cfg.startingLives, 5);
  EXPECT_EQ(cfg.startingTimerMs, 99000);
  EXPECT_EQ(cfg.gameTickDelayMs, 150);
  EXPECT_EQ(cfg.pacmanStartX, 2);
  EXPECT_EQ(cfg.pacmanStartY, 3);
  EXPECT_EQ(cfg.ghost1StartX, 4);
  EXPECT_EQ(cfg.ghost1StartY, 5);
  EXPECT_EQ(cfg.ghost2StartX, 6);
  EXPECT_EQ(cfg.ghost2StartY, 7);
  EXPECT_EQ(cfg.ghost3StartX, 8);
  EXPECT_EQ(cfg.ghost3StartY, 9);
  EXPECT_EQ(cfg.ghost4StartX, 10);
  EXPECT_EQ(cfg.ghost4StartY, 11);
  EXPECT_EQ(cfg.powerUpScore, 50);
}

TEST(LoadConfig, IgnoresCommentLines) {
  std::string ini = "# This is a comment\n"
                    "starting_lives = 7\n"
                    "# Another comment\n";
  GameConfig cfg = loadConfig(writeTempIni(ini));
  EXPECT_EQ(cfg.startingLives, 7);
}

TEST(LoadConfig, StripsInlineComments) {
  GameConfig cfg = loadConfig(writeTempIni("starting_lives = 4 # inline\n"));
  EXPECT_EQ(cfg.startingLives, 4);
}

TEST(LoadConfig, TrimsWhitespaceAroundKeyAndValue) {
  GameConfig cfg = loadConfig(writeTempIni("  starting_lives   =   6  \n"));
  EXPECT_EQ(cfg.startingLives, 6);
}

TEST(LoadConfig, SkipsBlankLines) {
  GameConfig cfg = loadConfig(writeTempIni("\n\n\nstarting_lives = 2\n\n"));
  EXPECT_EQ(cfg.startingLives, 2);
}

TEST(LoadConfig, SkipsLinesWithoutEquals) {
  GameConfig cfg =
      loadConfig(writeTempIni("this_line_has_no_equals\nstarting_lives = 1\n"));
  EXPECT_EQ(cfg.startingLives, 1);
}

TEST(LoadConfig, InvalidValueKeepsDefault) {
  GameConfig cfg = loadConfig(writeTempIni("starting_lives = not_a_number\n"));
  EXPECT_EQ(cfg.startingLives, 3);
}

TEST(LoadConfig, UnknownKeyIsIgnored) {
  GameConfig cfg =
      loadConfig(writeTempIni("unknown_key = 42\nstarting_lives = 2\n"));
  EXPECT_EQ(cfg.startingLives, 2);
}

TEST(UpdateDerivedValues, ComputesWindowDimensions) {
  GameConfig cfg;
  cfg.mapWidth = 10;
  cfg.mapHeight = 8;
  cfg.tileSize = 20;
  cfg.uiHeight = 40;
  cfg.updateDerivedValues();

  EXPECT_EQ(cfg.windowWidth, 200);  // 10 * 20
  EXPECT_EQ(cfg.windowHeight, 160); // 8 * 20
}

TEST(UpdateDerivedValues, NegativeValuesFallBackToDefaults) {
  GameConfig cfg;
  cfg.mapWidth = -5;
  cfg.mapHeight = -3;
  cfg.tileSize = -1;
  cfg.uiHeight = -10;
  cfg.updateDerivedValues();

  EXPECT_EQ(cfg.mapWidth, 20);
  EXPECT_EQ(cfg.mapHeight, 17);
  EXPECT_EQ(cfg.tileSize, 16);
  EXPECT_EQ(cfg.uiHeight, 80);
}

TEST(UpdateDerivedValues, ZeroValuesFallBackToDefaults) {
  GameConfig cfg;
  cfg.mapWidth = 0;
  cfg.mapHeight = 0;
  cfg.tileSize = 0;
  cfg.uiHeight = 0;
  cfg.updateDerivedValues();

  EXPECT_EQ(cfg.mapWidth, 20);
  EXPECT_EQ(cfg.mapHeight, 17);
  EXPECT_EQ(cfg.tileSize, 16);
  EXPECT_EQ(cfg.uiHeight, 80);
}

TEST(LoadConfig, DerivedWindowDimensionsReflectParsedTileSize) {
  // mapWidth/mapHeight stay at defaults (20x17); only tile_size changes.
  GameConfig cfg = loadConfig(writeTempIni("tile_size = 8\n"));
  EXPECT_EQ(cfg.windowWidth, 20 * 8);
  EXPECT_EQ(cfg.windowHeight, 17 * 8);
}
