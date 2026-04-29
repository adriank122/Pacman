# Pacman Game

A classic Pacman game implemented in C++. Move around the map, avoid ghosts and gather all pellets to win.

The motiviation for this project was to practice C++ skills on game project.

## Features

- **CLI Mode**: Terminal-based gameplay with text rendering
- **GUI Mode**: 2D graphics-based gameplay with SFML
- **Multiple Levels**: Two complete game levels with different map layouts
- **Scoring System**: Track scores with a ranking system
- **Technology Stack**: C++, Linux, CMake, SFML
- **Finite State Machine**: FSM to control game state flow

## TODOs

- Variable timestep driven update
- Ghost movement logic improvement
- Multiple difficulty
- DEMO section with gameplay gif

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
mkdir build
cd build
cmake ..
make
```

This will build:
- `pacman-cli` - CLI version
- `pacman-gui` - GUI version

## Testing

Run all tests:

```bash
cd build && ctest
```

Run only a specific suite (e.g. all `LoadConfig` tests) with regex:

```bash
cd build && ctest -R ^LoadConfig\.
```

Run a single test by its full name:

```bash
cd build && ctest -R LoadConfig.TrimsWhitespaceAroundKeyAndValue
```

The argument is a substring match against `Suite/TestName`, so any unique prefix or fragment works.

Or run all tests via CTest:

```bash
cd build && ctest --output-on-failure
```

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
