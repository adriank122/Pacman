#ifndef PACMAN_CORE_GAME_H
#define PACMAN_CORE_GAME_H

#include "map.h"
#include "pman.h"
#include "ghost.h"

namespace pacman {

// Forward declaration of Renderer at correct namespace level
namespace rendering {
class Renderer;
}

namespace core {

struct SGame{
    SPman pman;
    SMap map;
    SGhost ghost1, ghost2, ghost3, ghost4;
    int timer;
    int delay;
    int food;
};

void game_menu(SGame &game, rendering::Renderer &renderer);
int game_quit(rendering::Renderer &renderer);
void game_count(SGame &game, rendering::Renderer &renderer);
void game_new(SGame &game, int level, rendering::Renderer &renderer);
void game_instruction(SGame &game, rendering::Renderer &renderer);
void game_init(SGame &game);
void show_leaderboard(rendering::Renderer &renderer);
void save_leaderboard(SGame game, rendering::Renderer &renderer);
void game_leaderboard(SGame game, rendering::Renderer &renderer);

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_GAME_H
