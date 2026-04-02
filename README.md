# Pacman Game

A classic Pacman game implemented in C++. Move around the map, avoid ghosts and gather all pellets to win. Supports both terminal and GUI gameplay.

## Features

- **CLI Mode**: Terminal-based gameplay with text rendering
- **GUI Mode**: 2D graphics-based gameplay with SFML
- **Multiple Levels**: Two complete game levels with different map layouts
- **Scoring System**: Track scores with a ranking system
- **Technology Stack**: C++, Linux, CMake, SFML

## TODOs

- Ghost movement logic improvement
- Multiple difficulty level

## Building

### 1. Install dependencies

```bash
# Ubuntu/Debian - essential tools
sudo apt-get update
sudo apt-get install cmake build-essential

# SFML for GUI mode
sudo apt-get install libsfml-dev
```

### 2. Build the project

```bash
cd /path/to/Pacman
mkdir -p build
cd build
cmake ..
make
```

This will build:
- `pacman-cli` - CLI version
- `pacman-gui` - GUI version

## Usage

### CLI Mode

```bash
./pacman-cli
```

### GUI Mode

```bash
./pacman-gui
```

**Controls**:
- `W` - Move up
- `A` - Move left
- `S` - Move down
- `D` - Move right
- Menu navigation: `1` (New Game), `2` (Instructions), `3` (Ranking), `4` (Quit)

## Gameplay

1. Collect all pellets (`.`) to advance levels
2. Avoid ghosts (`A`) - you have 3 lives
3. Special pellets (`e`) give bonus points
4. Complete levels within the time limit