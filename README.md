# Pacman Game

A classic Pacman game implemented in C++. Move around the map, avoid ghosts and gather all pellets to win.

## Features

- **CLI Mode**: Terminal-based gameplay with text rendering
- **Multiple Levels**: Two complete game levels with different map layouts
- **Scoring System**: Track scores with a ranking system
- **Technology Stack**: C++, Linux, CMake, Make

## TODOs

- 2D graphics-based gameplay with SFML
- Ghost movement logic improvement
- Multiple difficulty level

## Building

```bash
cd /path/to/Pacman
mkdir -p build
cd build
cmake ..
make
```

## Usage

```bash
./pacman-cli
```

## Controls

- `W` - Move up
- `A` - Move left
- `S` - Move down
- `D` - Move right
- Menu navigation: `1`, `2`, `3`, `4` for menu options

## Gameplay

1. Collect all pellets (`.`) to advance levels
2. Avoid ghosts (`A`) - you have 3 lives
3. Special pellets (`e`) give bonus points
4. Complete levels within the time limit